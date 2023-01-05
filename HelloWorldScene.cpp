#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "SCENE1.h" //pour pouvoir switcher vers
#include "SCENE2.h"
#include "AudioEngine.h" //biblio pour importer les audioa
#include "soundScene.h"//pour pouvoir switcher vers sound
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) {
        return false;
    }
    auto  origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
   
/////////////////////////////////////////////////////////////////////////



    menuback = Sprite::create("menubackground.png");
    menuback->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    menuback->setScale(0.125);

    //  menuback->setAnchorPoint(Vec2(0, 0));
      //menuback->setPosition(Vec2(0, 0));
    this->addChild(menuback);
    auto* menu = Menu::create();
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    ///////////////////////////
    ///ajout des elements:


 //   auto menu_play = MenuItemImage::create(); //boutton play
    auto start_button = Sprite::create("newgame.png");
    auto start_button_selected = Sprite::create("newgame.png");
    MenuItemImage* menu_play = MenuItemImage::create();
    menu_play->setNormalImage(start_button);
    menu_play->setSelectedImage(start_button_selected);
    menu_play->setCallback(CC_CALLBACK_1(HelloWorld::play, this));


    menu->addChild(menu_play,4);

    auto sound_button = Sprite::create("options.png");
    auto sound_button_selected = Sprite::create("options.png");
    MenuItemImage* sound_play = MenuItemImage::create();
    sound_play->setNormalImage(sound_button);
    sound_play->setSelectedImage(sound_button_selected);
    sound_play->setCallback(CC_CALLBACK_1(HelloWorld::sound, this));


    menu->addChild(sound_play, 4);
    


    auto exit_button = Sprite::create("exit.png");
    auto exit_button_selected = Sprite::create("exit.png");
    MenuItemImage* menu_exit = MenuItemImage::create();
    menu_exit->setNormalImage(exit_button);
    menu_exit->setSelectedImage(exit_button_selected);
    menu_exit->setCallback(CC_CALLBACK_1(HelloWorld::exit, this));


    menu->addChild(menu_exit, 4);


    menu_play->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2)+50 ));
    sound_play->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2)));
    menu_exit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2)-50));

   //////////////////////////////////////////////////
    //upload music
    cocos2d::AudioEngine::stopAll();
    cocos2d::AudioEngine::preload("music.mp3"); //upload de notre music mp3 en v4 de cocos
    cocos2d::AudioEngine::play2d("music.mp3", true);    //PLAY MUSIC //true whwnever t7lat hello world


    return true;
}


//implemetation des fcts crees :

void HelloWorld::play(cocos2d::Ref* PSender) {
    CCLOG("PLAY"); //affichage de play 
    //fct en cliquant sur play, on switch vers scene 1    
    auto scene1 = SCENE1::createScene();
    Director::getInstance()->pushScene(TransitionSplitCols::create(1, scene1)); //la scene qu on veut y switch vers
}

void HelloWorld::sound(cocos2d::Ref* PSender) {
    CCLOG("SOUND"); //affichage de play 
    //fct en cliquant sur play, on switch vers scene 1    
    auto soundscene = soundScene::createScene();
    Director::getInstance()->pushScene(TransitionSplitCols::create(1, soundscene)); //la scene qu on veut y switch vers
}


void HelloWorld::exit(cocos2d::Ref* PSender) {
    CCLOG("exit"); //affichage de play 
    Director::getInstance()->popScene();

}
