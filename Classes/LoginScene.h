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
    void menuCloseCallback_Twitter(cocos2d::Ref* pSender);
    
    
    //call back delegate
    void didLoginFacebook(cocos2d::ValueMap infoFB);
    void didLoginGmail(cocos2d::ValueMap infoGmail);
    void didLoginTwitter(cocos2d::ValueMap infoTW);
    
    cocos2d::ValueMap infoUser;
    void loginFacebook();
    void logoutFacebook();
private:
    void onEnter();
};

#endif // __LoginScene_SCENE_H__
