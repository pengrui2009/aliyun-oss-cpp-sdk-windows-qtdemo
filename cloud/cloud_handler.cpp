#include "cloud_handler.h"

//CloudData *CloudData::_instance = 0;
//std::string CloudData::AccessKeyId="";
//std::string CloudData::AccessKeySecret="";
//std::string CloudData::Endpoint="";
//std::string CloudData::BucketName="";

CloudData::CloudData(std::string access_keyid, std::string access_keysecret,
                     std::string endpoint, std::string bucketname) :
    AccessKeyId(access_keyid),
    AccessKeySecret(access_keysecret),
    Endpoint(endpoint),
    BucketName(bucketname)
{
    handle_ptr = new ALIBABACLOUD_HANDLE::alibabacloud_handle(AccessKeyId, AccessKeySecret, Endpoint, BucketName);
}

int CloudData::get_download_percent()
{
    return handle_ptr->get_download_percent();
}
// desc: 上传文件
// param: 参数一/阿里云上的路径及要保存的文件名 参数二/本地路径
// return: 成功返回true，失败返回false
bool CloudData::upload_files(const std::string &target_path,const std::string &local_path)
{
    return handle_ptr->upload_files(target_path, local_path);
}

// desc: 查询阿里云某路径下的文件列表
// param: 参数一/阿里云上的路径 参数二/文件列表
// return: 成功返回true，失败返回false
bool CloudData::query_directory(const std::string &target_directory, std::vector<file_detail_st> &details)
{
    return handle_ptr->query_directory(target_directory, details);
}

// desc: 下载文件到本地路径下
// param: 参数一/阿里云上的路径及要保存的文件名 参数二/本地路径
// return: 成功返回true，失败返回false
bool CloudData::download_files(const std::string &target_directory, const std::string &local_path)
{
    return handle_ptr->download_files(target_directory, local_path);
}

// desc: 下载文件到内存中
// param: 参数一/阿里云上的路径及要保存的文件名 参数二/保存的数据 参数三/数据的字节数
// return: 成功返回true，失败返回false
bool CloudData::download_files_to_memory(const std::string &target_directory, char **data_ptr, int64_t &data_len)
{
    return handle_ptr->download_files_to_memory(target_directory, data_ptr, data_len);
}

// desc: 下载文件到内存中
// param: 参数一/阿里云上的路径及要保存的文件名 参数二/保存数据的字符串
// return: 成功返回true，失败返回false
bool CloudData::download_files_to_memory(const std::string &target_directory, std::string &content)
{
    return handle_ptr->download_files_to_memory(target_directory, content);
}
