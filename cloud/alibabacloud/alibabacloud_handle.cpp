#include "alibabacloud_handle.h"
#include <unistd.h>
#include <string.h>
namespace ALIBABACLOUD_HANDLE{

alibabacloud_handle::alibabacloud_handle(const std::string &AccessKeyId,const std::string &AccessKeySecret,const std::string &Endpoint,const std::string &BucketName):AccessKeyId(AccessKeyId),AccessKeySecret(AccessKeySecret),Endpoint(Endpoint),BucketName(BucketName)
{

    InitializeSdk();

    /* 设置连接池数，默认为16个 */
    conf.maxConnections = 20;

    /* 设置请求超时时间，超时没有收到数据就关闭连接，默认为10000ms */
    conf.requestTimeoutMs = 8000;

    /* 设置建立连接的超时时间，默认为5000ms */
    conf.connectTimeoutMs = 8000;

    oss_client = new OssClient(Endpoint, AccessKeyId, AccessKeySecret, conf);
    if(oss_client == nullptr){
        status = -1;
        return;
    }else{
		status = 1;
	}

    auto callback = std::bind(&alibabacloud_handle::ProgressCallback,this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3,
        std::placeholders::_4
    );
    progressCallback = {  callback , this };

}

alibabacloud_handle::~alibabacloud_handle(){
    ShutdownSdk();
}

bool alibabacloud_handle:: upload_files(const std::string &target_path, const std::string &local_path){

    std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(local_path.c_str(), std::ios::in|std::ios::binary);
    PutObjectRequest request(BucketName, target_path, content);

    request.setTransferProgress(progressCallback);
    auto outcome = oss_client->PutObject(request);

    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "PutObject fail" <<
        ",code:" << outcome.error().Code() <<
        ",message:" << outcome.error().Message() <<
        ",requestId:" << outcome.error().RequestId() << std::endl;
        return false;
    }
    return true;
}


bool alibabacloud_handle::query_directory(const std::string &target_directory, std::vector<file_detail_st> &details){
    std::string nextMarker = "";

	ListObjectsRequest request1(BucketName);
	auto outcome = oss_client->ListObjects(request1);
    do {
        /* 列举文件 */
        ListObjectsRequest request(BucketName);
         /* 设置正斜线（/）为文件夹的分隔符 */
        request.setDelimiter("/");
        request.setPrefix(target_directory);
        request.setMarker(nextMarker);
        outcome = oss_client->ListObjects(request);

        if (!outcome.isSuccess ()) {    
            /* 异常处理 */
            std::cout << "ListObjects fail" <<
            ",code:" << outcome.error().Code() <<
            ",message:" << outcome.error().Message() <<
            ",requestId:" << outcome.error().RequestId() << std::endl;
            return false;
        }  
        for (const auto& object : outcome.result().ObjectSummarys()) {
            file_detail_st detail;
//            std::cout << "object"<<
//            ",name:" << object.Key() <<
//            " ,size:" << object.Size() <<
//            " ,lastmodify time:" << object.LastModified() << std::endl;
            detail.name = object.Key();
            detail.size = std::to_string(object.Size());
            detail.date = object.LastModified();
            details.push_back(detail);
        }
//        for (const auto& commonPrefix : outcome.result().CommonPrefixes()) {
//            std::cout << "commonPrefix" << ",name:" << commonPrefix << std::endl;
//        }
        nextMarker = outcome.result().NextMarker();
    } while (outcome.result().IsTruncated());


    return true;
}

bool alibabacloud_handle::download_files(const std::string &target_directory,const std::string &local_directory){

    DownloadObjectRequest request(BucketName, target_directory, local_directory);
    request.setTransferProgress(progressCallback);

    auto outcome = oss_client->ResumableDownloadObject(request);
  
    if (!outcome.isSuccess()) {
        /* 异常处理 */
        std::cout << "ResumableDownloadObject fail" <<
        ",code:" << outcome.error().Code() <<
        ",message:" << outcome.error().Message() <<
        ",requestId:" << outcome.error().RequestId() << std::endl;
        return false;
    }else{
        return true;
    }
    
}


void alibabacloud_handle::ProgressCallback(size_t increment, int64_t transfered, int64_t total, void* userData) const
{
    if (increment)
    {

    }
    alibabacloud_handle *handle_ptr = static_cast<alibabacloud_handle *>(userData);
    int i = static_cast<int>((transfered*1.0/total*1.0) *100);
//    printf("[%d%%][%c]\r", i , lable[i % 4]);
//    fflush(stdout);
    handle_ptr->download_percent = i;
}


bool alibabacloud_handle::download_files_to_memory(const std::string &target_directory, std::string &content){
//    std::string strcontent;
    GetObjectRequest request(BucketName, target_directory);

    request.setTransferProgress(progressCallback);

    auto outcome = oss_client->GetObject(request);
    if (outcome.isSuccess()) {

//        *data_ptr = new char[outcome.result().Metadata().ContentLength()];
//        std::cout << "getObjectToBuffer" << " success, Content-Length:" << outcome.result().Metadata().ContentLength() << std::endl;
        //*(outcome.result().Content()) >> buf;

//        (*(outcome.result().Content())).read(*data_ptr, outcome.result().Metadata().ContentLength());
        getline(*(outcome.result().Content()), content, '\0');
    }
    else {
        /*异常处理*/

        std::cout << "getObjectToBuffer fail" <<
        "target_directory:" << target_directory <<
        ",code:" << outcome.error().Code() <<
        ",message:" << outcome.error().Message() <<
        ",requestId:" << outcome.error().RequestId() << std::endl;
        return false;
    }
    return true;
}

bool alibabacloud_handle::download_files_to_memory(const std::string &target_directory, char **data_ptr, int64_t &data_len){
//    std::string strcontent;
    GetObjectRequest request(BucketName, target_directory);

    request.setTransferProgress(progressCallback);

    auto outcome = oss_client->GetObject(request);
    if (outcome.isSuccess()) { 

        *data_ptr = new char[outcome.result().Metadata().ContentLength()];
//        std::cout << "getObjectToBuffer" << " success, Content-Length:" << outcome.result().Metadata().ContentLength() << std::endl;
        //*(outcome.result().Content()) >> buf;

        data_len = outcome.result().Metadata().ContentLength();
        (*(outcome.result().Content())).read(*data_ptr, outcome.result().Metadata().ContentLength());
//        getline(*(outcome.result().Content()), buf, '\0');
    }
    else {
        /*异常处理*/
        std::cout << "getObjectToBuffer fail" <<
        "target_directory:" << target_directory <<
        ",code:" << outcome.error().Code() <<
        ",message:" << outcome.error().Message() <<
        ",requestId:" << outcome.error().RequestId() << std::endl;
        return false;
    }
    return true;
}
}

