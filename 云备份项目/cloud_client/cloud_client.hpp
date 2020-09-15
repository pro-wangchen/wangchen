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
	static bool  Read(const std::string &name, std::string *body)//���ļ��ж�ȡ��������
	{
		std::ifstream fs(name, std::ios::binary);//�����ļ������Զ�������ʽ��
		if (fs.is_open() == false)
		{
			std::cout << "open file" << name << "filed" << std::endl;
			return false;
		}
		int64_t fsize = boost::filesystem::file_size(name); //��ȡ�ļ���С
		body->resize(fsize);//��body����ռ䣬�����ļ�����
		fs.read(&(*body)[0], fsize);//body��ָ�룬�Ƚ����ò���ʹ��
		if (fs.good() == false)
		{
			std::cout << "file" << name << "read data failed" << std::endl;
			return false;
		}
		fs.close();
		return true;
	}
	static bool Write(const std::string &name, const std::string &body)//���ļ���д������
	{
		std::ofstream ofs(name, std::ios::binary);//������
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
	bool Insert(const std::string &key, const std::string &val)//�����������
	{
		_backup_list[key] = val;
		return true;
	}
	bool GetEtag(const std::string &key,  std::string *val)//ͨ���ļ�����ȡԭ��etag��Ϣ
	{
		auto it = _backup_list.find(key);
		if (it == _backup_list.end())
		{
			return false;
		}
		*val = it->second;
		return true;
	}
	bool Storage()//�־û��洢
	{
		std::stringstream tmp;//ʵ����һ��string������
		
		auto it = _backup_list.begin();
		for (; it != _backup_list.end(); it++)
		{
			tmp << it->first << " " << it->second << "\r\n";
		}
		
		FileUtil::Write(_store_file, tmp.str());
		return true;
		return true;
	}
	bool InitLoad()//��ʼ������ԭ������
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
	std::string _store_file;//�־û��洢�ļ�����
	std::unordered_map < std::string, std::string> _backup_list;//���ݵ��ļ���Ϣ
};


class CloudClient//Ŀ¼���
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
				std::string name = list[i]; //���ļ���
				std::string pathname = LISTEN_DIR + name;
				std::cout << pathname << "is need to backup" << std::endl;
				std::string body;
				FileUtil::Read(pathname, &body);
				httplib::Client client(_srv_ip, _srv_port); //ʵ����client����׼������http�ϴ��ļ�����
				std::string req_path = "/" + name;
				auto rsp = client.Put(req_path.c_str(), body, "appliction/octet-stream");
				if (rsp == NULL || rsp->status != 200)
				{
					//�ļ��ϴ�����ʧ����
					std::cout << pathname << " backup failed" << std::endl;
					continue;
				}
				std::string etag;
				GetEtag(pathname, &etag);
				data_manage.Insert(name, etag);//���ݳɹ���������Ϣ
				std::cout << pathname << " backup success" << std::endl;
			}
			Sleep(1000); //����1000ms

		}
	
		return true;
	}
	bool GetBackupFileList(std::vector<std::string> *list)//��ȡ��Ҫ�����ļ��б�
	{
		if (boost::filesystem::exists(_listen_dir) == false)
		{
			boost::filesystem::create_directory(_listen_dir);//Ŀ¼�����ھʹ���
		}
		/*1.��ȡĿ¼���ļ�����
		2.�����ļ�etag
		3.��ԭ�е�etag���бȶԣ�û���ҵ����߲���Ⱦͽ��б��ݣ�������Ȳ��ñ���*/
		boost::filesystem::directory_iterator begin(_listen_dir);
		boost::filesystem::directory_iterator end;
		for (; begin != end; begin++)
		{
			if (boost::filesystem::is_directory(begin->status()))
			{
				//Ŀ¼�����б��ݣ������Ǽ򵥵Ĵ���
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
				list->push_back(name);//��ͬ����б���
			}
		}
		return true;
	}
	bool GetEtag(const std::string &pathname, std::string *etag)//�����ļ���etag��Ϣ
	{
		//etag �ļ���С���ļ����һ���޸�ʱ��
		int64_t fsize = boost::filesystem::file_size(pathname);
		time_t mtime = boost::filesystem::last_write_time(pathname);
		*etag = std::to_string(fsize) + "-" + std::to_string(mtime);
		return true;
	}
private:
	std::string _srv_ip;
	uint16_t _srv_port;
	std::string _listen_dir;//��ص�Ŀ¼����
	DataManager data_manage;
};

