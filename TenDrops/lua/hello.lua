

local winSize = CCDirector:sharedDirector():getWinSize()

-- sceneGame= CCScene:node()
-- layer= CCLayerColor:layerWithColor( ccc4(0,0,255, 255) )
-- sceneGame:addChild( layer )

-- label= CCLabelTTF:labelWithString("LuaProjectTemplate", "Arial", 48.0)
-- label:setColor( ccc3(255,255,255) )
-- label:setPosition( CCPoint( winSize.width/2, winSize.height/2) )
-- layer:addChild( label )

local cclog = function(...)
    print(string.format(...))
end

local function tableIndexOf( t, value )
  for k,v in pairs(t) do
    if v==value then return k end
  end
  return nil
end

local function tableRemove(t, value)
    table.remove(t, tableIndexOf(t, value))
end

local function GameLayer()
    local gameLayer = CCLayer:create()

    local xcells = 6
    local ycells = 6
    local ncells = 36
    local ndrops = math.random(ncells * 3/4, ncells)
    local cells = {}
    local bullets = {}

    local bullet_hor = CCTextureCache:sharedTextureCache():addImage("bullet_hor.png")
    local bullet_ver = CCTextureCache:sharedTextureCache():addImage("bullet_ver.png")

    local dropImages = {}
    for i = 1, 4 do
        dropImages[i] = CCTextureCache:sharedTextureCache():addImage(string.format("drop%d.png", i))
    end

    local cellSize = dropImages[4]:getContentSize().width

    local bomb
    local removeCell
    local removeBullet
    local replaceCell

    local function getDropByWater(water)
        local sprite = CCSprite:createWithTexture(dropImages[water])
        sprite.water = water
        return sprite
    end

    local function addDrops( ... )
        -- for i = 1, ncells do
        --     cells[i] = false
        -- end
        for i = 1, ndrops do
            cells[i] = getDropByWater(math.random(1, 4))
            cells[i]:setPosition(CCPointMake(i % xcells * cellSize + cellSize/2, i / xcells * cellSize + cellSize/2))
            gameLayer:addChild(cells[i])
        end
    end

    local function addWater(cell)
        cell.water = cell.water + 1
        if cell.water > 4 then
            bomb(cell)
        else
            local newCell = getDropByWater(cell.water)
            newCell:setPosition(cell:getPosition())
            replaceCell(cell, newCell)
        end
    end

    bomb = function(cell)
        local time = 0.5
        local moves = {
            {0, cellSize},
            {0, -cellSize},
            {cellSize, 0},
            {-cellSize, 0},
        }
        for _, move in pairs(moves) do
            local bullet = CCSprite:createWithTexture(move[1] == 0 and bullet_ver or bullet_hor)
            bullet:setPosition(cell:getPosition())
            gameLayer:addChild(bullet)
            table.insert(bullets, bullet)
            bullet:runAction(CCRepeatForever:create(CCMoveBy:create(time, CCPointMake(move[1], move[2]))))
        end

        removeCell(cell)
    end

    removeCell = function (cell )
        tableRemove(cells, cell)
        gameLayer:removeChild(cell, true)
    end

    replaceCell = function (cell, newCell)
        cells[tableIndexOf(cells, cell)] = newCell
        gameLayer:addChild(newCell)
        gameLayer:removeChild(cell, true)
    end

    local function getSpriteRect(sprite)
        local size = sprite:getTexture():getContentSize()
        -- cclog("getSpriteRect", rect.width, rect.height)
        local x, y = sprite:getPosition()
        return CCRectMake(x, y, size.width, size.height)
    end

    local function hitTest(x, y)
        for _, cell in pairs(cells) do
            if getSpriteRect(cell):containsPoint(CCPointMake(x, y)) then
                return cell
            end
        end
    end

    local function onTouchEnded(x, y)
        cclog("onTouchEnded: %0.2f, %0.2f", x, y)
        local cell = hitTest(x, y)
        if cell then
            addWater(cell)
            return true
        end
    end

    local function onTouch(eventType, x, y)
        cclog("onTouch", eventType, x, y)
        if eventType == CCTOUCHBEGAN then
            return true--onTouchBegan(x, y)
        elseif eventType == CCTOUCHMOVED then
            return true--onTouchMoved(x, y)
        else
            return onTouchEnded(x, y)
        end
    end

    local function conflictDetect(time)
        local bulletsToRemove = {}
        for _, bullet in pairs(bullets) do
            local cellsToAddWater = {}
            for _, cell in pairs(cells) do
                if getSpriteRect(cell):intersectsRect(getSpriteRect(bullet)) then
                    table.insert(cellsToAddWater, cell)
                end
            end

            for _, cell in pairs(cellsToAddWater) do
                addWater(cell)
            end

            if table.getn(cellsToAddWater) > 0 then
                table.insert(bulletsToRemove, bullet)
            end
        end
        for _, bullet in pairs(bulletsToRemove) do
            removeBullet(bullet)
        end
    end

    removeBullet = function (bullet )
        gameLayer:removeChild(bullet, true)
        tableRemove(bullets, bullet)
    end

    local function removeOutBullets(time)
        local bulletsToRemove = {}
        for _, bullet in pairs(bullets) do
            if not getSpriteRect(bullet):intersectsRect(CCRectMake(0, 0, winSize.width, winSize.height)) then
                table.insert(bulletsToRemove, bullet)
            end
        end
        for _, bullet in pairs(bulletsToRemove) do
            removeBullet(bullet)
        end
    end

    local function doOnEachFrame(time)
        -- cclog("doOnEachFrame")
        removeOutBullets(time)
        conflictDetect(time)
    end

    gameLayer:registerScriptTouchHandler(onTouch)
    gameLayer:setTouchEnabled(true)

    addDrops()
    CCDirector:sharedDirector():getScheduler():scheduleScriptFunc(doOnEachFrame, 1.0/4, false)

    return gameLayer
end

local sceneGame = CCScene:create()
sceneGame:addChild(GameLayer())

-- run
CCDirector:sharedDirector():runWithScene( sceneGame )
