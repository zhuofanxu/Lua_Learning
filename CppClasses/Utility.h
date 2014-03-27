//
//  Utility.h 主要用于处理资源图片数量较多时 通过资源index确定资源名
//  HelloCpp
//
//  Created by xgq on 3/1/14.
//
//

#ifndef __HelloCpp__Utility__
#define __HelloCpp__Utility__

#define NUM_OF_CARD  16
#include <vector.h>
#include <time.h>
#include <cocos2d.h>

USING_NS_CC;
//global variable
//vector动态数组存储矿物资源名
extern std::vector<std::string> OreResourceName;
extern std::vector<std::string> NumberSpriteName;
extern std::vector<std::string>::iterator OreResourceIt;
extern int  OreRandIndex;
extern int  CardRandIndex;


extern std::string OutResourceName;
extern std::string InResourceName;
extern std::string StarResourceName;
extern std::string ErrorResourceName;
extern std::string BackGroundResourceName;
extern std::string MainMenueResourceName;
extern std::string MainMenueImageNameL;
extern std::string MainMenueImageNameS;
extern std::string MainMenueImageNameT;
extern std::string MainMenueImageNameR;
//根据参数n产生 0-(n-1)的随机整数 resource.zie=42
void produceRandomNumber(int n);
//该参数的取值范围：[0-41]
std::string getOreName(int i);

void addResource();

void replaceNumSprite(CCSprite* currNumSpr,int currStarCount);

#endif /* defined(__HelloCpp__Resource__) */
