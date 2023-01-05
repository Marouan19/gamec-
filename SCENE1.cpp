#include "SCENE1.h"
#include "SCENE2.h"
#include "Gameover.h"
#include "AudioEngine.h"
#include "HelloWorldScene.h"
#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsJoint.h"

USING_NS_CC;

Scene* SCENE1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0, -300));

    // 'layer' is an autorelease object
    auto layer = SCENE1::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool SCENE1::init()
{
    if (!Layer::init()) {
        return false;
    }



    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();


    ////////////////   backround rectangle
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);





    auto background_rect = DrawNode::create();
    background_rect->drawSolidRect(origin, winSize, Color4F(1.0, 0.94, 0.87, 1.0)); //bg orange
    this->addChild(background_rect);
    this->setScale(1.001f);



    ///////////////////  add Sprite

    auto pinfo = AutoPolygon::generatePolygon("Pico_Player_blue.png");
    auto player = Sprite::create(pinfo);
    player->setAnchorPoint(Vec2(0.5f, 0.5f));
    player->setPosition(Vec2(50,60));
    player->setScale(0.3); //scale dyal player
    player->setName("player");
    this->addChild(player, 2);
    //  creating physique for player

    auto physicsBody1 = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(1000.0f, 0.5f, 0.5f));
    physicsBody1->setGravityEnable(true);
    physicsBody1->setDynamic(true);
    physicsBody1->setCollisionBitmask(1);
    physicsBody1->setCategoryBitmask(1);
    physicsBody1->setContactTestBitmask(1);
    physicsBody1->setTag(1);
    player->setPhysicsBody(physicsBody1);
 


    ///////////////////////////////////// creating the floor1(THe LAND)

    auto floor = Sprite::create("l2ard1.png");
    floor->setAnchorPoint(Vec2(0, 0));
    floor->setPosition(Vec2(0, 0));
    floor->setScale(0.125);
    this->addChild(floor, 1);

    //creating physique for THE FLOOR

    auto physicsBody_floor = PhysicsBody::createBox(floor->getContentSize(), PhysicsMaterial(1500.0f, 0.1f, 0.9f));

    physicsBody_floor->setDynamic(false);
    physicsBody_floor->setCollisionBitmask(1);
    physicsBody_floor->setCategoryBitmask(1);


    floor->setPhysicsBody(physicsBody_floor);



    ///////////////////////////////////// creating the floor2(THe LAND)

    auto floor2 = Sprite::create("l2ard.png");
    floor2->setAnchorPoint(Vec2(1, 0));
    floor2->setPosition(Vec2(480, 0));
    floor2->setScale(0.125);
    this->addChild(floor2, 1);

    //creating physique for THE FLOOR

    auto physicsBody_floor2 = PhysicsBody::createBox(floor2->getContentSize(), PhysicsMaterial(1500.0f, 0.1f, 0.9f));

    physicsBody_floor2->setDynamic(false);
    physicsBody_floor2->setCollisionBitmask(1);
    physicsBody_floor2->setCategoryBitmask(1);


    floor2->setPhysicsBody(physicsBody_floor2);



    //////////////////////////////////////  create obstacle1

    auto obstacle1 = Sprite::create("obstacle1.png");
    obstacle1->setAnchorPoint(Vec2(0, 0));
    obstacle1->setPosition(Vec2(170, 40));
    obstacle1->setScale(0.125);
    this->addChild(obstacle1, 1);

    auto physicsBody_obstacle1 = PhysicsBody::createBox(obstacle1->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));

    physicsBody_obstacle1->setDynamic(false);
    physicsBody_obstacle1->setCollisionBitmask(1);
    physicsBody_obstacle1->setCategoryBitmask(1);
    obstacle1->setPhysicsBody(physicsBody_obstacle1);
  


    //////////////////////////////
    auto obstacle2 = Sprite::create("obstacle1.png");
    obstacle2->setAnchorPoint(Vec2(0, 0));
    obstacle2->setPosition(Vec2(320, -77));
    obstacle2->setScale(0.240);
    this->addChild(obstacle2, 1);

    auto physicsBody_obstacle2 = PhysicsBody::createBox(obstacle2->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));

    physicsBody_obstacle2->setDynamic(false);
    physicsBody_obstacle2->setCollisionBitmask(5);
    physicsBody_obstacle2->setCategoryBitmask(5);
    obstacle2->setPhysicsBody(physicsBody_obstacle2);
    physicsBody_obstacle2->setContactTestBitmask(5);
    physicsBody_obstacle2->setTag(5);


    ////////////////////////////////////


     //////////////////////////////
    auto spriteBody = PhysicsBody::createBox(player->getContentSize(), PhysicsMaterial(0, 1, 0));
    spriteBody->setCollisionBitmask(1);
    spriteBody->setCollisionBitmask(true);
    // void reload(cocos2d::Ref* pSender);

    auto contactlistener = EventListenerPhysicsContact::create();
    contactlistener->onContactBegin = CC_CALLBACK_1(SCENE1::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactlistener, this);

    ////////////////////////////
    auto* menu = Menu::create();
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    ////////////////////////////

    auto goback_button = Sprite::create("menu.png");
    auto goback_button_selected = Sprite::create("menu.png");
    MenuItemImage* menu_goback = MenuItemImage::create();
    menu_goback->setNormalImage(goback_button);
    menu_goback->setSelectedImage(goback_button_selected);
    menu_goback->setCallback(CC_CALLBACK_1(SCENE1::goback, this));

    menu->addChild(menu_goback, 4);

    menu_goback->setPosition(Point((visibleSize.width / 2) + 220, (visibleSize.height / 2) + 140));








    auto* door1 = Sprite::create("door.PNG");
    door1->setAnchorPoint(Vec2(0, 0));
    door1->setPosition(Point((visibleSize.width / 2) + 200, (visibleSize.height / 2) - 115));
    door1->setScale(0.145);
    door1->setName("door1");
    this->addChild(door1, 3);
    auto physicsBody_door1 = PhysicsBody::createBox(door1->getContentSize(), PhysicsMaterial(1500.0f, 1.0f, 9.0f));
    physicsBody_door1->setDynamic(false);
    physicsBody_door1->setCollisionBitmask(3);
    physicsBody_door1->setCategoryBitmask(3);
    physicsBody_door1->setContactTestBitmask(3);
    physicsBody_door1->setTag(3);
    door1->setPhysicsBody(physicsBody_door1);


    /// <summary>
    /// 
    /*
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [floor2](PhysicsContact& contact) {
        PhysicsBody* x = contact.getShapeA()->getBody();
        PhysicsBody* y = contact.getShapeB()->getBody();
        
        // Replace the current scene with scene2 if nodeA and nodeB are the player and door1 objects, respectively
            if (1 == x->getCollisionBitmask() && 2 == y->getCollisionBitmask() || 2 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {
                CCLOG("Contact between player and door1 detected!");

                auto scene2 = SCENE2::createScene();
                Director::getInstance()->pushScene(TransitionSplitCols::create(0.4, scene2));
            }
        return true;
    }; 
    contactListener->onContactBegin = CC_CALLBACK_1(SCENE1::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
*/

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [player](PhysicsContact& contact) {


        PhysicsBody* x = contact.getShapeA()->getBody();
        PhysicsBody* y = contact.getShapeB()->getBody();


        if (1 == x->getCollisionBitmask() && 3 == y->getCollisionBitmask() || 3 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene =SCENE2::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));

        }

        if (1 == x->getCollisionBitmask() && 5 == y->getCollisionBitmask() || 5 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene = Gameover::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));

        }
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


   // Create a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(SCENE1::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SCENE1::onKeyPressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    keyboardListener->onKeyPressed = [player](EventKeyboard::KeyCode KeyCode, Event* event)
    {
        if (KeyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            auto action1 = JumpBy::create(0.5f, Vec2(50, 50), 30.0f, 1);
            player->runAction(action1);
            cocos2d::AudioEngine::preload("jump.mp3"); //upload de notre music mp3 en v4 de cocos
            cocos2d::AudioEngine::play2d("jump.mp3");
        }
        if (KeyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_D) {
            auto jump = JumpBy::create(0.5f, Vec2(50, 50), 50.0f, 1);
            MoveBy* moveAction = MoveBy::create(2, Vec2(70, 0));
            RepeatForever* repeatAction = RepeatForever::create(moveAction);
            player->runAction(repeatAction);
        }
        if (KeyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_A) {
            auto jump = JumpBy::create(0.5f, Vec2(50, 50), 50.0f, 1);
            MoveBy* moveAction = MoveBy::create(2, Vec2(-70, 0));
            RepeatForever* repeatAction = RepeatForever::create(moveAction);
            player->runAction(repeatAction);

        }

    };


    keyboardListener->onKeyReleased = [player](EventKeyboard::KeyCode KeyCode, Event* event)
    {
        if (KeyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_D) {
            player->stopAllActions();
        }
        if (KeyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_A) {
            player->stopAllActions();
        }

    };

    return true;
}
void SCENE1::goback(cocos2d::Ref* pSender)
{
    CCLOG("GOBACK"); //affichage de play 
    //fct en cliquant sur play, on switch vers   
    Director::getInstance()->popScene();
}

void SCENE1::reload(cocos2d::Ref* pSender) {
    auto scene = SCENE1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}


bool SCENE1::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* x = contact.getShapeA()->getBody();
    PhysicsBody* y = contact.getShapeB()->getBody();
    if (1 == x->getCollisionBitmask() && 2 == y->getCollisionBitmask() || 2 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

        void reload(cocos2d::Ref * pSender);
    }
    return true;
}
void SCENE1::door(cocos2d::Ref* pSender)
{
    CCLOG("DOOR");
}

void SCENE1::go(cocos2d::Ref* PSender) {
    Director::getInstance()->popScene(); //revenier a la scene hello world
}
