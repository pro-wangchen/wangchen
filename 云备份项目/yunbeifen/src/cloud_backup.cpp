#include <thread>
#include "cloud_backup.hpp"


void compress_test(char *argv[])
{
    _cloud_sys::CompressUtil::Compress(argv[1] , argv[2]);
    std::string file = argv[2];
    file += ".txt";
    _cloud_sys::CompressUtil::UnCompress(argv[2] , file.c_str());
}

void data_test()
{
    _cloud_sys::DataManager data_manage("./test.txt");
    data_manage.InitLoad();
    data_manage.Insert("a.txt" , "a.txt/gz");
    std::vector<std::string> list;
    data_manage.GetAllName(&list);
    for(auto i : list )
    {
        printf("%s\n", i.c_str());
    }
    printf("**********************\n");
    list.clear();
    data_manage.NonCompress(&list);
    for(auto i : list)
    {
        printf("%s\n" , i.c_str());
    }
}

void m_non_compress()
{
    _cloud_sys::NonHotCompress ncom(GZFILE_DIR , BACKUP_DIR);
    ncom.Start();
    return;
}


void thr_http_server()
{
	_cloud_sys::Server srv;
	srv.Start();
	return;
}

int main(int argc , char *argv[])
{
    //argv[1] 源文件名称
    //argv[2] 压缩包名称
    /*
    if(boost::filesystem::exists(GZFILE_DIR) == false)
    {
        boost::filesystem::create_directory(GZFILE_DIR);
    }
    if(boost::filesystem::exists(BACKUP_DIR) == false)
    {
        boost::filesystem::create_directory(BACKUP_DIR);
    }
    
    std::thread thr(m_non_compress);
    thr.join();
    return 0;
    */
	std::thread thr(m_non_compress); //启动非热点文件压缩模块
	std::thread thr_server(thr_http_server); //网络通信服务启动
	thr_server.join();
    
    return 0;
}
