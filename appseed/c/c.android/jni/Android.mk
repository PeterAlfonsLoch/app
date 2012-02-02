LOCAL_PATH := ../..

include $(CLEAR_VARS)

LOCAL_MODULE    := c
### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := *.cpp *.c _/*.c _/*.cpp bsdiff/*.c bsdiff/*.cpp hotplugin/*.cpp linux/*.cpp spa/*.cpp

include $(BUILD_SHARED_LIBRARY)
