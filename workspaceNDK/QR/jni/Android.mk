LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# OpenCV
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
include /home/costin/Android/adt-bundle-linux-x86_64-20131030/OpenCV-2.4.8-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := QR
LOCAL_SRC_FILES := QR.cpp

include $(BUILD_SHARED_LIBRARY)
