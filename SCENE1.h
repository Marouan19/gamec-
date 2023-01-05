#pragma once
#ifndef _SCENE1SCENE_H_
#define _SCENE1_SCENE_H_
#include "cocos2d.h"
#include "cocos2d.h"
#include "physics/CCPhysicsWorld.h"
#include "physics-nodes/CCPhysicsSprite.h"
#include "physics/CCPhysicsContact.h"
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include <iostream>
#include "SCENE2.h"
using namespace cocos2d;

USING_NS_CC;


class SCENE1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SCENE1);



    void go(Ref* pSender);
    void goback(Ref* pSender);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void door(Ref* pSender);
    void reload(Ref* pSender); //fct de replacement de scene lors d echec



    //physics 
    cocos2d::PhysicsWorld* sceneWorld;
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};
#endif