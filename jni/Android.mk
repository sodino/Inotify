LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Inotify
LOCAL_SRC_FILES := Inotify.cpp

LOCAL_LDLIBS    := -lm -llog 

include $(BUILD_SHARED_LIBRARY)
