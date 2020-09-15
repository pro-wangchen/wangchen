#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "httplib.h"

#define STORE_FILE "./list.backup"
#define LISTEN_DIR "./backup"



class FileUtil
{
public:
	static bool  Read(const std::string &name, std::string *body)//从文件中读取所有内容
	{
		std::ifstream fs(name, std::ios::binary);//输入文件流，以二进制形式打开
		if (fs.is_open() == false)
		{
			std::cout << "open file" << name << "filed" << std::endl;
			return false;
		}
		int64_t fsize = boost::filesystem::file_size(name); //获取文件大小
		body->resize(fsize);//给body申请空间，接受文件数据
		fs.read(&(*body)[0], fsize);//body是指针，先解引用才能使用
		if (fs.good() == false)
		{
			std::cout << "file" << name << "read data failed" << std::endl;
			return false;
		}
		fs.close();
		return true;
	}
	static bool Write(const std::string &name, const std::string &body)//向文件中写入数据
	{
		std::ofstream ofs(name, std::ios::binary);//输入流
		if (ofs.is_open() == false)
		{

			std::cout << "open file" << name << "filed" << std::endl;
			return false;
		}
		ofs.write(&body[0], body.size());
		if (ofs.good() == false)
		{
			std::cout << "file" << name << "write data failed" << std::endl;
			return false;
		}
		ofs.close();
		return true;
	}

};
class DataManager
{
public:
	DataManager(const std::string &filename)
		:_store_file(filename)
	{}
	bool Insert(const std::string &key, const std::string &val)//插入更新数据
	{
		_backup_list[key] = val;
		return true;
	}
	bool GetEtag(const std::string &key,  std::string *val)//通过文件名获取原有etag信息
	{
		auto it = _backup_list.find(key);
		if (it == _backup_list.end())
		{
			return false;
		}
		*val = it->second;
		return true;
	}
	bool Storage()//持久化存储
	{
		std::stringstream tmp;//实例化一个string流对象
		
		auto it = _backup_list.begin();
		for (; it != _backup_list.end(); it++)
		{
			tmp << it->first << " " << it->second << "\r\n";
		}
		
		FileUtil::Write(_store_file, tmp.str());
		return true;
		return true;
	}
	bool InitLoad()//初始化加载原有数据
	{
		std::string body;
		if (FileUtil::Read(_store_file, &body) == false)
		{
			return false;
		}
		std::vector<std::string> list;
		boost::split(list, body, boost::is_any_of("\r\n"), boost::token_compress_off);
		for (auto i : list)
		{
			size_t pos = i.find(" ");
			if (pos == std::string::npos)
			{
				continue;
			}
			std::string key = i.substr(0, pos);
			std::string val = i.substr(pos + 1);
			Insert(key, val);
		}
		return true;
	}
private:
	std::string _store_file;//持久化存储文件名称
	std::unordered_map < std::string, std::string> _backup_list;//备份的文件信息
};


class CloudClient//目录监控
{
public:
	CloudClient(const std::string &filename , const std::string &store_file , 
		const std::string &srv_ip , uint16_t srv_port)
		:_listen_dir(filename)
		,data_manage(store_file)
		,_srv_ip(srv_ip)
		,_srv_port(srv_port)
	{}
	bool Start()
	{
		data_manage.InitLoad();
		while (1)
		{
			std::vector<std::string> list;
			GetBackupFileList(&list);
			for (int i = 0; i < list.size(); i++)
			{
				std::string name = list[i]; //纯文件名
				std::string pathname = LISTEN_DIR + name;
				std::cout << pathname << "is need to backup" << std::endl;
				std::string body;
				FileUtil::Read(pathname, &body);
				httplib::Client client(_srv_ip, _srv_port); //实例化client对象，准备发起http上传文件请求
				std::string req_path = "/" + name;
				auto rsp = client.Put(req_path.c_str(), body, "appliction/octet-stream");
				if (rsp == NULL || rsp->status != 200)
				{
					//文件上传备份失败了
					std::cout << pathname << " backup failed" << std::endl;
					continue;
				}
				std::string etag;
				GetEtag(pathname, &etag);
				data_manage.Insert(name, etag);//备份成功，更新信息
				std::cout << pathname << " backup success" << std::endl;
			}
			Sleep(1000); //休眠1000ms

		}
	
		return true;
	}
	bool GetBackupFileList(std::vector<std::string> *list)//获取需要备份文件列表
	{
		if (boost::filesystem::exists(_listen_dir) == false)
		{
			boost::filesystem::create_directory(_listen_dir);//目录不存在就创建
		}
		/*1.获取目录下文件名称
		2.计算文件etag
		3.与原有的etag进行比对，没有找到或者不相等就进行备份，有且相等不用备份*/
		boost::filesystem::directory_iterator begin(_listen_dir);
		boost::filesystem::directory_iterator end;
		for (; begin != end; begin++)
		{
			if (boost::filesystem::is_directory(begin->status()))
			{
				//目录不进行备份，这里是简单的处理
				continue;
			}
			std::string pathname = begin->path().string();
			std::string name = begin->path().filename().string();
			std::string cur_etag;
			GetEtag(pathname, &cur_etag);
			std::string old_etag;
			data_manage.GetEtag(name , &old_etag);
			if (cur_etag != old_etag)
			{
				list->push_back(name);//不同则进行备份
			}
		}
		return true;
	}
	bool GetEtag(const std::string &pathname, std::string *etag)//计算文件的etag信息
	{
		//etag 文件大小，文件最后一次修改时间
		int64_t fsize = boost::filesystem::file_size(pathname);
		time_t mtime = boost::filesystem::last_write_time(pathname);
		*etag = std::to_string(fsize) + "-" + std::to_string(mtime);
		return true;
	}
private:
	std::string _srv_ip;
	uint16_t _srv_port;
	std::string _listen_dir;//监控的目录名称
	DataManager data_manage;
};

