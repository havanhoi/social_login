#include "SocialNetworkSignIn.h"
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
SocialNetworkSignIn::SocialNetworkSignIn(){
}
void SocialNetworkSignIn::onGooglePlusSignIn(){
}
void SocialNetworkSignIn::onGooglePlusSignOut(){
}
void SocialNetworkSignIn::onTwitterSignIn(){
}
void SocialNetworkSignIn::onTwitterSignOut(){
}

#endif










