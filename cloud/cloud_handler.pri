INCLUDEPATH += $$PWD/alibabacloud
INCLUDEPATH += $$PWD/alibabacloud/include



win32 {
    LIBS += -L$$PWD/library/windows/alibabacloud/ -lalibabacloud-oss-cpp-sdk
    LIBS += -L$$PWD/library/windows/alibabacloud/ -lcurl
    LIBS += -L$$PWD/library/windows/alibabacloud/ -leay32
    LIBS += -L$$PWD/library/windows/alibabacloud/ -lssleay32
    LIBS += -L$$PWD/library/windows/alibabacloud/ -lzlibwapi
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
