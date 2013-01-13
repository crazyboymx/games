#ifndef __PINGANY_TENDROPS_H__
#define __PINGANY_TENDROPS_H__

#include "cocos2d.h"

#include "Utils.h"
#include "CocosUtils.h"

using namespace cocos2d;

class MainLayer;
class InformationLayer;
class MainScene;
class GameOverLayer;
class ExitButtonLayer;

class GameController;
class LevelConfiguration;

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
    CC_SYNTHESIZE_READONLY(InformationLayer*, infoLayer, InfoLayer);
    CC_SYNTHESIZE_READONLY(MainLayer*, mainLayer, MainLayer);
public:
    ~MainScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    void startPlay(LevelConfiguration* config);
};

class Drop : public CCSprite
{
public:
    class Listener
    {
	public:
        virtual void onDropBump(Drop*) = 0;
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

    CCRect bulletsArea;
    MainLayer(): ncells(36), xcells(6), ycells(6),
        cellW(50), cellH(50),
        drops(NULL), bullets(NULL)
    {
    }
public:
    class GameListener
    {
	public:
        virtual void onTouchDrop(Drop* drop) = 0;
        virtual void onDropBump(Drop* drop) = 0;
        virtual void onBumpChainFinished() = 0;
    };
    CC_SYNTHESIZE(GameListener*, gameListener, GameListener);

public:
    ~MainLayer();

    virtual bool init();

    void startPlay(LevelConfiguration* config);

    // override
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    Drop* hitTest(const CCPoint& p);

    // override
    virtual void update(float dt);

    bool canAddWater() { return bullets->count() == 0; }
    void addSprite(CCSprite* sprite);

    void removeSprite(CCSprite* sprite);

    void onDropBump(Drop* drop);

    CREATE_FUNC(MainLayer);

private:
    bool isReadyToOver()
    {
        return drops->count() == 0 && bullets->count() == 0;
    }

    void conflictDetect();

    void removeOutBullets();

    void addDrops(LevelConfiguration* config);

    void bumpChainFinished();
};

class InformationLayer : public CCLayer
{
    bool init();
    CCLabelTTF *levelInfo, *scoreInfo, *leftDropInfo;

    CC_SYNTHESIZE_READONLY(int, level, Level);
    CC_SYNTHESIZE_READONLY(int, score, Score);
    CC_SYNTHESIZE_READONLY(int, leftDrops, LeftDrops);
public:
    InformationLayer(): levelInfo(NULL), scoreInfo(NULL), leftDropInfo(NULL)
    {}
    ~InformationLayer()
    {
        CC_SAFE_RELEASE_NULL(levelInfo);
        CC_SAFE_RELEASE_NULL(scoreInfo);
        CC_SAFE_RELEASE_NULL(leftDropInfo);
    }
    void setLevel(int level);
    void setScore(int score);
    void setLeftDrops(int leftDrops);

    void addScore(int score);
    void addDrops(int drops);

    CREATE_FUNC(InformationLayer);
};

class LevelConfiguration : public CCObject
{
    const static int ncells = 36;
    char waters[100];
    CC_SYNTHESIZE_READONLY(int, leftDrops, LeftDrops);
    LevelConfiguration(){}
    bool init() { return true; }

    CREATE_FUNC(LevelConfiguration);
public:
    char* getWaters() { return waters; }
    static LevelConfiguration* getRandomConfiguration();
};

class GameController : public CCObject, public MainLayer::GameListener
{
    bool started;
    int level;
    int score;
    int leftDrops;
    int bumpedDropForThisTouch;
    MainScene* mainScene;

    static GameController* instance;
    GameController(): started(false), mainScene(NULL),
        level(0), score(0), leftDrops(0),
        bumpedDropForThisTouch(0)
    {}
    bool init() { return true; }
    CREATE_FUNC(GameController);
public:

    virtual void onDropBump(Drop* drop)
    {
        bumpedDropForThisTouch ++;
        if (bumpedDropForThisTouch >= 3)
        {
            bumpedDropForThisTouch = 0;
            addLeftDrops(1);
        }
    }

    virtual void onTouchDrop(Drop* drop)
    {
        addLeftDrops(-1);
        bumpedDropForThisTouch = 0;
    }

    virtual void onBumpChainFinished(){}

    static GameController* sharedInstance();

    void startGame();

    void exitGame();

    void gameOver();

    void gameFailed()
    {
        // TODO
        gameOver();
    }

    LevelConfiguration* getLevelConfig(int level)
    {
        // TODO:
        return LevelConfiguration::getRandomConfiguration();
    }

    void replayThisLevel() { enterLevel(level); }
    void enterNextLevel() { enterLevel(level+1); }
    void enterLevel(int level)
    {
        LevelConfiguration* config = getLevelConfig(level);

        this->level = level;
        mainScene->getInfoLayer()->setLevel(level);

        setLeftDrops(config->getLeftDrops());
        setScore(0);
        mainScene->startPlay(config);
    }

    void addScore(int s)
    {
        setScore(score + s);
    }

    void setScore(int s)
    {
        this->score = s;
        mainScene->getInfoLayer()->setScore(score);
    }

    void addLeftDrops(int drops)
    {
        setLeftDrops(leftDrops + drops);
    }

    void setLeftDrops(int drops)
    {
        if (drops <= 0)
        {
            gameFailed();
            return;
        }
        leftDrops = drops;
        mainScene->getInfoLayer()->setLeftDrops(drops);
    }
};

class GameOverLayer : public CCLayer
{
public:
    bool init();
    CREATE_FUNC(GameOverLayer);
	void menuCallback(CCObject* o);
};

#endif