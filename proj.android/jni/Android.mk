LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

BOOST_PATH:= F:/somecode/boost_1_57_0

LOCAL_MODULE := tcpconnection_static
LOCAL_MODULE_FILENAME := libtcpconnection

LOCAL_SRC_FILES := ../../TcpConnection/TcpConnection.cpp \
                   ../../TcpConnection/impl/TcpConnectionImpl.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../ \
                    $(BOOST_PATH)/

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../

LOCAL_EXPORT_CPPFLAGS := -frtti -fexceptions -fsigned-char -std=c++11
LOCAL_EXPORT_CPPFLAGS += -DBOOST_ERROR_CODE_HEADER_ONLY
LOCAL_EXPORT_CPPFLAGS += -DBOOST_SYSTEM_NO_DEPRECATED
LOCAL_EXPORT_CPPFLAGS += -DBOOST_SYSTEM_NO_LIB
LOCAL_EXPORT_CPPFLAGS += -DBOOST_DATE_TIME_NO_LIB
LOCAL_EXPORT_CPPFLAGS += -DBOOST_REGEX_NO_LIB 

LOCAL_EXPORT_CFLAGS += -DBOOST_ERROR_CODE_HEADER_ONLY
LOCAL_EXPORT_CFLAGS += -DBOOST_SYSTEM_NO_DEPRECATED
LOCAL_EXPORT_CFLAGS += -DBOOST_SYSTEM_NO_LIB
LOCAL_EXPORT_CFLAGS += -DBOOST_DATE_TIME_NO_LIB
LOCAL_EXPORT_CFLAGS += -DBOOST_REGEX_NO_LIB 

include $(BUILD_STATIC_LIBRARY)
#==============================================================

$(info ----------------- Compile libfoundationkit infomation -------------------)
$(info TARGET_ARCH     = $(TARGET_ARCH))
$(info TARGET_ARCH_ABI = $(TARGET_ARCH_ABI))
$(info TARGET_ABI      = $(TARGET_ABI))
$(info APP_ABI         = $(APP_ABI))
$(info --------------------------------------------------------------------------)

