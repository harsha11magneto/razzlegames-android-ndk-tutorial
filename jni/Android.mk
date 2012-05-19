LOCAL_PATH := $(call my-dir)
MY_PATH := $(LOCAL_PATH)
TARGET_ABI      := android-4-armeabi 

#LOCAL_JNI_SHARED_LIBRARIES := \
#	libzip \
#	libpng \
#	libBox2D \

include $(call all-subdir-makefiles)

include $(CLEAR_VARS)
LOCAL_PATH := $(MY_PATH)

LOCAL_MODULE    := libmain
LOCAL_C_INCLUDES := \
										$(LOCAL_PATH)/Box2D \
										$(LOCAL_PATH)/libpng \
										$(LOCAL_PATH)/libzip \

LOCAL_CFLAGS := \
								-g3 \
								-ggdb \
								-gstabs+ \
								-DANDROID_NDK \

#-DDISABLE_IMPORTGL \

LOCAL_SRC_FILES := \
									 main.cpp \
									 utils.cpp \
									 Box2DTools.cpp \
									 Renderer.cpp \
									 GLHelpers.cpp \
									 AndroidJNIHelper.cpp \
									 Texture.cpp \
									 Sprite.cpp \

#importgl.c \

LOCAL_LDLIBS := -lGLESv1_CM -llog -lz 
LOCAL_STATIC_LIBRARIES := libBox2D libzip libpng

include $(BUILD_SHARED_LIBRARY)
