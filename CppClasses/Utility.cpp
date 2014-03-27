//
//  Utility.cpp
//  HelloCpp
//
//  Created by xgq on 3/5/14.
//
//

#include "Utility.h"

std::vector<std::string> OreResourceName;
std::vector<std::string>::iterator OreResourceIt;
std::vector<std::string> NumberSpriteName;
int  OreRandIndex=0;
int  CardRandIndex=0;
std::string OutResourceName;
std::string InResourceName;
std::string StarResourceName;
std::string BackGroundResourceName;
std::string ErrorResourceName;
std::string MainMenueResourceName;

std::string MainMenueImageNameL;
std::string MainMenueImageNameS;
std::string MainMenueImageNameT;
std::string MainMenueImageNameR;

void produceRandomNumber(int n)
{
    if (n>16) {
        OreRandIndex=rand()%n;
    }
    else
        CardRandIndex=rand()%n;
    // srand(seed);
}

std::string getOreName(int i)
{
    std::string orename;
    std::string strbegin="_";
    //std::string strend=".png";
    orename=OreResourceName[i];
    //从_位置开始，移除子串"_00X.png",长度为8
    orename.erase(orename.find("_"),8);
    
    
    return orename;
}

void replaceNumSprite(CCSprite* currNumSpr,int currStarCount)
{
    CCTexture2D* targetTex=NULL;
    CCSprite*    targetSpr=NULL;
    CCSprite*    currNumSprChild;
    int         Lnum=0;
    int         Mnum=0;
    int         Rnum=0;
    if (!currNumSpr) {
        CCLog("the first argument is NULL...... ");
    }
    else
    {
        if (currStarCount<9)       //当前星星的数量为0-8(下一次的数量为9)数量为个位数的处理方法
        {
            targetSpr=CCSprite::create(NumberSpriteName[currStarCount+1].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->stopAllActions();
            currNumSpr->setTexture(targetTex);
        }
        else if (currStarCount==9)                //当前正好为9,下一次为10(一位数与两为数的过度数字,需要为currNumSpr添加一个子节点)
        {
             //为十位数上添加数字精灵
            targetSpr=CCSprite::create(NumberSpriteName[1].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->stopAllActions();
            currNumSpr->setTexture(targetTex);
            //为个位数上添加数字精灵
           
        
            currNumSprChild=CCSprite::create(NumberSpriteName[0].c_str());;
            currNumSprChild->retain();
           // currNumSprChild->setTexture(targetTex);
            currNumSprChild->setTag(0);
            currNumSpr->addChild(currNumSprChild);
            currNumSprChild->setAnchorPoint(ccp(0, 0));
            currNumSprChild->setPosition(ccp(20, 0));
        }
        else if (10<=currStarCount&&currStarCount<99)//当前星星的数量为10-98(最多下一次99)数量为十位数的处理方法
        {
            //取整，得到十位上的数字
            Lnum=(currStarCount+1)/10;
            targetSpr=CCSprite::create(NumberSpriteName[Lnum].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->stopAllActions();
            currNumSpr->setTexture(targetTex);
            //取余，得到个位上的数字
            Rnum=(currStarCount+1)%10;
            targetSpr=CCSprite::create(NumberSpriteName[Rnum].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->getChildByTag(0)->stopAllActions();
            ((CCSprite*)(currNumSpr->getChildByTag(0)))->setTexture(targetTex);
            
        }
        else if (currStarCount==99)        //当前正好等于99，下一次100(二位数与三位数的过度，要添加子节点)
        {
            //为百位数上添加数字精灵
            targetSpr=CCSprite::create(NumberSpriteName[1].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->stopAllActions();
            currNumSpr->setTexture(targetTex);
            //为十位数上添加数字精灵
            targetSpr=CCSprite::create(NumberSpriteName[0].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSprChild=(CCSprite*)currNumSpr->getChildByTag(0);
            currNumSprChild->stopAllActions();
            currNumSprChild->setTexture(targetTex);
            //为新添加的子节点(个位数)添加数字精灵
            CCSprite* tempChild=CCSprite::create(NumberSpriteName[0].c_str());
            tempChild->retain();
            tempChild->setTag(0);
            currNumSprChild->addChild(tempChild);
            tempChild->setAnchorPoint(ccp(0, 0));
            tempChild->setPosition(ccp(20, 0));
          }
        else if (100<=currStarCount&&currStarCount<999) //当前星星的数量为100-998(最大下一次999)数量为十位数的处理方法
        {
            //除以100取整，得到百位上的数字
            Lnum=(currStarCount+1)/100;
            targetSpr=CCSprite::create(NumberSpriteName[Lnum].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->stopAllActions();
            currNumSpr->setTexture(targetTex);
            //除以10取整，在除以10取余 得到十位上的数字
            Mnum=(currStarCount+1)/10;
            Mnum=Mnum%10;
            targetSpr=CCSprite::create(NumberSpriteName[Mnum].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            currNumSpr->getChildByTag(0)->stopAllActions();
            ((CCSprite*)(currNumSpr->getChildByTag(0)))->setTexture(targetTex);
            //除以10，取余，得到个位上的数字
            Rnum=(currStarCount+1)%10;
            targetSpr=CCSprite::create(NumberSpriteName[Rnum].c_str());
            targetSpr->retain();
            targetTex=targetSpr->getTexture();
            ((CCSprite*)(currNumSpr->getChildByTag(0)->getChildByTag(0)))->stopAllActions();
            ((CCSprite*)(currNumSpr->getChildByTag(0)->getChildByTag(0)))->setTexture(targetTex);
        }
        else
        {
            //do nothing
            CCLog("The max numbers of star suppose is 999 currently if more bigger than 999,then it'll do nothing! ");
        }
    }
    
    
}

void addResource()
{
    static bool hasCalled=false;
    //OreResourceName[2].size();
    if (!hasCalled) {
        
    
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_0.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_01.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_02.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_03.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_04.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_05.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_06.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_07.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_08.png");
    NumberSpriteName.push_back("泡泡龙数字/跳字绿_09.png");
   
    OreResourceName.push_back("光辉石_000.png");
    OreResourceName.push_back("夜明珠_001.png");
    OreResourceName.push_back("太阳石_002.png");
    OreResourceName.push_back("太阴石_003.png");
    OreResourceName.push_back("混沌珠_004.png");
    OreResourceName.push_back("祖母绿_005.png");
    OreResourceName.push_back("羊脂玉_006.png");
    OreResourceName.push_back("鸡血石_007.png");
    OreResourceName.push_back("龙血石_008.png");
    OreResourceName.push_back("气运石_009.png");
    OreResourceName.push_back("神性_010.png");
    OreResourceName.push_back("精血_011.png");
    OreResourceName.push_back("舍利_012.png");
    OreResourceName.push_back("血脉_013.png");
    OreResourceName.push_back("造化残片_014.png");
    OreResourceName.push_back("魂魄_015.png");
    OreResourceName.push_back("鳞甲_016.png");
    OreResourceName.push_back("世界之根_017.png");
    OreResourceName.push_back("世界树种_018.png");
    OreResourceName.push_back("人参果_019.png");
    OreResourceName.push_back("晨曦之辉_020.png");
    OreResourceName.push_back("欲望之种_021.png");
    OreResourceName.push_back("石髓_022.png");
    OreResourceName.push_back("世界碎片_023.png");
    OreResourceName.push_back("地心结核_024.png");
    OreResourceName.push_back("寒铁_025.png");
    OreResourceName.push_back("星辰金精_026.png");
    OreResourceName.push_back("神格天晶_027.png");
    OreResourceName.push_back("精钢_028.png");
    OreResourceName.push_back("陨铁_029.png");
    OreResourceName.push_back("首阳铜_030.png");
    OreResourceName.push_back("魔纹钢_031.png");
    OreResourceName.push_back("世界树枝_032.png");
    OreResourceName.push_back("圣诞树_033.png");
    OreResourceName.push_back("建木条_034.png");
    OreResourceName.push_back("扶桑木_035.png");
    OreResourceName.push_back("桂支_036.png");
    OreResourceName.push_back("橄榄树_037.png");
    OreResourceName.push_back("沙罗树_038.png");
    OreResourceName.push_back("菩提树_039.png");
    OreResourceName.push_back("金苹果树_040.png");
    OreResourceName.push_back("铁树_041.png");
    
    OutResourceName="挖矿_牌面.png";
    InResourceName="挖矿_牌底.png";
    StarResourceName="泡泡龙_星星.png";
    ErrorResourceName="挖矿_错误.png";
    BackGroundResourceName="挖矿_底.png";
    MainMenueResourceName="XGT采集.png";
    MainMenueImageNameL="野外矿坑.png";
    MainMenueImageNameS="野外森林.png";
    MainMenueImageNameT="皇家矿坑.png";
    MainMenueImageNameR="皇家庄园.png";
        hasCalled=true;
    }
    
}

