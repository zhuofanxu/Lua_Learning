//
//  StartScene.cpp
//  HelloCpp
//
//  Created by xgq on 3/6/14.
//
//

#include "StartScene.h"
#include "Utility.h"
#include "AppMacros.h"
#include "GameScene.h"
StartLayer::StartLayer()
{
    
}
StartLayer::~StartLayer()
{
    
}
bool StartLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
   
    initData();
    return true;
}

void StartLayer::initData()
{
    addResource();
    CCSprite* pMenueSprite=CCSprite::create(MainMenueResourceName.c_str());
    pMenueSprite->retain();
    this->addChild(pMenueSprite);
    pMenueSprite->setPosition(ccp(designResolutionSize.width/2, designResolutionSize.height/2));
}

bool StartLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCLog("menu layer touch begin.....");
    CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2, GameScene::createScene()));
    //CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(2.0, GameScene::createScene()));
  // CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5, GameScene::createScene(), ccc3(84,255,159)));
    return true;
}

void StartLayer::ccTouchMvoed(CCTouch* touch, CCEvent* event)
{
    CCLog("menu layer touch move.....");
}

void StartLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCLog("menu layer touch ended......");
}

void StartLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    CCLog("meneu layer add touch listener successful......");
}

void StartLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLog("menu layer remove touch listener........");
}

StartScene::StartScene():pLayer(NULL)
{}
StartScene::~StartScene() 
{
    if (pLayer)
    {
        pLayer->release();
        pLayer=NULL;
    }
} 
bool StartScene::init()
{ 
   //先调用父类的初始化funciton
    if (!CCScene::init())
    {
        return false;
    } 
    this->pLayer=StartLayer::create();
    this->pLayer->retain();
    this->addChild(pLayer);
    return true;
} 

