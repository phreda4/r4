# Copyright (C) 2010 The Android Open Source Project
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
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := fbtest
LOCAL_SRC_FILES := graf.c r4android.c
LOCAL_LDLIBS    := -lm -landroid 
#LOCAL_LDLIBS    := -lm -llog -landroid 
LOCAL_STATIC_LIBRARIES := android_native_app_glue 
LOCAL_ARM_MODE := arm 
#LOCAL_CFLAGS += -O2 -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp
#LOCAL_CFLAGS += -O2 -mfpu=neon -mfloat-abi=softfp
LOCAL_CFLAGS += -Ofast
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
	