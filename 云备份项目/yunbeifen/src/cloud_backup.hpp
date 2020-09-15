#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <zlib.h>
#include <pthread.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include "httplib.h"

#define NONHOT_TIME 10  //最后一次访问时间大于10秒是非热点文件
#define INTERVAL_TIME 30  //30秒循环一次进行检测
#define BACKUP_DIR "./backup"  //文件的备份路径
#define GZFILE_DIR "./gzfile"  //压缩包存放路径
#define DATA_FILE "./list.backup"  //数据管理模块的数据备份名称


namespace _cloud_sys
{
    class FileUtil
    {
        public:
            static bool  Read(const std::string &name , std::string *body)//从文件中读取所有内容
            {
                std::ifstream fs(name , std::ios::binary );//输入文件流，以二进制形式打开
                if(fs.is_open() == false)
                {
                    std::cout<<"open file" << name << "filed" << std::endl;
                    return false;
                }
                int64_t fsize = boost::filesystem::file_size(name); //获取文件大小
                body->resize(fsize);//给body申请空间，接受文件数据
                fs.read(&(*body)[0],fsize);//body是指针，先解引用才能使用
                if(fs.good() == false)
                {
                    std::cout << "file" << name << "read data failed" << std::endl;
                    return false;
                }
                fs.close();
                return true;
            }
            static bool Write(const std::string &name , const std::string &body)//向文件中写入数据
            {
                std::ofstream ofs(name , std::ios::binary );//输入流
                if(ofs.is_open() == false)
                {

                    std::cout<<"open file" << name << "filed" << std::endl;
                    return false;
                }
                ofs.write(&body[0] , body.size());
                if(ofs.good() == false )
                {
                    std::cout << "file" << name << "write data failed" << std::endl;
                    return false;
                }
                ofs.close();
                return true;
            }

    };
    class CompressUtil
    {
        public:
            static bool Compress(const std::string &src , const std::string &dst)//文件压缩 -- 源文件名称和压缩包名称
            {
                std::string body;
                FileUtil::Read(src , &body);
                gzFile gf = gzopen(dst.c_str() , "wb");//打开压缩包
                if(gf == NULL)
                {
                    std::cout << "open file" << dst << "filed" <<std::endl;
                    return false;
                }
                int wlen = 0;
                while(wlen < body.size())//若一次没有将数据全部压缩，则下次从未压缩的部分开始继续压缩
                {
                    int ret = gzwrite(gf , &body[wlen] , body.size() - wlen);
                    if(ret == 0)
                    {
                        std::cout << "file" << dst <<  "write Compress data failed" << std::endl;
                        return false;
                    }
                    wlen += ret;

                }
                gzclose(gf);
                return true;
            }
            static bool UnCompress(const std::string &src , const std::string &dst ) //文件解压缩 -- 压缩包名称和源文件名称
            {
                std::ofstream ofs (dst ,std::ios::binary);
                if(ofs.is_open() == false )
                {
                    std::cout<< "open file" << dst << "filed" << std::endl;
                    return false;
                }
                gzFile gf = gzopen(src.c_str() , "rb");
                if(gf == NULL )
                {
                    std::cout<< "open file" << src << "failed" << std::endl;
                    ofs.close();
                    return false ;
                }
                int ret ;
                char tmp[4096] = {0};
                while (( ret = gzread(gf , tmp , 4096)) > 0 )//gzread(句柄，缓冲区，缓冲区大小)
                {
                    ofs.write(tmp , ret);
                }
                ofs.close();
                gzclose(gf);

                return true;
            }
    };
    
    class DataManager
    {
        public:
            DataManager(const std::string &path):_back_file (path)
            {
                pthread_rwlock_init(&_rwlock , NULL);
                
            }
            ~DataManager()
            {
                pthread_rwlock_destroy(&_rwlock);

            }
            bool Exists(const std::string &name) //判断文件是否存在,是否能从_file_list 找到这个文件信息
            {
                pthread_rwlock_rdlock(&_rwlock);
                auto it = _file_list.find(name);
                if(it == _file_list.end())
                {
                    pthread_rwlock_unlock(&_rwlock);
                    return false;
                }
                return true;

            }
            bool IsCompress(const std::string &name) //判断文件是否已经压缩,文件上传后源文件与压缩包名称一致，比较名称
            {
                pthread_rwlock_rdlock(&_rwlock);
                auto it = _file_list.find(name);
                if(it == _file_list.end())
                {
                    pthread_rwlock_unlock(&_rwlock);
                    return false;
                }
                if(it->first == it->second)
                {
                    pthread_rwlock_unlock(&_rwlock);
                    return false;//名称一样，表示未压缩
                }
                    pthread_rwlock_unlock(&_rwlock);
                return true;

            }
            bool NonCompress(std::vector<std::string> *list) //获取未压缩文件列表
            {
                //遍历_file_list
                pthread_rwlock_rdlock(&_rwlock);
                auto it = _file_list.begin();
                for( ; it != _file_list.end();it++)
                {
                    if(it->first == it->second )
                    {
                        list->push_back(it->first);
                    }
                }
                pthread_rwlock_unlock(&_rwlock);
                return true;
            }
            bool Insert(const std::string &src, const std::string &dst)//插入更新数据
            {
                //src 源文件名称   dst 压缩包名称
                pthread_rwlock_wrlock(&_rwlock);
                _file_list[src] = dst;
                pthread_rwlock_unlock(&_rwlock);
				Storage();
                return true;
            }
            bool GetAllName(std::vector<std::string> *list)//获取所有文件名称
            {
                pthread_rwlock_rdlock(&_rwlock);
                auto it = _file_list.begin();
                for(;it != _file_list.end() ; it++)
                {
                    list->push_back(it->first);//获取源文件名称
                }
                pthread_rwlock_unlock(&_rwlock);
                return true;
            }
			bool GetGzName(const std::string &src, std::string *dst)//根据源文件名称获取压缩包名称
			{
				auto it = _file_list.find(src);
				if (it == _file_list.end())
				{
					return false;
				}
				*dst = it->second;
				return true;
			}
            bool Storage()//数据改变后持久化存储
            {
                //将_file_list 中的数据进行持久化存储 -- 序列化    src dst\r\n
                std::stringstream tmp;//实例化一个string流对象
                pthread_rwlock_rdlock(&_rwlock);
                auto it = _file_list.begin();
                for(;it != _file_list.end() ; it++)
                {
                    tmp << it->first << " " << it->second <<"\r\n";
                }
                pthread_rwlock_unlock(&_rwlock);
                FileUtil::Write(_back_file , tmp.str());
                return true;
            }
            bool InitLoad() //启动时初始化加载原有数据
            {
                //1.将这个备份文件的数据读取出来，2.进行字符串处理，按照\r\n进行分割 3.每一行按照空格进行分割
                std::string body;
                if(FileUtil::Read(_back_file,&body) == false )
                {
                    return false;
                }
                std::vector<std::string> list;
                boost::split(list , body , boost::is_any_of("\r\n"), boost::token_compress_off );
                for(auto i : list)
                {
                    size_t pos = i.find(" ");
                    if(pos == std::string::npos)
                    {
                        continue;
                    }
                    std::string key = i.substr(0,pos);
                    std::string val = i.substr(pos+1);
                    Insert(key,val);
                }
                return true;
            }
        private:
            std::string _back_file;//持久化数据存储文件名称
            std::unordered_map<std::string,std::string> _file_list;//数据管理容器
            pthread_rwlock_t _rwlock;


    };
    
  _cloud_sys::DataManager data_manage(DATA_FILE);
    class NonHotCompress
    {
    public:
        NonHotCompress(const std::string dir_name, const std::string bu_dir):
            _gz_dir(dir_name),_bu_dir(bu_dir)
        {

        }
        bool Start()//开始运行，总体向外提供的功能接口
        {
            //循环的，每隔一段时间判断是否有非热点文件，然后进行压缩
            while(1)
            {
                //1.获取文件列表
                std::vector<std::string> list;
                data_manage.NonCompress(&list);
                //2.判断是否是热点文件
                for(int i = 0; i < list.size() ; i++ )
                {
                    bool ret = FileIsHot(list[i]);
                    if(ret == false)
                    {
                        std::cout << "non hot file" << list[i] << std::endl;
                        std::string s_filename = list[i]; //源文件名称
                        std::string d_filename = list[i] + ".gz"; //压缩包名称
                        std::string src_name = _bu_dir + s_filename;//源文件路径名称
                        std::string dst_name = _gz_dir + d_filename ; 
                //3.非热点文件进行压缩
                      if(CompressUtil::Compress(src_name ,dst_name) == true)
                      {
                          data_manage.Insert(s_filename , d_filename); //更新数据信息
                          unlink(src_name.c_str());//删除源文件
                      }
                    }
                }
                //4.休眠
                sleep(INTERVAL_TIME);
            }

        }
    private :
        bool FileIsHot(const std::string &name)//判断文件是否是热点文件
        {
            time_t cur_t = time(NULL);
            struct stat st;
            if(stat(name.c_str() , &st) <0 )
            {
                std::cout << "get file" << name << "stat failed" <<std::endl;
                return false;
            }
            if((cur_t  -  st.st_atime) > NONHOT_TIME )
            {
                return false;
            }
            return true;
            //热点返回true  非热点返回false
        }
        std::string _bu_dir; //压缩前文件的路径
        std::string _gz_dir;//压缩后的文件路径

    };
    class Server 
    {

        public :
            Server()
            {

            }
            ~Server() 
            {

            }
            bool Start()
            {
                _server.Put("/(.*)" , UpLoad);
                _server.Get("/list" , List);
                _server.Get("/download/(.*)" , Download);

                _server.listen("0.0.0.0" , 9000);
                return true;
            }

        private :
            static void UpLoad(const httplib:: Request &req , httplib:: Response &rsp)//文件上传处理回调函数
            {
				std::string filename = req.matches[1];
				std::string pathname = BACKUP_DIR + filename;
				FileUtil::Write(pathname, req.body);
				rsp.status = 200;
				return;
                
            }
            static void List(const httplib:: Request &req , httplib:: Response &rsp)//文件列表处理回调函数
            {
				std::vector<std::string> list;
				data_manage.GetAllName(&list);
				std::stringstream tmp;
				tmp << "<html><body><hr />";
				for (int i = 0; i < list.size(); i++)
				{
					tmp << "<a href = " / download / " " << list[i] << ">" << list[i] << "</a>";
					tmp << "<hr />";
					//tmp << "<hr /> </body></html>" << "a.txt" << "</a>";
				}
				tmp << "<hr /><body></html>";

				rsp.set_content(tmp.str().c_str(), tmp.str().size(), "text/html");
				rsp.status = 200;
				return;

            }
            static void Download(const httplib:: Request &req , httplib:: Response &rsp)//文件下载处理回调函数
            {
				std::string filename = req.matches[1];
				if (data_manage.Exists(filename) == false)
				{
					rsp.status = 404;
					return;
				}
				std::string pathname = BACKUP_DIR + filename; // 源文件的备份路径
				if (data_manage.IsCompress(filename) != false)
				{
					//文件被压缩，先进行解压
					std::string gzfile;
					data_manage.GetGzName(filename, &gzfile);
					std::string gzpathname = GZFILE_DIR + gzfile;
					CompressUtil::UnCompress(gzpathname, pathname);
					unlink(gzpathname.c_str());//删除压缩包
					data_manage.Insert(pathname, pathname);
				}
				FileUtil::Read(pathname, &rsp.body);
				rsp.set_content("Content-Type", "application/oct-stream");
				rsp.status = 200;
				return;

            }
            std::string _file_dir;//文件上传备份路径
            httplib::Server  _server; 
    };
    
}
