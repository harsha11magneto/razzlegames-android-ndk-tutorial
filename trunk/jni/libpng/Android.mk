# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LIBPNG_PATH := libpng/
include $(CLEAR_VARS)

LOCAL_CFLAGS := \
								-g3 \
								-ggdb \
								-gstabs+ \
								-DANDROID_NDK \

LOCAL_MODULE    := libpng
LOCAL_SRC_FILES :=\
	$(LIBPNG_PATH)png.c \
	$(LIBPNG_PATH)pngerror.c \
	$(LIBPNG_PATH)pngget.c \
	$(LIBPNG_PATH)pngmem.c \
	$(LIBPNG_PATH)pngpread.c \
	$(LIBPNG_PATH)pngread.c \
	$(LIBPNG_PATH)pngrio.c \
	$(LIBPNG_PATH)pngrtran.c \
	$(LIBPNG_PATH)pngrutil.c \
	$(LIBPNG_PATH)pngset.c \
	$(LIBPNG_PATH)pngtrans.c \
	$(LIBPNG_PATH)pngwio.c \
	$(LIBPNG_PATH)pngwrite.c \
	$(LIBPNG_PATH)pngwtran.c \
	$(LIBPNG_PATH)pngwutil.c 

	
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
