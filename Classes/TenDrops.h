#ifndef __PINGANY_TENDROPS_H__
#define __PINGANY_TENDROPS_H__

#include "cocos2d.h"

#include "Utils.h"
#include "CocosUtils.h"

using namespace cocos2d;

class MainLayer;
class MainScene;
class GameOverScene;
class ExitButtonLayer;

enum
{
    SPRITE_DROP = 1,
    SPRITE_BULLET
};

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
    virtual bool init();
    CREATE_FUNC(MainScene);
};

class Drop : public CCSprite
{
public:
    class Listener
    {
	public:
        virtual void onDropBomp(Drop*) = 0;
    };
private:
    int water;
    Listener* listener;

    void updateImage();
public:
    Drop(): water(0),
        listener(NULL)
    {}
    bool init(int water, Listener* listener);

    CCRect getRect() { return CocosUtils::getSpriteRect(this); }

    void addWater();
};

class MainLayer : public CCLayer, public Drop::Listener
{
    int ncells, xcells, ycells;
    int cellW, cellH;
    CCArray *drops, *bullets;
public:
    MainLayer(): ncells(36), xcells(6), ycells(6),
        cellW(60), cellH(60),
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

    void addSprite(CCSprite* sprite);

    void removeSprite(CCSprite* sprite);

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

class GameController : public CCObject
{
    bool started;
    static GameController* instance;
    GameController(): started(false)
    {}
    bool init() { return true; }
    CREATE_FUNC(GameController);
public:

    static GameController* sharedInstance();

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