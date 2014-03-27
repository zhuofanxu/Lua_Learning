//
//  CardNode.h
//  HelloCpp
//
//  Created by xgq on 3/5/14.
//
//

#ifndef __HelloCpp__CardNode__
#define __HelloCpp__CardNode__

//#include <iostream>
#include "Utility.h"
#include "TouchableSprite.h"
#define IN_AngleZ  270 //里面卡牌起始z轴角度值
#define IN_DeltaZ  90  //里面卡牌旋转的z轴角度值
#define OUT_AngleZ 0
#define OUT_DeltaZ 90

#define Duration   0.3
USING_NS_CC;
class CardNode : public CCNode,public CCTargetedTouchDelegate
{
public:
    CardNode();
    ~CardNode();
    
    void openCard();
    void closeCard();
    void updateOreSprite();
    //卡牌节点的初始化
    bool init();
    //卡牌子节点(精灵)的初始化
    bool initData();
    //创建(初始化)卡牌翻转动画
    bool initAnimation();
    //判断卡牌节点所在矩形域是否包含触摸点
    bool containsTouchLocation(CCTouch* touch);
    //获取卡牌节点所在矩形
    CCRect rect();
    inline std::string getOreNameFromCard(){return m_oreName;}
    inline bool getIsOpenFromCard(){return m_isOpen;}
    inline void setHasOreForCard(bool flag){m_hasOre=flag;}
    inline bool getHasOreFromCard(){return m_hasOre;}
    inline bool getIsAcutionDone(){return m_isActionDone;}
    inline void setHasBeenTouched(bool istouched){m_hasBeenTouched=istouched;}
    inline bool getHasBeenTouched(){return m_hasBeenTouched;}
    CREATE_FUNC(CardNode);
    //卡牌执行完一次动作(close/open)后的回掉
    void finishActionCall();
private:
    //
    bool m_hasBeenTouched;
    //卡牌一次翻转动作是否执行完成
    bool m_isActionDone;
    //卡牌含有的矿物名
    std::string m_oreName;
    //卡牌是否翻开标志
    bool m_isOpen;
    //卡牌是否含有矿物
    bool m_hasOre;
    //卡牌里面精灵翻转动作
    CCActionInterval* pActionIn;
    //卡牌外面精灵翻转
    CCActionInterval* pActionOut;
    
    //属于卡牌的三个子节点
    TouchableSprite*   pTouchOreSprite_out;
    TouchableSprite*   pTouchOreSprite_in;
    TouchableSprite*   pOreSprite;

};
#endif /* defined(__HelloCpp__CardNode__) */
