#include "httplib.h"

void helloworld(const httplib::Request &req , httplib::Response &rsp)
{
    //rsp.status 状态码   rsp.headers 头部信息  rsp.body 正文
    //rsp.set_header(const char *key , const char *val)
    std::cout << "method:" << req.method << std::endl;
    std::cout << "path" << req.path << std::endl;
    std::cout<< "body" << req.body << std::endl;


    rsp.status = 200;
    rsp.body = "<html><body><h1>helloworld<h1><body></html>";
    rsp.set_header("Content-Type" , "text/html");
    rsp.set_header("Content-Length" , std::to_string(rsp.body.size()));
    return ;
}
int main()
{
    httplib::Server server;
    server.Get("/" , helloworld);

    server.listen("0.0.0.0",9000); //监听本机的所有网卡

    return 0;
}
