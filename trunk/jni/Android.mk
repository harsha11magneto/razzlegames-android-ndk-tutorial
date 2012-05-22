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

#---------------------------------------------------------
# Nonsense, for some reason if I use a wildcard without local
#   path, it doesn't find the source files.
#     If I do it appends LOCAL_PATH to the prefix twice!
#---------------------------------------------------------
MY_PREFIX := $(LOCAL_PATH)/../
MY_LOCAL_SRC_FILES := \
	$(wildcard $(LOCAL_PATH)/*.cpp)

# This fixes the problem!
LOCAL_SRC_FILES := \
	$(subst jni/, , $(MY_LOCAL_SRC_FILES))

LOCAL_LDLIBS := -lGLESv1_CM -llog -lz 
LOCAL_STATIC_LIBRARIES := libBox2D libzip libpng

include $(BUILD_SHARED_LIBRARY)
