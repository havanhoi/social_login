#include "SocialNetworkSignIn.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "AppController.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
using namespace std;
USING_NS_CC;
static SocialNetworkSignIn *shareInstant = NULL;
SocialNetworkSignIn* SocialNetworkSignIn::getInstance(){
    if (shareInstant == NULL) {
        shareInstant = new SocialNetworkSignIn();
    }
    return shareInstant;
}
SocialNetworkSignIn::SocialNetworkSignIn(){}

void SocialNetworkSignIn::onGooglePlusSignIn(){
    [XAppDelegate onGooglePlusSignIn];
}
void SocialNetworkSignIn::onGooglePlusSignOut(){
    [XAppDelegate onGooglePlusSignOut];
}

void SocialNetworkSignIn::onFBSignIn(){
    [XAppDelegate onFBSignIn];
}

void SocialNetworkSignIn::onFBSignOut(){
    [XAppDelegate onFBSignOut];
}

#endif










