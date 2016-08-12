#include "CppBridge.h"
#include "LoginScene.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_CppBridge_onDidSocialSignIn(JNIEnv* env, jobject thiz, jstring personName, jstring personEmail, jstring personId, jint index)
{
    // your C++ code goes here
    const char * native_nameStr = env->GetStringUTFChars(personName, JNI_FALSE);
    std::string nameStr(native_nameStr);
    
    const char * native_emailStr = env->GetStringUTFChars(personEmail, JNI_FALSE);
    std::string emailStr(native_emailStr);
    
    const char * native_idStr = env->GetStringUTFChars(personId, JNI_FALSE);
    std::string idStr(native_idStr);
    
    cocos2d::ValueMap userInfo;
    if (nameStr != "") {
        userInfo["name"] = nameStr;
    }
    if (idStr != "") {
        userInfo["id"] = std::string(idStr);
        
    }
    if (emailStr != "") {
        userInfo["email"] = emailStr;
        if (userInfo["email"].isNull()) {
            userInfo["email"] = userInfo["id"];
        }
    }
    auto _loginScene = dynamic_cast<LoginScene *>(Director::getInstance()->getRunningScene()->getChildByTag(183));
    _loginScene->didSignInSocial(userInfo, index);
    
    env->ReleaseStringUTFChars(personName, native_nameStr);
    env->ReleaseStringUTFChars(personEmail, native_emailStr);
    env->ReleaseStringUTFChars(personId, native_idStr);
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_CppBridge_onDidSocialSignOut(JNIEnv* env, jobject thiz){
    auto _loginScene = dynamic_cast<LoginScene *>(Director::getInstance()->getRunningScene()->getChildByTag(183));
    _loginScene->didSocialSignOut();
}

#endif