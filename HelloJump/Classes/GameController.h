
#ifndef __PINGANY_GAMECONTROLLER_H__
#define __PINGANY_GAMECONTROLLER_H__

#include "LevelConfiguration.h"

class GameController : public CCObject
{
    bool started;
    int level;
    int score;

    static GameController* instance;
    GameController(): started(false), mainScene(NULL),
        level(0), score(0)
    {}
    bool init();
    CREATE_FUNC(GameController);

    CC_SYNTHESIZE_READONLY(MainScene*, mainScene, MainScene);
    CC_SYNTHESIZE_READONLY(SoundManager*, soundManager, SoundManager);
public:
    ~GameController();

    static GameController* sharedInstance();

    void startGame();

    void exitGame();

	void openMenu();

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
};

#endif
