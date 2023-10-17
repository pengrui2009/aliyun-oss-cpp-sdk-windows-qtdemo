#ifndef CLOUDDATA_H
#define CLOUDDATA_H

#include <QMutexLocker>
#include "alibabacloud_handle.h"

using namespace ALIBABACLOUD_HANDLE;
class CloudData
{
public:
    CloudData(std::string access_keyid, std::string access_keysecret, std::string endpoint, std::string bucketname);

    ~CloudData()
    {
        std::cout << "CloudData destory" << std::endl;
    }

    CloudData(const CloudData&)=delete;
    CloudData& operator=(const CloudData&)=delete;
//    static CloudData *Instance() {
//        static QMutex mutex;
//        if (!_instance) {
//            QMutexLocker locker(&mutex);
//            if (!_instance) {
//                _instance = new CloudData;
//            }
//        }
//        return _instance;
//    }

    int get_download_percent();
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

public:
    std::string AccessKeyId;
    std::string AccessKeySecret;
    std::string Endpoint;
    std::string BucketName;
private:

    ALIBABACLOUD_HANDLE::alibabacloud_handle *handle_ptr;
//    static CloudData *_instance;
};

#endif // CLOUDDATA_H
