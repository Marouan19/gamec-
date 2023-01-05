

#pragma once
#ifndef  _SOUND_SCENE_H_
#define  _SOUND_SCENE_H_
#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

class soundScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //a selector one
    void menuCloseCallback(cocos2d::Ref* pSender);


    CREATE_FUNC(soundScene);
    cocos2d::Sprite* menuback;
    cocos2d::Menu* menu1;
    //menu items
    void sound2(Ref* pSender);
    void music(Ref* pSender);
    void goback(Ref* pSender);


};



#endif

