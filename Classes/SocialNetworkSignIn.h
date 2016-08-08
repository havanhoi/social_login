#ifndef __SocialNetworkSignIn__
#define __SocialNetworkSignIn__
#include "cocos2d.h"
#define SOCIAL_NETWORK SocialNetworkSignIn::getInstance()

class SocialNetworkSignIn{
public:
    SocialNetworkSignIn();
    static SocialNetworkSignIn *getInstance();
    static void onGooglePlusSignIn();
    static void onGooglePlusSignOut();
    
    static void onFBSignIn();
    static void onFBSignOut();
};

#endif