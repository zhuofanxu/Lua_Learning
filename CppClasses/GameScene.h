//
//  GameScene.h
//  HelloCpp
//
//  Created by xgq on 3/1/14.
//
//

#ifndef __HelloCpp__GameScene__
#define __HelloCpp__GameScene__
#include <cocos2d.h>
#include "TouchableSprite.h"
#include "CardNode.h"
#define Game_Time 60
#define Card_Show_Time 2.0
USING_NS_CC;
class GameScene : public CCLayer 
{ 
public:
    GameScene();
    ~GameScene(); 
    static CCScene* createScene();
    
    //scheduleUpdate每一帧要调用的更新函数 覆写了CCNode::update(flaot dt)
    virtual void update(float delay);
    void gameLogic(float delay);
    void enterRound(float delay);
    void exitRound(float delay);
    //void updateGame(float dt);
    void createUI();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    //可能需要覆写的 接收触摸信息的回掉虚函数
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch,CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch,CCEvent* event);
    
    //  selector callback
    void menuCloseCallback(CCObject* pSender);
    
    
    
    CREATE_FUNC(GameScene);
    
  
private:
    //游戏时间
   // float              mGameTime;
    bool               mShouldChangeRound;
    //表示玩家当前获取的星星数量
    int                mCurrCount;
    //游戏局数
    int                mRound;
    CCProgressTimer*   pTimeProgressL;
    CCProgressTimer*   pTimeProgressR;
    //表示星星数量的数字精灵
    CCSprite*          pNumSprite;
    //背景精灵
    CCSprite*          pBackGroundSprite;
    //卡牌节点
    CardNode*          pCardNode;
    //保存卡牌节点对象数组
    CCArray* pCard_nodes;
    //用于初始化精灵图片资源数据或者其它对象的实例化
    void initData();
};

#endif /* defined(__HelloCpp__GameScene__) */
