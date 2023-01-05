#include "SCENE2.h"
#include "SCENE1.h"
#include "Gameover.h"
#include "HelloWorldScene.h"
#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsJoint.h"
#include "win.h"
USING_NS_CC;

Scene* SCENE2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0, -300));

    // 'layer' is an autorelease object
    auto layer = SCENE2::create();

    // add layer as a child to scene
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool SCENE2::init()
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



    ///////////////////  add Sprite

    auto pinfo = AutoPolygon::generatePolygon("Pico_Player_blue.png");
    auto player = Sprite::create(pinfo);
    player->setAnchorPoint(Vec2(0.5f, 0.5f));
    player->setPosition(Vec2(20, 60));
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





    //////////////////////create the background that iclude PICO PARK
    ///////////////////////////////////// creating the floor1(THe LAND)

    auto floor = Sprite::create("l2ard.png");
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
    floor2->addChild(floor2, 1);

    //creating physique for THE FLOOR

    auto physicsBody_floor2 = PhysicsBody::createBox(floor2->getContentSize(), PhysicsMaterial(1500.0f, 0.1f, 0.9f));

    physicsBody_floor2->setDynamic(false);
    physicsBody_floor2->setCollisionBitmask(1);
    physicsBody_floor2->setCategoryBitmask(1);
    floor2->setPhysicsBody(physicsBody_floor2);



    /////////////////////////////
    // 
    // 
    // 
    // 
    // 
    auto obstacle2 = Sprite::create("obstacle1.png");
    obstacle2->setAnchorPoint(Vec2(0, 0));
    obstacle2->setPosition(Vec2(330, -77));
    obstacle2->setScale(0.240);
    this->addChild(obstacle2, 1);

    auto physicsBody_obstacle2 = PhysicsBody::createBox(obstacle2->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));

    physicsBody_obstacle2->setDynamic(false);
    physicsBody_obstacle2->setCollisionBitmask(5);
    physicsBody_obstacle2->setCategoryBitmask(5);
    obstacle2->setPhysicsBody(physicsBody_obstacle2);
    physicsBody_obstacle2->setContactTestBitmask(5);
    physicsBody_obstacle2->setTag(5);














    auto obstacle3 = Sprite::create("obstacle1.png");
    obstacle3->setAnchorPoint(Vec2(0, 0));
    obstacle3->setPosition(Vec2(130, -77));
    obstacle3->setScale(0.240);
    this->addChild(obstacle3, 1);

    auto physicsBody_obstacle3 = PhysicsBody::createBox(obstacle3->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 1.0f));

    physicsBody_obstacle3->setDynamic(false);
    physicsBody_obstacle3->setCollisionBitmask(5);
    physicsBody_obstacle3->setCategoryBitmask(5);
    obstacle3->setPhysicsBody(physicsBody_obstacle3);
    physicsBody_obstacle3->setContactTestBitmask(5);
    physicsBody_obstacle3->setTag(5);
    ////////////////////////////

   // Create a keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(SCENE2::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SCENE2::onKeyPressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    keyboardListener->onKeyPressed = [player](EventKeyboard::KeyCode KeyCode, Event* event)
    {

        if (KeyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || KeyCode == EventKeyboard::KeyCode::KEY_SPACE) {
            auto action1 = JumpBy::create(0.7f, Vec2(80, 50), 60.0f, 1);
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


    ////////////////////////////
    auto* menu = Menu::create();
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    ////////////////////////////

    auto goback_button = Sprite::create("menu.PNG");
    auto goback_button_selected = Sprite::create("menu.PNG");
    MenuItemImage* menu_goback = MenuItemImage::create();
    menu_goback->setNormalImage(goback_button);
    menu_goback->setSelectedImage(goback_button_selected);
    menu_goback->setCallback(CC_CALLBACK_1(SCENE2::goback, this));

    menu->addChild(menu_goback, 4);

    menu_goback->setPosition(Point((visibleSize.width / 2) + 220, (visibleSize.height / 2) + 140));
    //////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto *dontpush2 = Sprite::create("button.png");

    dontpush2->setAnchorPoint(Vec2(0, 0));
    dontpush2->setPosition(Vec2(50, 40));
    dontpush2->setScale(0.30);
    door1->setName("buttom");
    this->addChild(dontpush2, 6);

    auto physicsBody_dontpush2 = PhysicsBody::createBox(dontpush2->getContentSize(), PhysicsMaterial(0.1f, 0.5f, 0.5f));
    physicsBody_dontpush2->setDynamic(false);
    physicsBody_dontpush2->setCollisionBitmask(6);
    physicsBody_dontpush2->setCategoryBitmask(6);
    physicsBody_dontpush2->setContactTestBitmask(6);
    physicsBody_door1->setTag(6);
    dontpush2->setPhysicsBody(physicsBody_dontpush2);

    ////////////////////////////////////////////////////////////////////////////////
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [player](PhysicsContact& contact) {


        PhysicsBody* x = contact.getShapeA()->getBody();
        PhysicsBody* y = contact.getShapeB()->getBody();
        if (1 == x->getCollisionBitmask() && 3 == y->getCollisionBitmask() || 3 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene = win::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));

        }

        if (1 == x->getCollisionBitmask() && 5 == y->getCollisionBitmask() || 5 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene = Gameover::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));

        }
        if (1 == x->getCollisionBitmask() && 6 == y->getCollisionBitmask() || 6 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

        


        }
        return true;
        return true;
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


   
    //////////////////////////////////////////////////////////////////

    auto floor3 = Sprite::create("l2ard.png");
    floor3->setAnchorPoint(Vec2(1, 0));
    floor3->setPosition(Vec2(300, 0));
    floor3->setScale(0.125);
    this->addChild(floor3, 1);

    //creating physique for THE FLOOR

    auto physicsBody_floor3 = PhysicsBody::createBox(floor3->getContentSize(), PhysicsMaterial(1500.0f, 0.1f, 0.9f));

    physicsBody_floor3->setDynamic(false);
    physicsBody_floor3->setCollisionBitmask(1);
    physicsBody_floor3->setCategoryBitmask(1);


    floor3->setPhysicsBody(physicsBody_floor3);



    return true;
}



//////////////////////////////////////////////////////////////////

void SCENE2::goback(cocos2d::Ref* pSender)
{
    CCLOG("GOBACK"); //affichage de play 
    //fct en cliquant sur play, on switch vers   
    Director::getInstance()->popScene();
}



bool SCENE2::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* x = contact.getShapeA()->getBody();
    PhysicsBody* y = contact.getShapeB()->getBody();
    if (1 == x->getCollisionBitmask() && 2 == y->getCollisionBitmask() || 2 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

        void reload(cocos2d::Ref * pSender);
    }
    return true;
}
void SCENE2::door(cocos2d::Ref* pSender)
{
    CCLOG("DOOR");
}

void SCENE2::go(cocos2d::Ref* PSender) {
    auto scene1 = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionSplitCols::create(1, scene1));
}

