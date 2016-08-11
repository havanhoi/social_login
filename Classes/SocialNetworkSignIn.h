#ifndef __SocialNetworkSignIn__
#define __SocialNetworkSignIn__
#include "cocos2d.h"
#define SOCIAL_NETWORK SocialNetworkSignIn::getInstance()

class SocialNetworkSignIn{
    

public:
    SocialNetworkSignIn();
    static SocialNetworkSignIn *getInstance();
    static void onGoogleSignIn();
    static void onGoogleSignOut();
    
    static void onFBSignIn();
    static void onFBSignOut();
        
};
#endif