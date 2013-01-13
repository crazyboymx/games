
#ifndef __PINGANY_GAMECONTROLLER_H__
#define __PINGANY_GAMECONTROLLER_H__

#include "MainLayer.h"
#include "LevelConfiguration.h"

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
    bool init();
    CREATE_FUNC(GameController);

    CC_SYNTHESIZE_READONLY(SoundManager*, soundManager, SoundManager);
public:

    virtual void onDropBump(Drop* drop);

    virtual void onTouchDrop(Drop* drop);

    virtual void onBumpChainFinished(){}

    static GameController* sharedInstance();

    void startGame();

    void exitGame();

    void levelFailed();

    void levelComplete();

    LevelConfiguration* getLevelConfig(int level);

    void replayThisLevel() { enterLevel(level); }
    void enterNextLevel() { enterLevel(level+1); }
    void enterLevel(int level);

    void addScore(int s)
    {
        setScore(score + s);
    }

    void setScore(int s);

    void addLeftDrops(int drops)
    {
        setLeftDrops(leftDrops + drops);
    }

    void setLeftDrops(int drops);
};

#endif
