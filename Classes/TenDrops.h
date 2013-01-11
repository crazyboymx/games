#ifndef __PINGANY_TENDROPS_H__
#define __PINGANY_TENDROPS_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "Utils.h"
#include "CocosUtils.h"

using namespace cocos2d;

class MainLayer;
class MainScene;
class GameOverScene;
class ExitButtonLayer;

class ExitButtonLayer: public CCLayer
{
public:
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(ExitButtonLayer);
};

class MainScene : public CCScene
{
public:
    MainScene(){}
    virtual bool init();
    CREATE_FUNC(MainScene);
};

class Drop
{
public:
    class Listener
    {
	public:
        virtual void onDropBomp(Drop*) = 0;
        virtual void onSpriteAdded(CCSprite*) = 0;
        virtual void onSpriteRemoved(CCSprite*) = 0;
    };
private:
    int water;
    Listener* listener;
    CC_SYNTHESIZE_READONLY(CCSprite*, sprite, Sprite);

public:
    Drop(int water, Listener* listener): water(water),
        listener(listener)
    {}
    virtual ~Drop()
    {
        destroy();
    }

    bool init();

    const CCRect& getRect() { return CocosUtils::getSpriteRect(sprite); }

    static CCSprite* getSpriteByWater(int water);

    void addWater();

    void replaceImage();

    void destroy();
};

class MainLayer : public CCLayer, public Drop::Listener
{
    int ncells, xcells, ycells;
    CCArray *drops, *bullets;
public:
    MainLayer(): ncells(36), xcells(6), ycells(6),
        drops(NULL), bullets(NULL)
    {
    }

    ~MainLayer();

    virtual bool init();

    // override
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    Drop* hitTest(const CCPoint& p);

    // override
    virtual void update(float dt);

    void onSpriteAdded(CCSprite* sprite);

    void onSpriteRemoved(CCSprite* sprite);

    void onDropBomp(Drop* drop);

    CREATE_FUNC(MainLayer);

private:
    bool isReadyToOver()
    {
        return drops->count() == 0 && bullets->count() == 0;
    }

    void conflictDetect();

    void removeOutBullets();

    void addDrops();
};

class GameController
{
    bool started;
    static GameController* instance;
public:
    GameController(): started(false)
    {}

    GameController* sharedInstance();

    void startGame();

    void exitGame();

    void gameOver();
};

class GameOverScene : public CCScene
{
public:
    bool init();
    CREATE_FUNC(GameOverScene);
};

#endif