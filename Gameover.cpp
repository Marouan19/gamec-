#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "SCENE1.h"
#include "Gameover.h"

USING_NS_CC;

Scene* Gameover::createScene()
{
    auto scene = Scene::create();
    auto layer = Gameover::create();

    scene->addChild(layer);

    return scene;
}

bool Gameover::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto  origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    ///////////////// Background

    Gameover::gameover = Sprite::create("gameover.png");
    gameover->setPosition(Point((visibleSize.width / 2) , (visibleSize.height / 2)));
    gameover->setScale(0.125);
    this->addChild(gameover);

    auto* menu2 = Menu::create();
    menu2->setPosition(Point(0, 0));
    this->addChild(menu2 );


    ///try again exit
    auto tryagain_button = Sprite::create("newgame.png");
    auto tryagain_button_selected = Sprite::create("newgame.png");
    MenuItemImage* menu_tryagain = MenuItemImage::create();
    menu_tryagain->setNormalImage(tryagain_button);
    menu_tryagain->setSelectedImage(tryagain_button_selected);
    menu_tryagain->setCallback(CC_CALLBACK_1(Gameover::tryagain, this));


    menu2->addChild(menu_tryagain, 4);


    auto exit_button = Sprite::create("exit.png");
    auto exit_button_selected = Sprite::create("exit.png");
    MenuItemImage* menu_exit = MenuItemImage::create();
    menu_exit->setNormalImage(exit_button);
    menu_exit->setSelectedImage(exit_button_selected);
    menu_exit->setCallback(CC_CALLBACK_1(Gameover::exit, this));


    menu2->addChild(menu_exit, 4);


    menu_tryagain->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) + 50));
    menu_exit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2) - 30));

 /*
    cocos2d::AudioEngine::stopAll();

   cocos2d::AudioEngine::preload("gameover.mp3");
    cocos2d::AudioEngine::play2d("gameover.mp3", true); */  
    return true;
}
void Gameover::tryagain(cocos2d::Ref* PSender) {
    CCLOG("TRYAGAIN");  
    auto scene1 = SCENE1::createScene();
    Director::getInstance()->pushScene(TransitionSplitCols::create(1, scene1));
}
void Gameover::exit(cocos2d::Ref* PSender) {
    CCLOG("exit");
    auto scene1 = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionSplitCols::create(1, scene1));

}
