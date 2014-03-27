//
//  TouchableSprite.h
//  HelloCpp
//
//  Created by xgq on 2/27/14.
//
//

#ifndef __HelloCpp__TouchableSprite__
#define __HelloCpp__TouchableSprite__

#include <iostream>
#include "cocos2d.h"

//卡牌类型枚举变量
enum TAG
{
    tag_inCard,
    tag_outCard
};

class TouchableSprite : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{

public:
    
    TouchableSprite();
    //TouchableSprite可能会作为一个可触摸精灵的基类,故这里使用virtual destructor
    virtual ~TouchableSprite();
    
    static TouchableSprite* createWhithFile(const char* file);
  
};


#endif /* defined(__HelloCpp__TouchableSprite__) */

