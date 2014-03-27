--常量

local outRname = "images/littleGameImages/挖矿_牌面.png"
local inRname="images/littleGameImages/挖矿_牌底.png"
local errorRname="images/littleGameImages/挖矿_错误.png"
local starRname="images/littleGameImages/泡泡龙_星星.png"

local digitMulitR="images/fight/跳字绿_乘.png"
local kDigitPrefix = "fight/跳字绿_"
local digitPrefixR="images/fight/跳字绿_"
--local NumberSpriteName[0]="images/fight/跳字绿_0.png"
--与动作相关的
local IN_AngleZ=270 --里面卡牌起始z轴角度值
local IN_DeltaZ=90  --里面卡牌旋转的z轴角度值
local OUT_AngleZ=0
local OUT_DeltaZ=90
local Duration=0.3
local NumberSpriteName={}
--产生[1,16]之间的随机整数
function produceRandomNumber(x)
    local rand=math.random(x)
    rand=getIntPart(rand)
    return rand
end
--lua对一个number型取整
function getIntPart(x)
    if math.ceil(x)==x then
         x=math.ceil(x)
    else
         x=math.ceil(x)-1
    end
    return x
end

for i=0,9 do
    NumberSpriteName[i]=digitPrefixR..""..i..""..".png"
end


function replaceNumSprite(currNumSpr,currStarCount)
    --print(currStarCount,currNumSpr)
    local targeTex=nil 
    local targetSpr=nil
    local currNumSprChild=nil
    local currNumSprChildChild=nil
    local Lnum=0 
    local Mnum=0
    local Rnum=0
    -- if not currNumSpr then
    --     CCLuaLog("replaceNumSprite函数第一参数为空")
    -- else
        if currStarCount<9 then 
            targetSpr=CCSprite:create(NumberSpriteName[currStarCount+1])
            targetTex=targetSpr:getTexture()
            currNumSpr:stopAllActions()
            currNumSpr:setTexture(targetTex)
        elseif currStarCount==9 then 
            targetSpr=CCSprite:create(NumberSpriteName[1])
            targetTex=targetSpr:getTexture()
            currNumSpr:stopAllActions()
            currNumSpr:setTexture(targetTex)
            currNumSprChild=CCSprite:create(NumberSpriteName[0])
            currNumSprChild:setTag(0)
            currNumSpr:addChild(currNumSprChild)
            currNumSprChild:setAnchorPoint(ccp(0, 0))
            currNumSprChild:setPosition(ccp(40, 0))
        elseif currStarCount>=10 and currStarCount<99 then 
            Lnum=(currStarCount+1)/10
            Lnum=getIntPart(Lnum)
            --print("----------------")
            --print(Lnum)
            --print("----------------")
            --print("Lnum---",NumberSpriteName[Lnum])
            targetSpr=CCSprite:create(NumberSpriteName[Lnum])
            --print("----------------")
            --print(Lnum,targetSpr)
            --print("----------------")
            targetTex=targetSpr:getTexture()
            currNumSpr:stopAllActions()
            currNumSpr:setTexture(targetTex)
            --取余，得到个位上的数字
            Rnum=(currStarCount+1)%10
            Rnum=getIntPart(Rnum)
            --print("Rnum---",NumberSpriteName[Rnum])
            targetSpr=CCSprite:create(NumberSpriteName[Rnum])
            
            targetTex=targetSpr:getTexture()
            tolua.cast(currNumSpr:getChildByTag(0),"CCSprite"):stopAllActions()
            --print("currNumSpr:getChildByTag(0),targeTex",currNumSpr:getChildByTag(0),targetTex)
            --转成ccsprite型
            tolua.cast(currNumSpr:getChildByTag(0),"CCSprite"):setTexture(targetTex)
        elseif currStarCount==99 then
            targetSpr=CCSprite:create(NumberSpriteName[1])
            targetTex=targetSpr:getTexture()
            currNumSpr:stopAllActions()
            currNumSpr:setTexture(targetTex)
            --为十位数上添加数字精灵
            targetSpr=CCSprite:create(NumberSpriteName[0])
            targetTex=targetSpr:getTexture()
            currNumSprChild=currNumSpr:getChildByTag(0)
            tolua.cast(currNumSprChild,"CCSprite"):stopAllActions()
            tolua.cast(currNumSprChild,"CCSprite"):setTexture(targetTex)
            --为新添加的子节点(个位数)添加数字精灵
            local tempChild=CCSprite:create(NumberSpriteName[0])
            tempChild:setTag(0)
            currNumSprChild:addChild(tempChild)
            tempChild:setAnchorPoint(ccp(0, 0))
            tempChild:setPosition(ccp(40, 0))
        elseif currStarCount>=100 and currStarCount<999 then 
            Lnum=(currStarCount+1)/100
            Lnum=getIntPart(Lnum)
            targetSpr=CCSprite:create(NumberSpriteName[Lnum])
            targetTex=targetSpr:getTexture()
            currNumSpr:stopAllActions()
            currNumSpr:setTexture(targetTex)
            --除以10取整，在除以10取余 得到十位上的数字
            Mnum=(currStarCount+1)/10
            Mnum=getIntPart(Mnum)
            Mnum=Mnum%10
            Mnum=getIntPart(Mnum)
            targetSpr=CCSprite:create(NumberSpriteName[Mnum])
            targetTex=targetSpr:getTexture()
            tolua.cast(currNumSpr:getChildByTag(0),"CCSprite"):stopAllActions()
            tolua.cast(currNumSpr:getChildByTag(0),"CCSprite"):setTexture(targetTex)
            --除以10，取余，得到个位上的数字
            Rnum=(currStarCount+1)%10
            getIntPart(Rnum)
            targetSpr=CCSprite:create(NumberSpriteName[Rnum])
            targetTex=targetSpr:getTexture()
            tolua.cast(currNumSpr:getChildByTag(0):getChildByTag(0),"CCSprite"):stopAllActions()
            tolua.cast(currNumSpr:getChildByTag(0):getChildByTag(0),"CCSprite"):setTexture(targetTex)
        elseif currStarCount>=1000 then
            --do nothing
            --CCLuaLog("一次星星数量超过999,达到上限")
        end




    -- body
end








--卡牌类
CardNode={
   --m_isActionDone=true,      --卡牌一次翻转动作是否完成
   -- m_isHasStar=false,        --卡牌是否含有星星
    --m_spriteOut=nil,          --卡牌外精灵
    --m_spriteIn=nil,           --卡牌里精灵
    --m_sprite=nil,             --卡牌可能含有的星星精灵/错误精灵
   --m_actionOut=nil,          --卡牌外精灵旋转动作
   -- m_actionIn=nil,           --卡牌里精灵旋转动作
}

function CardNode:new( ... )
	local obj = {}
	setmetatable(obj,self)
	self.__index=self
    obj.m_node = CCNode:create()
    obj.m_isHasStar=false
    obj.m_hasBeenTouched=false        --每一轮卡牌被触摸标记
    obj.m_isActionDone=true
    obj.m_spriteIn=CCSprite:create(inRname)
    obj.m_spriteOut=CCSprite:create(outRname)
    obj.m_sequenceActionOut=nil         
    obj.m_sequenceActionIn=nil
    obj.m_isOpened=false
    --print(obj.m_spriteOut,obj.m_spriteIn)
    if not obj.m_isHasStar then
        obj.m_sprite=CCSprite:create(errorRname)
        --print("不含有星星:",obj.m_sprite,self.m_sprite)
    else
        obj.m_sprite=CCSprite:create(starRname)
        obj.m_sprite:setPosition(ccp(11,11))
        --print("含有星星:",obj.m_sprite)
    end
    --print(obj.m_spriteIn,obj.m_spriteOut,obj.m_sprite)
    if obj.m_spriteIn~=nil and obj.m_spriteOut~=nil and obj.m_sprite~=nil then
            obj.m_node:addChild(obj.m_spriteIn)
            obj.m_sprite:setAnchorPoint(ccp(0,0))
            obj.m_spriteIn:addChild(obj.m_sprite)
            obj.m_node:addChild(obj.m_spriteOut)
            obj.m_node:setContentSize(obj.m_spriteOut:getContentSize()) --设置卡牌节点与卡牌外精灵一样大小
            --CCLuaLog("卡牌节点挂接子节点成功!")
        else
            CCLuaLog("xxxx卡牌节点挂接子节点失败xxxx")
        end
	return obj
	-- body
end
--卡牌执行完一次动作(close/open)后的回掉
function CardNode:finishActionCall( ... )
	self.m_isActionDone=true
	--print(self.m_isActionDone)
	-- body
end
function CardNode:openCard( ... )
	self.m_isActionDone=false
    self.m_isOpened=true
	self.m_spriteIn:setVisible(false)
   -- print("动作有效检测:",self.m_sequenceActionIn,self.m_sequenceActionOut)
   -- print("精灵检测:",self.m_spriteIn,self.m_spriteOut)
    self:initAnimation()
	self.m_spriteIn:runAction(self.m_sequenceActionIn)
   -- print("翻转切换.....")
	self.m_spriteOut:runAction(self.m_sequenceActionOut)
	-- body
end
function CardNode:closeCard( ... )
	self.m_isActionDone=false
    self.m_isOpened=false
    --IN_DeltaZ=-IN_DeltaZ  --里面卡牌旋转的z轴角度值
    --OUT_DeltaZ=-OUT_DeltaZ
	self.m_spriteOut:setVisible(false)
    self:initAnimation()
	self.m_spriteOut:runAction(self.m_sequenceActionIn)
	self.m_spriteIn:runAction(self.m_sequenceActionOut)
    --IN_DeltaZ=-IN_DeltaZ
    --OUT_DeltaZ=-OUT_DeltaZ
	-- body
end

--卡牌动作初始化
function CardNode:initAnimation( ... )
    local actionArrayIn=CCArray:create()
    local actionArrayOut=CCArray:create()
    --延时动作
    local delaAction =CCDelayTime:create(Duration/2)
    --print("延时动作里",delaAction)
    --显示动作
    local showAction=CCShow:create()
    --摄像机动作
    local cameraAction=CCOrbitCamera:create(Duration/2, 1, 0,IN_AngleZ, IN_DeltaZ, 0, 0)
    --动作执行完回调
    local callFun=CCCallFunc:create(function()self:finishActionCall()end)
    actionArrayIn:addObject(delaAction)
    actionArrayIn:addObject(showAction)
    actionArrayIn:addObject(cameraAction)
    actionArrayIn:addObject(callFun)
   -- print("四个动作",delaAction,showAction,cameraAction,callFun)
    local cameraAction=CCOrbitCamera:create(Duration/2, 1, 0, OUT_AngleZ, OUT_DeltaZ, 0, 0)
    local hideAction=CCHide:create()
    local delayTime=CCDelayTime:create(Duration/2)
    --print("延时动作外",delayTime)
    --print("三个动作外",cameraAction,hideAction,delayTime)
    actionArrayOut:addObject(cameraAction)
    actionArrayOut:addObject(hideAction)
    actionArrayOut:addObject(delayTime)
    --print("动作数组检测",actionArrayOut,actionArrayIn)
    self.m_sequenceActionOut=CCSequence:create(actionArrayOut)
    self.m_sequenceActionIn=CCSequence:create(actionArrayIn)
    --print("翻转动作:",self.m_sequenceActionOut,self.m_sequenceActionOut)
    if (self.m_sequenceActionOut~=nil) and (self.m_sequenceActionIn~=nil) then
      -- CCLuaLog("卡牌动作创建成功") 
    else 
       CCLuaLog("xxxx卡牌动作创建失败xxxx")
    end
	-- body
end
function CardNode:rect( ... )
    local size =self.m_node:getContentSize()
    --print(size,size.width,size.height)
    local x, y =self.m_node:getPosition()
   -- print(x,y)
   -- print("卡牌范围:",x-size.width/2,x+size.width/2,y-size.height/2,y+size.height/2)
    return CCRectMake(x-size.width/2,y-size.height/2,size.width,size.height)
    -- body
end
--判断卡牌节点所在矩形域是否包含触摸点
function CardNode:containsTouchLocation(x,y)
    --local touchPoint =touch:getLocationInView()
    --touchPoint=CCDirector:sharedDirector():convertToGL(touchPoint)
    local touchPoint =ccp(x,y)
    --print("触摸点",touchPoint)
    return self:rect():containsPoint(touchPoint)
    -- body
end
function CardNode:updateStarSprite()
    local targetTex=nil
    local targetSpr=nil
    if self.m_isHasStar then
        targetSpr=CCSprite:create(starRname)
        targetTex=targetSpr:getTexture()
        self.m_sprite:setTexture(targetTex)
    else
        targetSpr=CCSprite:create(errorRname)
        targetTex=targetSpr:getTexture()
        self.m_sprite:setTexture(targetTex)
    end
end



--采矿控制类
CollectStar={}
--常量
local winSize=CCDirector:sharedDirector():getWinSize()
local progressBackR="images/littleGameImages/挖矿_时间底.png"
local backGroundR="images/littleGameImages/挖矿_底.png"
local progressR="images/littleGameImages/挖矿_时间进度.png"
local funnelR="images/littleGameImages/挖矿_漏斗.png"
local rewardsR="images/littleGameImages/挖矿_奖励.png"
local numOfCard=16
local gameTotalTime=35    --游戏总时间 
--游戏状态相关的变量
local isShow=false
local isClose=false
local gameElapse=0        --游戏总计时
local duringChangeRound=0 --本回合结束到下回合开始的停留/经历的时间
local beginAutoCloseTime=false
local autoClose=0         --自动关闭向玩家打开的含有星星卡牌间隔时间
--记录每一轮分数
local roundOneScore=0
local roundTwoScore=0
local roundThreeScore=0
local roundFourScore=0
local roundFiveScore=0

function CollectStar:new(gameOverCallFunc)

    --m_layer=nil,          --游戏场景层
    self.m_gameLevel=1        --区别于野外矿坑与皇家矿坑,默认为野外矿坑
    self.m_gameTime=0       --游戏进行时间
    self.m_gameTimer=nil
    self.m_gameScore=0     --游戏分数
    --self.m_numSprite=nil,      --计分的数字精灵
    --m_timeProgressL=nil,  --表示时间进度
    --m_timeProgressR=nil,
    self.m_cardArray={}       --卡牌数组
    self.m_round=0
    self.m_shouldChangeRound=true
    --gameOverCallFunc=nil    --游戏结束回调
    print("-----m_shouldChangeRound--------",self.m_shouldChangeRound)
    local obj ={}
    setmetatable(obj,self)
    self.__index=self
    self.m_layer=CCLayer:create()         --游戏层
    --注册触摸回调处理函数
    obj.m_layer:registerScriptTouchHandler(function(eventType,x,y)
        self:onTouch(eventType,x,y)
    end)
    self.gameOverCallFunc = gameOverCallFunc
    --游戏背景精灵
    local backGroundSp =CCSprite:create(backGroundR)
    backGroundSp:setPosition(winSize.width/2,winSize.height/2)
    obj.m_layer:addChild(backGroundSp,0) 
    --游戏卡牌UI
    for i=1,numOfCard do
        obj.m_cardArray[i]=CardNode:new()
        --obj.m_cardArray[i]:initAnimation()
        --obj.m_cardArray[i]:initData()
    end
    --在游戏主场景整齐摆放4x4卡牌
    for i=1, numOfCard/4 do
        for j=1,numOfCard/4 do
            local card =obj.m_cardArray[i+(j-1)*4]
            card.m_node:setPosition((winSize.width-card.m_node:getContentSize().width*4)/2+(i-1/2)*card.m_node:getContentSize().width+i*winSize.width/150-10,winSize.height-(j*winSize.height/150+card.m_node:getContentSize().height*(j-1/2)+(winSize.height-card.m_node:getContentSize().height*4)/2))
            self.m_layer:addChild(card.m_node,1)
        end
    end
    --序列帧动画
    
    --skill:setPlay(true)
    --进度条背景精灵
    local progressSpbackL=CCSprite:create(progressBackR) 
    --progressSpbackL:setAnchorPoint(ccp(0,0))
    progressSpbackL:setPosition(winSize.width/2-370,winSize.height/2+100)
    self.m_layer:addChild(progressSpbackL,1)
    local progressSpbackR=CCSprite:create(progressBackR)
    --progressSpbackR:setAnchorPoint(ccp(0,0))
    progressSpbackR:setPosition(winSize.width/2+390,winSize.height/2+100)
    self.m_layer:addChild(progressSpbackR,1)
    --进度精灵
    local progressSp=CCSprite:create(progressR)    

    self.m_timeProgressL=CCProgressTimer:create(progressSp)
    self.m_timeProgressL:setScaleY(24.35)
    self.m_timeProgressL:setType(kCCProgressTimerTypeBar)
    self.m_timeProgressL:setMidpoint(ccp(1, 0))
    --设置为高度变化(y轴)
    self.m_timeProgressL:setBarChangeRate(ccp(0, 1))
    --self.m_timeProgressL:setPercentage(100)
    --self.m_timeProgressL:setAnchorPoint(ccp(0,0))
    self.m_timeProgressL:setPosition(winSize.width/2-370,winSize.height/2+100)
    self.m_layer:addChild(self.m_timeProgressL,1)
    --右边时间进度条
    self.m_timeProgressR=CCProgressTimer:create(progressSp)
    self.m_timeProgressR:setScaleY(24.35)
    --设置为水平或垂直进度条
    self.m_timeProgressR:setType(kCCProgressTimerTypeBar)
    --设置进度从下到上的变化
    self.m_timeProgressR:setMidpoint(ccp(1, 0))
    --设置为高度变化(y轴)
    self.m_timeProgressR:setBarChangeRate(ccp(0, 1))
    --self.m_timeProgressR:setPercentage(100)
    --self.m_timeProgressR:setAnchorPoint(ccp(0, 0))
    self.m_timeProgressR:setPosition(winSize.width/2+390,winSize.height/2+100)
    self.m_layer:addChild(self.m_timeProgressR,1)
    --通过gamelevel判断是否添加奖励
    --if self.m_gameLevel==2 then
        local rewards = CCSprite:create(rewardsR) 
        --rewards:setAnchorPoint(ccp(0,0))
        rewards:setPosition(winSize.width/2-370,winSize.height/2-70)
        self.m_layer:addChild(rewards,2)
    --end
    local funnel=CCSprite:create(funnelR)
    --funnel:setAnchorPoint(ccp(0,0))
    funnel:setPosition(winSize.width/2+390,winSize.height/2-70)
    self.m_layer:addChild(funnel,2)
    
    --表示star数量的ui
    local star =CCSprite:create(starRname)
    star:setScale(0.7)
    star:setPosition(progressSpbackL:getContentSize().width*2+10,30)
    self.m_layer:addChild(star,1)

    local mulit=CCSprite:create(digitMulitR)
    mulit:setScale(0.8)
    mulit:setPosition(progressSpbackL:getContentSize().width*2+60,30)
    self.m_layer:addChild(mulit,1)
    --表示socre的数字
    self.m_numSprite =CCSprite:create(NumberSpriteName[0])
    self.m_numSprite:setPosition(progressSpbackL:getContentSize().width*2+100,30)
    self.m_numSprite:setScale(0.8)
    self.m_layer:addChild(self.m_numSprite,1)
    --开启定时更新
    self.m_layer:scheduleUpdateWithPriorityLua(function(dt)
            self:update(dt)

        end, 0)
    print("------开启定时器-------")
    --设置随机种子
    math.randomseed(os.time())
    self.m_gameTimer=Schedule:createScheduleWithInterval(1, function()
         obj.m_gameTime=obj.m_gameTime+1
         --print("--m_gameTime--",obj.m_gameTime)
         if obj.m_gameTime>=gameTotalTime then 
             obj:showResult()

         end
    end,gameTotalTime)    

    return obj 
    -- body
end

-- 显示结算界面
function CollectStar:showResult()
    print("showResult")
    self.m_layer:setTouchEnabled(false)
    self.m_layer:unregisterScriptTouchHandler()
    local resultWin = CWidgetWindow:create()
    resultWin:setTouchEnabled(true)
    self.m_layer:addChild(resultWin, 10)
    local spriteFrame = MCLoader:sharedMCLoader():loadSpriteFrame("小游戏结算底.png")
    local resultBg = CImageView:createWithSpriteFrame(spriteFrame)
    resultBg:setAnchorPoint(ccp(0.5, 0.5))
    resultBg:setPosition(winSize.width/2, winSize.height/2)
    resultWin:addChild(resultBg)
    local size = resultBg:getContentSize()

    spriteFrame = MCLoader:sharedMCLoader():loadSpriteFrame("时间到.png")
    local timeLabel = CImageView:createWithSpriteFrame(spriteFrame)
    timeLabel:setPosition(size.width/2, 280)
    resultBg:addChild(timeLabel)

    local star = MCLoader:sharedMCLoader():loadSprite("popodragon/泡泡龙_星星.png")
    star:setAnchorPoint(ccp(0.5, 0.5))
    star:setPosition(winSize.width/2 - 50, 300)
    resultWin:addChild(star, 1)

    local digitMulti = MCLoader:sharedMCLoader():loadSprite("fight/跳字绿_乘.png")
    digitMulti:setAnchorPoint(ccp(0.5, 0.5))
    digitMulti:setPosition(star:getPositionX() + digitMulti:getContentSize().width + 10, 300)
    resultWin:addChild(digitMulti, 1)
    local scoreX = digitMulti:getPositionX() + digitMulti:getContentSize().width*0.6

    local d = {}
    local s = self.m_gameScore
    repeat
        local r = s%10
        table.insert(d, 1, r)
        s = math.floor(s/10)
    until s == 0
    local x = scoreX
    for k, v in ipairs(d) do
        local digit = MCLoader:sharedMCLoader():loadSprite(kDigitPrefix .. v .. ".png")
        digit:setAnchorPoint(ccp(0.5, 0.5))
        digit:setPosition(x, 300)
        digit:setScale(0.6)
        x = x + digit:getContentSize().width*0.6
        resultWin:addChild(digit, 1)
    end

    local button = CButton:create()
    button:setTouchEnabled(true)
    button:setPosition(winSize.width/2, 210)
    spriteFrame = MCLoader:sharedMCLoader():loadSpriteFrame("按钮二字_01.png")
    button:setNormalSpriteFrame(spriteFrame)
    spriteFrame = MCLoader:sharedMCLoader():loadSpriteFrame("按钮二字_02.png")
    button:setSelectedSpriteFrame(spriteFrame)
    button:setOnClickScriptHandler(function()
        self:exchangeClick()
    end)
    resultWin:addChild(button)
    spriteFrame = MCLoader:sharedMCLoader():loadSpriteFrame("按钮字_兑换.png")
    local exchangeImage = CImageView:createWithSpriteFrame(spriteFrame)
    exchangeImage:setPosition(55, 30)
    button:addChild(exchangeImage)
end

-- 结算界面兑换按钮
function CollectStar:exchangeClick()
    print("exchangeClick")
    if self.gameOverCallFunc then
        self.gameOverCallFunc()
    end
end
--游戏退出清理
function CollectStar:delete( ... )
      roundOneScore=0
      roundTwoScore=0
      roundThreeScore=0
      roundFourScore=0
      roundFiveScore=0
      isShow=false
      isClose=false
      gameElapse=0        --游戏总计时
      duringChangeRound=0 --本回合结束到下回合开始的停留/经历的时间
      beginAutoCloseTime=false
      autoClose=0         --自动关闭向玩家打开的含有星星卡牌间隔时间
      --self.m_gameTime=0
    if self.m_gameTimer then
        self.m_gameTimer:stop()
        print("---干掉计时器---")
        self.m_gameTimer = nil
    end
    if self.m_layer then 
       
        self.m_layer:unscheduleUpdate()
        self.m_layer:removeFromParentAndCleanup(true)
       
        self.m_layer = nil
    end
    -- body
end

function CollectStar:onTouch(eventType,x,y)
  if self.m_round==1 then
    for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
           -- print("触摸到卡片",i)
            if self.m_cardArray[i].m_isHasStar and (not self.m_cardArray[i].m_hasBeenTouched) then
                self.m_cardArray[i].m_hasBeenTouched=true
                --if self.m_skill==nil then 
                    self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
                    self.m_skill:setRate(1)
                    self.m_skill:setAutoRemoveWithTimes(1)
                    --self.m_skill:setAnchorPoint(ccp(0.5,0.5))
                    self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
                    local x,y=self.m_cardArray[i].m_node:getPosition()
                    --x=x
                    y=y+20
                    self.m_skill:setPosition(x,y)

                    self.m_layer:addChild(self.m_skill,2)
                    self.m_skill:setPlay(true)
                --end 
                replaceNumSprite(self.m_numSprite,self.m_gameScore)
                self.m_gameScore=self.m_gameScore+1
                roundOneScore=roundOneScore+1
                if self.m_cardArray[i].m_isOpened then                    --玩家在卡牌自动关闭前就触摸到了有星星的卡牌
                    for j=1,numOfCard do
                        if self.m_cardArray[j].m_isHasStar and j~=i then  --除了已经触摸到的卡牌,其余的有星星的卡牌全部提前关闭
                            self.m_cardArray[j]:closeCard()
                        end
                    end
                    print("----提前关闭提示卡牌-----")
                else                                                      --正常情况下的触摸
                    self.m_cardArray[i]:openCard()
                end
            elseif not self.m_cardArray[i].m_isHasStar then
                self.m_cardArray[i].m_hasBeenTouched=true
                if not self.m_cardArray[i].m_isOpened  then
                    self.m_cardArray[i]:openCard()
                end
                self.m_shouldChangeRound=true
                self.m_layer:setTouchEnabled(false)                      --关闭触摸直到下一轮开始
                print("--------挖矿错误改变m_shouldChangeRound---------",self.m_shouldChangeRound)
            end
        end
    end
  elseif self.m_round==2 then
     for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
            --print("触摸到卡片",i)
            
            if self.m_cardArray[i].m_isHasStar and (not self.m_cardArray[i].m_hasBeenTouched) then
                self.m_cardArray[i].m_hasBeenTouched=true
                --if not self.m_skill then 
                    self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
                    self.m_skill:setRate(1)
                    self.m_skill:setAutoRemoveWithTimes(1)
                    self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
                    local x,y=self.m_cardArray[i].m_node:getPosition()
                    --x=x-37
                    y=y+20
                    self.m_skill:setPosition(x,y)

                    self.m_layer:addChild(self.m_skill,2)
                    self.m_skill:setPlay(true)
                --end 
                replaceNumSprite(self.m_numSprite,self.m_gameScore)
                self.m_gameScore=self.m_gameScore+1
                roundTwoScore=roundTwoScore+1
                if self.m_cardArray[i].m_isOpened then                    --玩家在卡牌自动关闭前就触摸到了有星星的卡牌
                    for j=1,numOfCard do
                        if self.m_cardArray[j].m_isHasStar and j~=i then  --除了已经触摸到的卡牌,其余的有星星的卡牌全部提前关闭
                            self.m_cardArray[j]:closeCard()
                        end
                    end
                    print("----提前关闭提示卡牌-----")
                else                                                      --正常情况下的触摸
                    self.m_cardArray[i]:openCard()
                end
            elseif not self.m_cardArray[i].m_isHasStar then
                self.m_cardArray[i].m_hasBeenTouched=true
                if not self.m_cardArray[i].m_isOpened  then
                    self.m_cardArray[i]:openCard()
                end
                self.m_layer:setTouchEnabled(false)                      --关闭触摸直到下一轮开始
                self.m_shouldChangeRound=true
            end
        end
    end

  elseif self.m_round==3 then
     for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
          --  print("触摸到卡片",i)
            if self.m_cardArray[i].m_isHasStar and (not self.m_cardArray[i].m_hasBeenTouched) then
                self.m_cardArray[i].m_hasBeenTouched=true
                --if self.m_skill==nil then 
                    self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
                    self.m_skill:setRate(1)
                    self.m_skill:setAutoRemoveWithTimes(1)
                    self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
                    local x,y=self.m_cardArray[i].m_node:getPosition()
                    y=y+20
                    self.m_skill:setPosition(x,y)

                    self.m_layer:addChild(self.m_skill,2)
                    self.m_skill:setPlay(true)
                --end
                replaceNumSprite(self.m_numSprite,self.m_gameScore)
                self.m_gameScore=self.m_gameScore+1
                roundThreeScore=roundThreeScore+1
                if self.m_cardArray[i].m_isOpened then                    --玩家在卡牌自动关闭前就触摸到了有星星的卡牌
                    for j=1,numOfCard do
                        if self.m_cardArray[j].m_isHasStar and j~=i then  --除了已经触摸到的卡牌,其余的有星星的卡牌全部提前关闭
                            self.m_cardArray[j]:closeCard()
                        end
                    end
                    print("----提前关闭提示卡牌-----")
                else                                                      --正常情况下的触摸
                    self.m_cardArray[i]:openCard()
                end
            elseif not self.m_cardArray[i].m_isHasStar  then
                self.m_cardArray[i].m_hasBeenTouched=true
                if not self.m_cardArray[i].m_isOpened  then
                    self.m_cardArray[i]:openCard()
                end
                self.m_layer:setTouchEnabled(false)                      --关闭触摸直到下一轮开始
                self.m_shouldChangeRound=true
            end
        end
    end

  elseif self.m_round==4 then
     for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
           -- print("触摸到卡片",i)
            
            if self.m_cardArray[i].m_isHasStar and (not self.m_cardArray[i].m_hasBeenTouched) then
                self.m_cardArray[i].m_hasBeenTouched=true
               -- if self.m_skill==nil then 
                    self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
                    self.m_skill:setRate(1)
                    self.m_skill:setAutoRemoveWithTimes(1)
                    self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
                    local x,y=self.m_cardArray[i].m_node:getPosition()
                    y=y+20
                    self.m_skill:setPosition(x,y)

                    self.m_layer:addChild(self.m_skill,2)
                    self.m_skill:setPlay(true)
                --end 
                replaceNumSprite(self.m_numSprite,self.m_gameScore)
                self.m_gameScore=self.m_gameScore+1
                roundFourScore=roundFourScore+1
                if self.m_cardArray[i].m_isOpened then                    --玩家在卡牌自动关闭前就触摸到了有星星的卡牌
                    for j=1,numOfCard do
                        if self.m_cardArray[j].m_isHasStar and j~=i then  --除了已经触摸到的卡牌,其余的有星星的卡牌全部提前关闭
                            self.m_cardArray[j]:closeCard()
                        end
                    end
                    print("----提前关闭提示卡牌-----")
                else                                                      --正常情况下的触摸
                    self.m_cardArray[i]:openCard()
                end
            elseif not self.m_cardArray[i].m_isHasStar  then
                self.m_cardArray[i].m_hasBeenTouched=true 
               if not self.m_cardArray[i].m_isOpened  then
                    self.m_cardArray[i]:openCard()
                end
                self.m_layer:setTouchEnabled(false)                      --关闭触摸直到下一轮开始
                self.m_shouldChangeRound=true
            end
        end
     end
  elseif self.m_round==5 then
     for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
            --print("触摸到卡片",i)
            
            if self.m_cardArray[i].m_isHasStar and (not self.m_cardArray[i].m_hasBeenTouched) then
                self.m_cardArray[i].m_hasBeenTouched=true
                --if self.m_skill==nil then 
                    self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
                    self.m_skill:setRate(1)
                    self.m_skill:setAutoRemoveWithTimes(1)
                    self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
                    local x,y=self.m_cardArray[i].m_node:getPosition()
                    y=y+20
                    self.m_skill:setPosition(x,y)

                    self.m_layer:addChild(self.m_skill,2)
                    self.m_skill:setPlay(true)
                --end
                print("--------",self.m_numSprite,self.m_gameScore)
                replaceNumSprite(self.m_numSprite,self.m_gameScore)
                self.m_gameScore=self.m_gameScore+1
                roundFiveScore=roundFiveScore+1
                if self.m_cardArray[i].m_isOpened then                    --玩家在卡牌自动关闭前就触摸到了有星星的卡牌
                    for j=1,numOfCard do
                        if self.m_cardArray[j].m_isHasStar and j~=i then  --除了已经触摸到的卡牌,其余的有星星的卡牌全部提前关闭
                            self.m_cardArray[j]:closeCard()
                        end
                    end
                    print("----提前关闭提示卡牌-----")
                else                                                      --正常情况下的触摸
                    self.m_cardArray[i]:openCard()
                end
            elseif not self.m_cardArray[i].m_isHasStar  then
               self.m_cardArray[i].m_hasBeenTouched=true 
               if not self.m_cardArray[i].m_isOpened  then
                    self.m_cardArray[i]:openCard()
               end
               self.m_layer:setTouchEnabled(false)                      --关闭触摸直到下一轮开始
                --self.m_shouldChangeRound=true
               --提前退出
               if self.gameOverCallFunc then 
                    self.gameOverCallFunc()
                end 
            end
        end
     end 
  elseif self.m_round==6 then 
    for i=1,numOfCard do
        if self.m_cardArray[i]:containsTouchLocation(x,y) then
            if not self.m_cardArray[i].m_hasBeenTouched then
               self.m_cardArray[i].m_hasBeenTouched=true
               self.m_skill = LYDynamicPicture:createDynamicPicture(0, 18)
               self.m_skill:setRate(1)
               --self.m_skill:setAutoRemoveWithTimes(1)
               self.m_skill:setFollow(self.m_layer, CCSizeMake(0,0), false)
               local x,y=self.m_cardArray[i].m_node:getPosition()
               y=y+20
               self.m_skill:setPosition(x,y)
               self.m_layer:addChild(self.m_skill,2)
               self.m_skill:setPlay(true)
               replaceNumSprite(self.m_numSprite,self.m_gameScore)
               self.m_gameScore=self.m_gameScore+1
            end     
        end
     end      
  end
end 
--用到一些计时变量
--local elapse=0

function CollectStar:update(dt)  
    self:gameLogic(dt)
    if(gameElapse<gameTotalTime) then
        self.m_timeProgressL:setPercentage(100*gameElapse/gameTotalTime)
        self.m_timeProgressR:setPercentage(100*gameElapse/gameTotalTime)
        
    end

end
function CollectStar:enterRound(dt)
    print("--m_round",self.m_round)
    if self.m_round==1 then
        local indexR=produceRandomNumber(16)
       -- print("--产生的随机索引值--")
       -- print(indexR)
        --print("--产生的随机索引值--")
       self.m_cardArray[indexR].m_isHasStar=true
    elseif self.m_round==2 then
        local indexR1=produceRandomNumber(16)
        self.m_cardArray[indexR1].m_isHasStar=true
        local indexR2=produceRandomNumber(16)
        --产生不重复的随机索引
        while indexR2==indexR1 do
            indexR2=produceRandomNumber(16)
        end
        self.m_cardArray[indexR2].m_isHasStar=true
    elseif self.m_round==3 then
        local indexR1=produceRandomNumber(16)
        self.m_cardArray[indexR1].m_isHasStar=true
        local indexR2=produceRandomNumber(16)
        --产生不重复的随机索引
        while indexR2==indexR1 do
            indexR2=produceRandomNumber(16)
        end
        self.m_cardArray[indexR2].m_isHasStar=true
        local indexR3=produceRandomNumber(16)
        while indexR3==indexR2 or indexR3==indexR1 do
            indexR3=produceRandomNumber(16)

        end
        self.m_cardArray[indexR3].m_isHasStar=true
    elseif self.m_round==4 then
        local indexR1=produceRandomNumber(16)
        self.m_cardArray[indexR1].m_isHasStar=true
        local indexR2=produceRandomNumber(16)
        --产生不重复的随机索引
        while indexR2==indexR1 do
            indexR2=produceRandomNumber(16)
        end
        self.m_cardArray[indexR2].m_isHasStar=true
        local indexR3=produceRandomNumber(16)
        while indexR3==indexR2 or indexR3==indexR1 do
            indexR3=produceRandomNumber(16)
        end
        self.m_cardArray[indexR3].m_isHasStar=true
        local indexR4=produceRandomNumber(16)
        while indexR4==indexR3 or indexR4==indexR2 or indexR4==indexR1 do
            indexR4=produceRandomNumber(16)
        end
        self.m_cardArray[indexR4].m_isHasStar=true
    elseif self.m_round==5 then
        local indexR1=produceRandomNumber(16)
        self.m_cardArray[indexR1].m_isHasStar=true
        local indexR2=produceRandomNumber(16)
        --产生不重复的随机索引
        while indexR2==indexR1 do
            indexR2=produceRandomNumber(16)
        end
        self.m_cardArray[indexR2].m_isHasStar=true
        local indexR3=produceRandomNumber(16)
        while indexR3==indexR2 or indexR3==indexR1 do
            indexR3=produceRandomNumber(16)
        end
        self.m_cardArray[indexR3].m_isHasStar=true
        local indexR4=produceRandomNumber(16)
        while indexR4==indexR3 or indexR4==indexR2 or indexR4==indexR1 do
            indexR4=produceRandomNumber(16)
        end
        self.m_cardArray[indexR4].m_isHasStar=true
        local indexR5 = produceRandomNumber(16)
        while indexR5==indexR4 or indexR5==indexR3 or indexR5==indexR2 or indexR5==indexR1 do
            indexR5=produceRandomNumber(16)
        end
        self.m_cardArray[indexR5].m_isHasStar=true
    elseif self.m_round==6 then 
        for i=1,numOfCard do
            self.m_cardArray[i].m_isHasStar=true
        end
    end

    for i=1,numOfCard do
           self.m_cardArray[i]:updateStarSprite()
           --print("--更新精灵--")
    end
end

function CollectStar:exitRound()
   for i=1,numOfCard do
      if self.m_cardArray[i].m_isOpened  then 
          self.m_cardArray[i]:closeCard()
          --print("----关闭之前打开的所有卡牌----")
      end
   end

    --所有卡牌关闭后设置卡牌不含星星
   for i=1,numOfCard do
     self.m_cardArray[i].m_hasBeenTouched=false     --新的回合更新触摸标志到初始化状态
     --if self.m_cardArray[i].m_isActionDown then
     self.m_cardArray[i].m_isHasStar=false
   end
end


function CollectStar:gameLogic(dt)
     gameElapse=gameElapse+dt
     --print("--m_shouldChangeRound:",self.m_shouldChangeRound)
     if gameElapse<gameTotalTime then
        --print("self.m_shouldChangeRound------",self.m_shouldChangeRound)
          if self.m_shouldChangeRound then
              --print("进入游戏逻辑",duringChangeRound)
              duringChangeRound=duringChangeRound+dt
              --print("--duringChangeRound:",duringChangeRound)
              if duringChangeRound>=1 then
                  self:exitRound()
              end
              if duringChangeRound>=3 then
                  self.m_round=self.m_round+1
                  duringChangeRound=0
                  self.m_shouldChangeRound=false
                  print("--m_shouldChangeRound:",self.m_shouldChangeRound)
                  self:enterRound()
                  --print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
                  for i=1,numOfCard do
                      if self.m_cardArray[i].m_isHasStar then 
                         self.m_cardArray[i]:openCard()
                      end
                  end
                  self.m_layer:setTouchEnabled(true)               --开启触摸
                  beginAutoCloseTime=true                          --自动关闭计时开始
              end
          end
     
          if beginAutoCloseTime and self.m_round~=6 then                                   --检测自动关闭提示卡牌
              autoClose=autoClose+dt
              if autoClose>=2 then
                 for i=1,numOfCard do
                    if self.m_cardArray[i].m_isOpened and (not self.m_cardArray[i].m_hasBeenTouched) then
                       self.m_cardArray[i]:closeCard()
                    end
                 end
                 autoClose=0
                 beginAutoCloseTime=false
             end
         end
         if self.m_round==1 then
           -- print("roundOneScore----",roundOneScore)
            if roundOneScore==1 then
              self.m_shouldChangeRound=true
              self.m_layer:setTouchEnabled(false)
            end
         elseif  self.m_round==2 then
            -- print("roundTwoScore----",roundTwoScore)
            if roundTwoScore==2 then 
              self.m_shouldChangeRound=true
              self.m_layer:setTouchEnabled(false)
            end 
         elseif  self.m_round==3 then
            if roundThreeScore==3 then 
              self.m_shouldChangeRound=true
              self.m_layer:setTouchEnabled(false)
            end 
         elseif self.m_round==4 then
            if roundFourScore==4 then 
              self.m_shouldChangeRound=true
              self.m_layer:setTouchEnabled(false)
            end 
         elseif self.m_round==5 then
            if roundFiveScore==5 then
              if self.m_gameScore==15 then
                  if self.m_gameLevel==2 then 
                      --print("-------进入奖励环节-----")
                      self.m_shouldChangeRound=true
                      self.m_layer:setTouchEnabled(false)
                 else 
                    if self.gameOverCallFunc then 
                     self.gameOverCallFunc()
                    end
                 end         
             else
                 if self.gameOverCallFunc then 
                     self.gameOverCallFunc()
                end     
             end
          end
        end
    end
end
