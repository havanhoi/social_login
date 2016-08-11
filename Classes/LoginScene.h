#ifndef __LoginScene_SCENE_H__
#define __LoginScene_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class LoginScene : public cocos2d::Layer

{
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(LoginScene);

    // Button callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuCloseCallback_Gmail(cocos2d::Ref* pSender);
    void menuCloseCallback_LogOut(cocos2d::Ref* pSender);
    
    
    //call back delegate
    void didSignInFacebook(cocos2d::ValueMap infoFB);
    void didSignInGmail(cocos2d::ValueMap infoGmail);
    void didSocialSignOut();
    
    cocos2d::ValueMap infoUser;
private:
    void onEnter();
};

#endif // __LoginScene_SCENE_H__
