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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "loginAction", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}
void SocialNetworkSignIn::onGoogleSignOut(){
}

void SocialNetworkSignIn::onFBSignIn(){
}

void SocialNetworkSignIn::onFBSignOut(){
}

#endif










