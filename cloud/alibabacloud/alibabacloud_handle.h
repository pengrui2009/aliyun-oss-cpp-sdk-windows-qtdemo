#pragma once

#include <string>
#include <stdio.h>
#include <alibabacloud/oss/OssClient.h>
#include <memory>
#include <fstream>
#include <iostream>
using namespace AlibabaCloud::OSS;

namespace ALIBABACLOUD_HANDLE{

struct file_detail_st
{
    std::string name;
    std::string size;
    std::string date;
};

class alibabacloud_handle{
public:
    // desc: 构造函数用于初始化OSS账号信息以及初始化sdk
	// param: 参数一/AccessKeyId 参数二/AccessKeySecret 参数三/Endpoint 参数四/BucketName 
	// return: NULL
    alibabacloud_handle(const std::string &,const std::string &,const std::string &,const std::string &);

    // desc: 关闭sdk
	// param: NULL 
	// return: NULL
    ~alibabacloud_handle();
    
    int get_download_percent() {return download_percent;}
    // desc: 上传文件
	// param: 参数一/阿里云上的路径及要保存的文件名 参数二/本地路径 
	// return: 成功返回true，失败返回false
    bool upload_files(const std::string &,const std::string &);

    // desc: 查询阿里云某路径下的文件列表
    // param: 参数一/阿里云上的路径 参数二/文件列表
	// return: 成功返回true，失败返回false
    bool query_directory(const std::string &, std::vector<file_detail_st> &);

    // desc: 下载文件到本地路径下
	// param: 参数一/阿里云上的路径及要保存的文件名 参数二/本地路径
	// return: 成功返回true，失败返回false
    bool download_files(const std::string &,const std::string &);

    // desc: 下载文件到内存中
	// param: 参数一/阿里云上的路径及要保存的文件名 参数二/保存数据的字符串
	// return: 成功返回true，失败返回false
    bool download_files_to_memory(const std::string &, char **data_ptr, int64_t &data_len);

    bool download_files_to_memory(const std::string &, std::string &);

    // desc: 进度条显示
	// param: transfered/已完成的大小 total/总大小 
	// return: NULL
    void ProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData) const;

public:
    int status;

private:
    //OSS 通过使用 AccessKeyId 和 AccessKeySecret 对称加密的方法来验证某个请求的发送者身份。AccessKeyId 用于标识用户；AccessKeySecret 是用户用于加密签名字符串和 OSS 用来验证签名字符串的密钥，必须保密。
    std::string AccessKeyId;
    std::string AccessKeySecret;
    std::string Endpoint;       //OSS对外服务的访问域名
    std::string BucketName;     //存储空间名
    ClientConfiguration conf;
    OssClient *oss_client;
    TransferProgress progressCallback;
    const char lable[5] = {'|','/','-','\\','\\'};

    //Download Percent
    int download_percent;
};
}

