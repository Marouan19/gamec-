#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "soundScene.h"//pour pouvoir switcher vers sound
USING_NS_CC;

Scene* soundScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = soundScene::create();

    scene->addChild(layer);

    return scene;
}

bool soundScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto  origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();


/////////////////////////////////////////////////////////////////////////

    menuback = Sprite::create("soundbackground.png");
    menuback->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    menuback->setScale(0.125);



    this->addChild(menuback);
    auto* menu = Menu::create();
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    auto sound_button = Sprite::create("soundon.png");
    auto sound_button_selected = Sprite::create("soundon.png");
    MenuItemImage* menu_sound = MenuItemImage::create();
    menu_sound->setNormalImage(sound_button);
    menu_sound->setSelectedImage(sound_button_selected);
    menu_sound->setCallback(CC_CALLBACK_1(soundScene::sound2,this));

    menu->addChild(menu_sound, 4);

    menu_sound->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) ));



    auto Music_button = Sprite::create("mute.png");
    auto Music_button_selected = Sprite::create("mute.png");
    MenuItemImage* menu_Music = MenuItemImage::create();
    menu_Music->setNormalImage(Music_button);
    menu_Music->setSelectedImage(Music_button_selected);
    menu_Music->setCallback(CC_CALLBACK_1(soundScene::music, this));

    menu->addChild(menu_Music, 4);

    menu_Music->setPosition(Point((visibleSize.width / 2)-120, (visibleSize.height / 2)));


    auto goback_button = Sprite::create("menu.png");
    auto goback_button_selected = Sprite::create("menu.png");
    MenuItemImage* menu_goback = MenuItemImage::create();
    menu_goback->setNormalImage(goback_button);
    menu_goback->setSelectedImage(goback_button_selected);
    menu_goback->setCallback(CC_CALLBACK_1(soundScene::goback, this));

    menu->addChild(menu_goback, 4);

    menu_goback->setPosition(Point((visibleSize.width / 2) +120, (visibleSize.height / 2)));


    return true;
}

    void soundScene::goback(cocos2d::Ref* pSender) 
    {
        CCLOG("GOBACK"); //affichage de play 
        //fct en cliquant sur play, on switch vers   
          Director::getInstance()->popScene();
    }
    
    void soundScene::music(cocos2d::Ref* pSender)
    {
        CCLOG("MUSIC"); //affichage de play 
        //fct en cliquant sur play, on switch vers   
        cocos2d::AudioEngine::stopAll();
    }
    void soundScene::sound2(cocos2d::Ref* pSender)
    {
        CCLOG("SOUND2"); //affichage de play 
        //fct en cliquant sur play, on switch vers   
        cocos2d::AudioEngine::preload("music.mp3"); //upload de notre music mp3 en v4 de cocos
        cocos2d::AudioEngine::play2d("music.mp3", true);    //PLAY MUSIC //true whwnever t7lat hello world

    }

