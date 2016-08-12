#ifndef __BH_Minesweeper__CppBridge__
#define __BH_Minesweeper__CppBridge__

#include "cocos2d.h"
#include <string>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/jni/JniHelper.h"

extern "C"
{
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_CppBridge_onDidSocialSignIn(JNIEnv* env, jobject thiz, jstring personName, jstring personEmail, jstring personId, jint index);
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_CppBridge_onDidSocialSignOut(JNIEnv* env, jobject thiz);
};

#endif

#endif /* defined(__BH_Minesweeper__CppBridge__) */
