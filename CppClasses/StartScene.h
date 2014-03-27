//
//  StartScene.h
//  HelloCpp
//
//  Created by xgq on 3/6/14.
//
//

#ifndef __HelloCpp__StartScene__
#define __HelloCpp__StartScene__
#include <cocos2d.h>
USING_NS_CC;

class StartLayer : public CCLayer
{
public:
    StartLayer();
    ~StartLayer();
    virtual bool init();
    void initData();
    CREATE_FUNC(StartLayer);
    
    
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMvoed(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);

    virtual void onEnter();
    virtual void onExit();
    
};


class StartScene : public CCScene
{ 
public:
    StartScene();
    ~StartScene();
    virtual bool init(); 
    CREATE_FUNC(StartScene);
    CC_SYNTHESIZE(StartLayer*,pLayer,Layer);
private:
    
    //void initData();
};

#endif /* defined(__HelloCpp__StartScene__) */
