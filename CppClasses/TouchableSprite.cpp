//
//  TouchableSprite.cpp
//  HelloCpp
//
//  Created by xgq on 2/27/14.
//
//

#include "TouchableSprite.h"
USING_NS_CC;



TouchableSprite::TouchableSprite()
{
    //Card_Is_Open=false;
}
TouchableSprite::~TouchableSprite()
{
}


TouchableSprite* TouchableSprite::createWhithFile(const char *file)
{
   // initAnimation();
    TouchableSprite* pTouchSprite=new TouchableSprite();
    if (pTouchSprite && pTouchSprite->initWithFile(file))
    {
        pTouchSprite->autorelease();
        return pTouchSprite;
    }
    CC_SAFE_DELETE(pTouchSprite);
    return NULL;
}


