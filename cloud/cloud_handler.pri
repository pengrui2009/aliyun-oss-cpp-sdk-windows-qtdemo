INCLUDEPATH += $$PWD/alibabacloud
INCLUDEPATH += $$PWD/alibabacloud/include



win32 {
    LIBS += -lalibabacloud-oss-cpp-sdk -L$$PWD/library/windows/alibabacloud/
    LIBS += -lcurl -L$$PWD/library/windows/alibabacloud/
    LIBS += -leay32 -L$$PWD/library/windows/alibabacloud/
    LIBS += -lssleay32 -L$$PWD/library/windows/alibabacloud/
    LIBS += -lzlibwapi -L$$PWD/library/windows/alibabacloud/
}
unix {
    LIBS += -lalibabacloud-oss-cpp-sdk -L$$PWD/library/linux/alibabacloud/
    LIBS += -lcurl
    LIBS += -lpthread
    LIBS += -lssl
    LIBS += -lcrypto
}



SOURCES     += $$PWD/alibabacloud/alibabacloud_handle.cpp
SOURCES     += $$PWD/cloud_handler.cpp

HEADERS     += $$PWD/alibabacloud/alibabacloud_handle.h
HEADERS     += $$PWD/cloud_handler.h
