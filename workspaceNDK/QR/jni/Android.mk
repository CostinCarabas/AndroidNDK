LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# OpenCV
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
include ../OpenCV-2.4.8-android-sdk/sdk/native/jni/OpenCV.mk
#/home/costin/Android/adt-bundle-linux-x86_64-20131030

LOCAL_MODULE    := QR
LOCAL_SRC_FILES := QR.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS     += -llog -ldl

LOCAL_MODULE     := detection_based_tracker

include $(BUILD_SHARED_LIBRARY)
