#include "LoginScene.h"
#include "SocialNetworkSignIn.h"
#include "JsonDump.h"
USING_NS_CC;
using namespace std;
Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->setTag(183);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "fonts/CloseNormal.png",
                                           "fonts/CloseSelected.png",
                                           CC_CALLBACK_1(LoginScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(visibleSize.width*0.25,visibleSize.height *0.2));
    closeItem->setScale(2.0);
    
    
    auto closeItem_1 = MenuItemImage::create("fonts/CloseNormal.png","fonts/CloseSelected.png",CC_CALLBACK_1(LoginScene::menuCloseCallback_Gmail, this));
    
    closeItem_1->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height *0.2));
    closeItem_1->setScale(2.0);
    
    CCLOG("deck = %f",visibleSize.width);
    
    auto closeItem_2 = MenuItemImage::create("fonts/CloseNormal.png",
                                             "fonts/CloseSelected.png",
                                             CC_CALLBACK_1(LoginScene::menuCloseCallback_LogOut, this));
    
    closeItem_2->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height *0.2));
    closeItem_2->setScale(2.0);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, closeItem_1,closeItem_2, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF(cocos2d::StringUtils::format("%s", "Social Network"), "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2,
                            visibleSize.height - label->getContentSize().height));
    if (label->getBoundingBox().size.width > visibleSize.width) {
        label->setScale(0.5);
    }
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    

    
    return true;
}
void LoginScene::onEnter(){
    Layer::onEnter();
}

void LoginScene::menuCloseCallback(Ref* pSender)
{
    SOCIAL_NETWORK->onFBSignIn();
}

void LoginScene::menuCloseCallback_Gmail(Ref* pSender)
{
    SOCIAL_NETWORK->onGoogleSignIn();
}


void LoginScene::menuCloseCallback_LogOut(Ref* pSender)
{
    SOCIAL_NETWORK->onFBSignOut();
    SOCIAL_NETWORK->onGoogleSignOut();
}

void LoginScene::didSignInFacebook(cocos2d::ValueMap infoFB){
    infoUser.clear();
    infoUser = infoFB;
    CCLOG("______________USERNAME FACEBOOK______________");
    CCLOG("name: %s", infoUser["name"].asString().c_str());
    CCLOG("id: %s", infoUser["id"].asString().c_str());
    CCLOG("email: %s", infoUser["email"].asString().c_str());
    CCLOG("_____________________________________________");
}

void LoginScene::didSignInGmail(cocos2d::ValueMap infoGmail){
    infoUser.clear();
    infoUser = infoGmail;
    CCLOG("______________USERNAME GMAIL_________________");
    CCLOG("name: %s", infoUser["name"].asString().c_str());
    CCLOG("id: %s", infoUser["id"].asString().c_str());
    CCLOG("email: %s", infoUser["email"].asString().c_str());
    CCLOG("_____________________________________________");
}
