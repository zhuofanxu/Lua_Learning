--设置内存回收
collectgarbage("setpause",100)
collectgarbage("setstepmul",5000)


--获取窗口大小
local winSize =CCDirector:sharedDirector():getWinSize()

--创建背景层
local function createLayer( ... )
	local layerHello =CCLayer:create() 

--加入背景精灵
	local backSprite =CCSprite:create("Hello.png")
	backSprite:setPosition(winSize.width/2,winSize.height/2)
    layerHello:addChild(backSprite)
--创建label
    local label =CCLabelTFT:create("Fuck Cocos2d-x","Arial",50) 
    label:setPosition(winSize.width/2,60)
    label:setVisible(true)
    layerHello:addChild(label)

    return layerHello

	-- body
end
--加入关闭按钮菜单
local function createExitBtn( ... )
	local layerMenu =CCLayer:create()

	--用于退出的回掉函数
	local function menuCallbackExit( ... )
		CCDirector:sharedDirector():endToLua()
		-- body
	end 
	-- body
 
--创建退出按钮
local menuExitItem =CCMenuItem:create("CloseNomal.png","CloseSelected.png")
 menuExitItem:setPosition(winSize.width-50,winSize.height-50)
 --注册退出函数
 menuExitItem:registerScriptHandler(menuCallbackExit)
--创建菜单
local menuClose=CCMenu:create(menuExitItem)
menuClose:setPosition(0,0)
menuClose:setVisible(true)
--菜单加入层中
layerMenu:addChild(menuClose)

return layerMenu

end

local scene=CCScene:create()
scene:addChild(createLayer())
scene:addChild(createExitBtn())
CCDirector:sharedDirector():runWithScene(scene)

