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
#

include $(CLEAR_VARS)
TARGET_ABI      := android-4-armeabi 

LIBZIP_PATH = libzip/

LOCAL_CFLAGS := \
	-g3 \
	-ggdb \
	-DANDROID_NDK \
	-gstabs+ \

LOCAL_MODULE    := libzip
LOCAL_SRC_FILES :=\
	$(LIBZIP_PATH)/zip_add.c \
	$(LIBZIP_PATH)/zip_add_dir.c \
	$(LIBZIP_PATH)/zip_close.c \
	$(LIBZIP_PATH)/zip_delete.c \
	$(LIBZIP_PATH)/zip_dirent.c \
	$(LIBZIP_PATH)/zip_entry_free.c \
	$(LIBZIP_PATH)/zip_entry_new.c \
	$(LIBZIP_PATH)/zip_err_str.c \
	$(LIBZIP_PATH)/zip_error.c \
	$(LIBZIP_PATH)/zip_error_clear.c \
	$(LIBZIP_PATH)/zip_error_get.c \
	$(LIBZIP_PATH)/zip_error_get_sys_type.c \
	$(LIBZIP_PATH)/zip_error_strerror.c \
	$(LIBZIP_PATH)/zip_error_to_str.c \
	$(LIBZIP_PATH)/zip_fclose.c \
	$(LIBZIP_PATH)/zip_file_error_clear.c \
	$(LIBZIP_PATH)/zip_file_error_get.c \
	$(LIBZIP_PATH)/zip_file_get_offset.c \
	$(LIBZIP_PATH)/zip_file_strerror.c \
	$(LIBZIP_PATH)/zip_filerange_crc.c \
	$(LIBZIP_PATH)/zip_fopen.c \
	$(LIBZIP_PATH)/zip_fopen_index.c \
	$(LIBZIP_PATH)/zip_fread.c \
	$(LIBZIP_PATH)/zip_free.c \
	$(LIBZIP_PATH)/zip_get_archive_comment.c \
	$(LIBZIP_PATH)/zip_get_archive_flag.c \
	$(LIBZIP_PATH)/zip_get_file_comment.c \
	$(LIBZIP_PATH)/zip_get_num_files.c \
	$(LIBZIP_PATH)/zip_get_name.c \
	$(LIBZIP_PATH)/zip_memdup.c \
	$(LIBZIP_PATH)/zip_name_locate.c \
	$(LIBZIP_PATH)/zip_new.c \
	$(LIBZIP_PATH)/zip_open.c \
	$(LIBZIP_PATH)/zip_rename.c \
	$(LIBZIP_PATH)/zip_replace.c \
	$(LIBZIP_PATH)/zip_set_archive_comment.c \
	$(LIBZIP_PATH)/zip_set_archive_flag.c \
	$(LIBZIP_PATH)/zip_set_file_comment.c \
	$(LIBZIP_PATH)/zip_source_buffer.c \
	$(LIBZIP_PATH)/zip_source_file.c \
	$(LIBZIP_PATH)/zip_source_filep.c \
	$(LIBZIP_PATH)/zip_source_free.c \
	$(LIBZIP_PATH)/zip_source_function.c \
	$(LIBZIP_PATH)/zip_source_zip.c \
	$(LIBZIP_PATH)/zip_set_name.c \
	$(LIBZIP_PATH)/zip_stat.c \
	$(LIBZIP_PATH)/zip_stat_index.c \
	$(LIBZIP_PATH)/zip_stat_init.c \
	$(LIBZIP_PATH)/zip_strerror.c \
	$(LIBZIP_PATH)/zip_unchange.c \
	$(LIBZIP_PATH)/zip_unchange_all.c \
	$(LIBZIP_PATH)/zip_unchange_archive.c \
	$(LIBZIP_PATH)/zip_unchange_data.c

LOCAL_LDLIBS := -lz

include $(BUILD_STATIC_LIBRARY)
