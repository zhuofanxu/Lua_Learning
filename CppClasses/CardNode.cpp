//
//  CardNode.cpp
//  HelloCpp
//
//  Created by xgq on 3/5/14.
//
//

#include "CardNode.h"
CardNode::CardNode()
{
    m_oreName="";
    m_isOpen=false;
    //卡牌默认是不含矿物的
    m_hasOre=false;
    pActionIn=NULL;
    pActionOut=NULL;
    pTouchOreSprite_out=NULL;
    pTouchOreSprite_in=NULL;
    pOreSprite=NULL;
    m_isActionDone=true;
    m_hasBeenTouched=false;
}



CardNode::~CardNode()
{
    if (pTouchOreSprite_out)
    {
        pTouchOreSprite_out->release();
        pTouchOreSprite_out=NULL;
    }
    if (pTouchOreSprite_in)
    {
        pTouchOreSprite_in->release();
        pTouchOreSprite_in=NULL;
    }
    
    if (pOreSprite)
    {
        pOreSprite->release();
        pOreSprite=NULL;
    }
    if (pActionIn) {
        pActionIn->release();
        pActionIn=NULL;
    }
    if (pActionOut) {
        pActionOut->release();
        pActionOut=NULL;
    }

}


bool CardNode::containsTouchLocation(CCTouch* touch)
{
    CCPoint touchPoint=touch->getLocationInView();
    touchPoint=CCDirector::sharedDirector()->convertToGL(touchPoint);
    return rect().containsPoint(touchPoint);
}

CCRect CardNode::rect()
{
    CCSize  size=getContentSize();
    CCPoint pos=getPosition();
    return  CCRectMake(pos.x-size.width/2, pos.y-size.height/2, size.width, size.height);
}

bool CardNode::initAnimation()
{
    
    
    pActionIn=(CCActionInterval*)\
        CCSequence::create(CCDelayTime::create(Duration/2),\
                           CCShow::create(),\
                           CCOrbitCamera::create(Duration/2, 1, 0, IN_AngleZ, IN_DeltaZ, 0, 0),\
                           CCCallFunc::create(this, callfunc_selector(CardNode::finishActionCall)),\
                           NULL);
    pActionIn->retain();
    pActionOut=(CCActionInterval*)\
        CCSequence::create(CCOrbitCamera::create(Duration/2, 1, 0, OUT_AngleZ, OUT_DeltaZ, 0, 0),\
                           CCHide::create(),\
                           CCDelayTime::create(Duration/2),\
                           NULL);
    pActionOut->retain();
    if (pActionOut && pActionIn) {
        CCLog("Card action init successful!");
        return true;
    }
    else
    {
        CCLog("Card action init failed!!!");
        return false;
    }

}


void CardNode::finishActionCall()
{
    m_isActionDone=true;
}

void CardNode::openCard()
{
    m_isActionDone=false;
    pTouchOreSprite_in->setVisible(false);
    pTouchOreSprite_in->runAction(pActionIn);
    pTouchOreSprite_out->runAction(pActionOut);
    m_isOpen=true;
}

void CardNode::closeCard()
{
    m_isActionDone=false;
    pTouchOreSprite_out->setVisible(false);
    pTouchOreSprite_out->runAction(pActionIn);
    pTouchOreSprite_in->runAction(pActionOut);
    m_isOpen=false;
}

void CardNode:: updateOreSprite()
{
    CCTexture2D* targetTex=NULL;
    CCSprite*    targetSpr=NULL;
    if (m_hasOre) {
        targetSpr=CCSprite::create(StarResourceName.c_str());
        targetSpr->retain();
        targetTex=targetSpr->getTexture();
        pOreSprite->setTexture(targetTex);
    }
    else
    {
        targetSpr=CCSprite::create(ErrorResourceName.c_str());
        targetSpr->retain();
        targetTex=targetSpr->getTexture();
        pOreSprite->setTexture(targetTex);
    }
}
bool CardNode:: initData()
{
   // std::string filename="ore/";
    pTouchOreSprite_in=TouchableSprite::createWhithFile(InResourceName.c_str());
    pTouchOreSprite_in->retain();
    pTouchOreSprite_out=TouchableSprite::createWhithFile(OutResourceName.c_str());
    pTouchOreSprite_out->retain();
    if (!m_hasOre) {
        pOreSprite=TouchableSprite::createWhithFile(ErrorResourceName.c_str());
        pOreSprite->retain();
    }
    else
    {
        //随机产生一个0-41之间的整数(矿物的索引值)
//        produceRandomNumber(42);
//        filename+=OreResourceName[OreRandIndex];
        pOreSprite=TouchableSprite::createWhithFile(StarResourceName.c_str());
        pOreSprite->retain();
        pOreSprite->setPosition(ccp(11, 11));
       // m_oreName=getOreName(OreRandIndex);
    }
    
    if (pTouchOreSprite_in&&pTouchOreSprite_out&&pOreSprite) {
        this->addChild(pTouchOreSprite_in);
        pOreSprite->setAnchorPoint(ccp(0, 0));
        pTouchOreSprite_in->addChild(pOreSprite);
        //pTouchOreSprite_in->setAnchorPoint(ccp(0, 0));
        //pOreSprite->setPosition(ccp(10, 10));
        this->addChild(pTouchOreSprite_out);
        //设置卡牌节点与卡牌外面精灵一样大小
        this->setContentSize(pTouchOreSprite_out->getContentSize());
        CCLog("CardNode attach children's nodes successful!");
        return true;
    }
    else
    {
        return false;
        CCLog("CardNode's children's nodes init failed!!!");
    }
    
}

bool CardNode::init()
{
    //this->setAnchorPoint(ccp(0.5, 0.5));
    if (initAnimation()) {
        return true;
    }
    else
        return false;
}

