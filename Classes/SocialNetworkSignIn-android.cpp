#include "SocialNetworkSignIn.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
#include <jni.h>
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#endif
USING_NS_CC;
using namespace std;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
static SocialNetworkSignIn *shareInstant = NULL;
SocialNetworkSignIn* SocialNetworkSignIn::getInstance(){
    if (shareInstant == NULL) {
        shareInstant = new SocialNetworkSignIn();
    }
    return shareInstant;
}
SocialNetworkSignIn::SocialNetworkSignIn(){}

void SocialNetworkSignIn::onGoogleSignIn(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "onGoogleSignIn", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
void SocialNetworkSignIn::onGoogleSignOut(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "onGoogleSignOut", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

}

void SocialNetworkSignIn::onFBSignIn(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "onFacebookSignIn", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void SocialNetworkSignIn::onFBSignOut(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "onFacebookSignOut", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif






