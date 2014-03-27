//
//  GameScene.cpp
//  HelloCpp
//
//  Created by xgq on 3/1/14.
//
//

#include "GameScene.h"
#include "AppMacros.h"
#include "Utility.h"

GameScene::GameScene()
{
    pBackGroundSprite=NULL;
    pCard_nodes=NULL;
    pCardNode=NULL;
    pTimeProgressL=NULL;
    pTimeProgressR=NULL;
    pNumSprite=NULL;
    mCurrCount=0;
    mRound=0;
    mShouldChangeRound=true;
} 
GameScene::~GameScene() 
{
    
    if (pCard_nodes)
    {
        pCard_nodes->release();
        pCard_nodes=NULL;
    }
    if (pCardNode) {
        pCardNode->release();
        pCardNode=NULL;
    }
    if (pBackGroundSprite) {
        pBackGroundSprite->release();
        pBackGroundSprite=NULL;
    }
    if (pTimeProgressL) {
        pTimeProgressL->release();
        pTimeProgressL=NULL;
    }
    if (pTimeProgressR) {
        pTimeProgressR->release();
        pTimeProgressR=NULL;
    }
    if (pNumSprite) {
        pNumSprite->release();
        pNumSprite=NULL;
    }


}
CCScene* GameScene::createScene()
{ 
    CCScene*   scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;

}

void GameScene::createUI()
{
    //进度条背景图片
    CCSprite* sbackL=CCSprite::create("挖矿_时间底.png");
    sbackL->retain();
    sbackL->setAnchorPoint(ccp(0, 0));
    sbackL->setPosition(ccp(60, 125));
    //sback->setScaleY(0.5);
    // sback->setScaleY(1);
    pBackGroundSprite->addChild(sbackL);
    CCSprite* sbackR=CCSprite::create("挖矿_时间底.png");
    sbackR->retain();
    sbackR->setAnchorPoint(ccp(0, 0));
    sbackR->setPosition(ccp(420, 125));
    pBackGroundSprite->addChild(sbackR);
    //创建进度条
    CCSprite* sptime=CCSprite::create("挖矿_时间进度.png");
    sptime->retain();
    //左边时间进度条
    pTimeProgressL=CCProgressTimer::create(sptime);
    pTimeProgressL->setScaleY(24.35);
    pTimeProgressL->retain();
    //设置为水平或垂直进度条
    pTimeProgressL->setType(kCCProgressTimerTypeBar);
    //CCNode::CCNode();
    //设置进度从下到上的变化
    pTimeProgressL->setMidpoint(ccp(1, 0));
    //设置为高度变化(y轴)
    pTimeProgressL->setBarChangeRate(ccp(0, 1));
   // pTimeProgressL->setPercentage(100);
    pTimeProgressL->setAnchorPoint(ccp(0, 0));
    pTimeProgressL->setPosition(ccp(68, 132));
    pBackGroundSprite->addChild(pTimeProgressL);
    //右边时间进度条
    pTimeProgressR=CCProgressTimer::create(sptime);
    pTimeProgressR->setScaleY(24.35);
    pTimeProgressR->retain();
    //设置为水平或垂直进度条
    pTimeProgressR->setType(kCCProgressTimerTypeBar);
    //CCNode::CCNode();
    //设置进度从下到上的变化
    pTimeProgressR->setMidpoint(ccp(1, 0));
    //设置为高度变化(y轴)
    pTimeProgressR->setBarChangeRate(ccp(0, 1));
    //pTimeProgressR->setPercentage(100);
    pTimeProgressR->setAnchorPoint(ccp(0, 0));
    pTimeProgressR->setPosition(ccp(428, 132));
    pBackGroundSprite->addChild(pTimeProgressR);

    //添加进度动画 10秒内达到100%
//    CCProgressTo* actionL=CCProgressTo::create(60, 100);
//    actionL->retain();
//    pTimeProgressL->runAction(actionL);
//    CCProgressTo* actionR=CCProgressTo::create(60, 100);
//    actionR->retain();
//    pTimeProgressR->runAction(actionR);
    //挖矿漏斗
    CCSprite* funnel=CCSprite::create("挖矿_漏斗.png");
    funnel->retain();
    funnel->setAnchorPoint(ccp(0, 0));
    funnel->setPosition(ccp(410, 85));
    pBackGroundSprite->addChild(funnel);
    //挖矿奖励精灵
    CCSprite* rewards=CCSprite::create("挖矿_奖励.png");
    rewards->retain();
    rewards->setAnchorPoint(ccp(0, 0));
    rewards->setPosition(ccp(50, 100));
    pBackGroundSprite->addChild(rewards);
    //表示star数量的ui
    CCSprite* star=CCSprite::create("泡泡龙_星星.png");
    star->retain();
    star->setScale(0.7);
    star->setPosition(ccp(82, 15));
    pBackGroundSprite->addChild(star);
    
    CCSprite* mulit=CCSprite::create("泡泡龙数字/跳字绿_乘.png");
    mulit->setScale(0.8);
    mulit->setPosition(ccp(105, 12));
    pBackGroundSprite->addChild(mulit);
    
    pNumSprite=CCSprite::create(NumberSpriteName[0].c_str());
    pNumSprite->retain();
   
    pNumSprite->setScale(0.8);
    pNumSprite->setPosition(ccp(125, 12));
    pBackGroundSprite->addChild(pNumSprite);
}

bool GameScene::init() 
{ 
   //先调用父类的初始化funciton
    if (!CCLayer::init())
    {
        return false;
    } 
    initData();
    //矿物精灵以子节点的身份加入到卡牌里面精灵上
   // srand((unsigned)time(NULL));
   
    //开启定时器
    this->scheduleUpdate();
    return true;
}

void GameScene::initData()
{
    //添加资源名
     addResource();
     //设计分辨率裁剪后的有效尺寸
    CCSize  visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //设计分辨率被裁剪的尺寸(上下或左右裁剪的矩形尺寸)
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    // add your codes here...
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    
    //创建游戏背景精灵
    pBackGroundSprite = CCSprite::create(BackGroundResourceName.c_str());
    //pBackGroundSprite保存了精灵对象指针，该对象的引用计数加一
    pBackGroundSprite->retain();
    pBackGroundSprite->setPosition(ccp(designResolutionSize.width/2, designResolutionSize.height/2));
    //将该精灵以子节点的身份加入到本层
    this->addChild(pBackGroundSprite, 0);
    createUI();
    //创建卡牌数组
    pCard_nodes=CCArray::create();
    pCard_nodes->retain();
    
    
       //以每次程序运行的时间作为随机种子
    srand((unsigned)time(NULL));
    //初始化精灵对象并加入ccarray数组保存
    for (int i=0; i<NUM_OF_CARD; i++)
    {
        pCardNode=CardNode::create();
        pCardNode->retain();
        pCard_nodes->addObject(pCardNode);
        

    }
//设置随机的1个卡牌含有矿物 每次产生的随机位置可能会重复，所以如果规定某一个数量就要要另行判断
//    produceRandomNumber(16);
//    ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
//    produceRandomNumber(16);
//    ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
//    produceRandomNumber(16);
//    ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
    
    for (int i=0; i<NUM_OF_CARD; i++)
    {
        ((CardNode*)pCard_nodes->objectAtIndex(i))->initData();
        
    }
    this->setTouchEnabled(false);
    //在背景中间整齐摆放4x4的卡片
    for (int i=0; i<NUM_OF_CARD/4; i++)
    {
        
        for (int j=0; j<NUM_OF_CARD/4; j++)
        {
            CardNode* cnode=(CardNode*)(pCard_nodes->objectAtIndex(i+j*4));
            cnode->retain();
            cnode->setPosition(ccp(designResolutionSize.width*(i+1)/7+80, designResolutionSize.height*(j+1)/5-8));
            pBackGroundSprite->addChild(cnode);
        }
    }
    
    
   
}


bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLog("touch scene began...............");
    //static std::string orename;
    static int    RoundOnecount=0;
    static int    RoundTwocount=0;
    static int    RoundThreecount=0;
   // static int    RoundFourcount=0;
    switch (mRound)
    {
        case 1:
            for (int i=0; i<NUM_OF_CARD; i++)
            {
                if (((CardNode*)pCard_nodes->objectAtIndex(i))->containsTouchLocation(pTouch))
                {
                    if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard())
                    {
                        if (((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                        {
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->openCard();
                        }

                    }
                    
                    if (((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard())
                    {
                        replaceNumSprite(pNumSprite, mCurrCount);
                        //检测是否已经点击过
                        if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getHasBeenTouched()) {
                            mCurrCount++;
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasBeenTouched(true);
                        }
                        RoundOnecount++;
                        if (RoundOnecount==1) {
                            mShouldChangeRound=true;
                        }
                        
                    }
                    else
                    {
                        mShouldChangeRound=true;
                        break;
                    }
                    
                }
                
            }

            break;
        case 2:
            for (int i=0; i<NUM_OF_CARD; i++)
            {
                if (((CardNode*)pCard_nodes->objectAtIndex(i))->containsTouchLocation(pTouch))
                {
                    if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard())
                    {
                        if (((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                        {
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->openCard();
                        }
                        
                    }
                    if (((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard())
                    {
                        replaceNumSprite(pNumSprite, mCurrCount);
                        if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getHasBeenTouched()) {
                            mCurrCount++;
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasBeenTouched(true);
                        }
                        RoundTwocount++;
                        cout<<RoundTwocount<<endl;
                        if (RoundTwocount==2) {
                            mShouldChangeRound=true;
                        }

                        
                    }
                
                    else
                    {
                        mShouldChangeRound=true;
                        break;
                    }
                    
                }
                
            }
               break;
        case 3:
            for (int i=0; i<NUM_OF_CARD; i++)
            {
                if (((CardNode*)pCard_nodes->objectAtIndex(i))->containsTouchLocation(pTouch))
                {
                    if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard())
                    {
                        if (((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                        {
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->openCard();
                        }
                        
                    }
                    
                    if (((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard())
                    {
                        replaceNumSprite(pNumSprite, mCurrCount);
                        if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getHasBeenTouched()) {
                            mCurrCount++;
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasBeenTouched(true);
                        }

                        RoundThreecount++;
                        cout<<RoundThreecount;
                        if (RoundThreecount==3) {
                            mShouldChangeRound=true;
                        }
                    }
                    else
                    {
                        mShouldChangeRound=true;
                        break;
                    }
                    
                }
                
            }
            break;
        case 4:
            for (int i=0; i<NUM_OF_CARD; i++)
            {
                if (((CardNode*)pCard_nodes->objectAtIndex(i))->containsTouchLocation(pTouch))
                {
                    if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard())
                    {
                        if (((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                        {
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->openCard();
                        }
                        
                    }
                    
                    if (((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard())
                    {
                        replaceNumSprite(pNumSprite, mCurrCount);
                        if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getHasBeenTouched()) {
                            mCurrCount++;
                            ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasBeenTouched(true);
                        }
                        //作其他处理
                            
                        
                    }
                    else
                    {
                        
                        break;
                    }
                    
                }
           

            }
             break;
        default:
            break;
}
           return true;
}

void GameScene::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCLog("touch scene move...............");
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{
    CCLog("touch scene end...............");
}

void GameScene::onEnter()
{
    
    
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
    //CCLOG("add layer touch listener successful....");
}

void GameScene::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    // CCLOG("remove layer touch listener successful...");
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}



void GameScene::gameLogic(float delay)
{
    static bool  isShow=false;
    static bool  isClose=false;
    static float game_elapse=0;
    static float duringCloseToOpne=0;
    static float duringChangeRound=0;
    game_elapse+=delay;
    duringChangeRound+=delay;
   // NextRound(delay);
        
    if (game_elapse<=60.0)
    {
       if (mShouldChangeRound)
       {
           //结束上一个回合
          exitRound(delay);
          mRound++;
          enterRound(delay);
          
           //每一轮自动翻牌标志变量
           isShow=false;
           isClose=false;
           duringCloseToOpne=0;
           mShouldChangeRound=false;
           duringChangeRound=0;
           
           //新的回合更新点击标志到初始化状态
           for (int i=0; i<NUM_OF_CARD; i++)
           {
               ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasBeenTouched(false);
           }
        }
     
        if (duringChangeRound>=2.0) {
            if (!isShow)
            {
                for (int i=0; i<NUM_OF_CARD; i++)
                {
                    if(((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard()&&((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                    {
                        ((CardNode*)pCard_nodes->objectAtIndex(i))->openCard();
                        
                    }
                    
                }
                isShow=true;
            }
            duringCloseToOpne+=delay;
            //cout<<duringCloseToOpne<<endl;
            //卡牌显示2s后自动关闭
            if (duringCloseToOpne>=Card_Show_Time&&!isClose)
            {
                for (int i=0; i<NUM_OF_CARD; i++)
                {
                    if (((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard()&&((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                    {
                        ((CardNode*)pCard_nodes->objectAtIndex(i))->closeCard();
                    }
                }
                isClose=true;
                
            }

        }
        //实时检测close不含星星物品的卡牌
        for (int i=0; i<NUM_OF_CARD; i++) {
            if (!((CardNode*)pCard_nodes->objectAtIndex(i))->getHasOreFromCard()&&((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard()&&((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone()) {
                ((CardNode*)pCard_nodes->objectAtIndex(i))->closeCard();

            }
             ((CardNode*)pCard_nodes->objectAtIndex(i))->updateOreSprite();
        }
        
    }
    
    
    //60秒后结束游戏
    if (game_elapse>60.0)
    {
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif

    }
 
}

void GameScene::enterRound(float delay)
{
    int indexTemp=0;
    int indexTemp_=0;
    int indexTemp__=0;
       //更新每一轮星星在卡牌的位置和数量
    switch (mRound) {
        case 1:
            produceRandomNumber(16);
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            
            break;
        case 2:
            produceRandomNumber(16);
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            indexTemp=CardRandIndex;
            //产生不重复的"随机"位置索引
            while (CardRandIndex==indexTemp) {
                produceRandomNumber(16);
            }
             ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            break;
        case 3:
            produceRandomNumber(16);
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            indexTemp=CardRandIndex;
            //产生不重复的"随机"位置索引
            while (CardRandIndex==indexTemp) {
                produceRandomNumber(16);
            }
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            indexTemp_=CardRandIndex;
            while (CardRandIndex==indexTemp||CardRandIndex==indexTemp_) {
                produceRandomNumber(16);
            }
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            break;
        case 4:
            produceRandomNumber(16);
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            indexTemp=CardRandIndex;
            //产生不重复的"随机"位置索引
            while (CardRandIndex==indexTemp) {
                produceRandomNumber(16);
            }
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            indexTemp_=CardRandIndex;
            while (CardRandIndex==indexTemp||CardRandIndex==indexTemp_) {
                produceRandomNumber(16);
            }
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
              indexTemp__=CardRandIndex;
            while (CardRandIndex==indexTemp||CardRandIndex==indexTemp_||CardRandIndex==indexTemp__) {
                produceRandomNumber(16);
            }
            ((CardNode*)pCard_nodes->objectAtIndex(CardRandIndex))->setHasOreForCard(true);
            break;
        default:
            break;
            
    }
   
}

void GameScene::exitRound(float delay)
{
    //设置所有卡牌不含矿物 关闭已打开的卡牌
    for (int i=0; i<NUM_OF_CARD; i++)
    {
        if(((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard()&&((CardNode*)pCard_nodes->objectAtIndex(i))->getIsAcutionDone())
                ((CardNode*)pCard_nodes->objectAtIndex(i))->closeCard();
       // if(!((CardNode*)pCard_nodes->objectAtIndex(i))->getIsOpenFromCard())
        ((CardNode*)pCard_nodes->objectAtIndex(i))->setHasOreForCard(false);
        
    }

}

void GameScene::update(float delay)
{
    static float elapse=0;
    //static int currCount=0;
    elapse+=delay;
    //更新表示星星数量的UI
    //更新时间进度
    if (elapse<=Game_Time)
    {
        pTimeProgressL->setPercentage(100*elapse/Game_Time);
        pTimeProgressR->setPercentage(100*elapse/Game_Time);
    }

    //执行游戏逻辑
    gameLogic(delay);
    //CCLog("%f",elapse);
    //还要附加其他的判断条件
   // gameLogic(elapse);

}
