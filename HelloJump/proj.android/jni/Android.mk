LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
	$(shell cd $(LOCAL_PATH) && ls ../../Classes/*.cpp) \
	$(shell cd $(LOCAL_PATH) && ls ../../../shared/utils/*.cpp)

LOCAL_CPPFLAGS += -DHAS_TEXTURE_PACKED

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
	$(LOCAL_PATH)/../../../shared/utils \
	$(COCOS2DX_ROOT)/cocos2dx/  \
	$(COCOS2DX_ROOT)/cocos2dx/include  \
	$(COCOS2DX_ROOT)/cocos2dx/kazmath/include  \
	$(COCOS2DX_ROOT)/cocos2dx/platform/android \
	$(COCOS2DX_ROOT)/CocosDenshion/include

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
