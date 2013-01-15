
#ifndef __PINGANY_MAINLAYER_H__
#define __PINGANY_MAINLAYER_H__

#include "Drop.h"

class MainLayer : public CCLayer, public Drop::Listener
{
    int ncells, xcells, ycells;
    int cellW, cellH;
    CCArray *drops, *bullets;
    CCNode* spritesBatch;

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
        virtual void beforeDropHitByBullet(Drop* drop) = 0;
        virtual void onDropChanged(Drop* drop) = 0;
        virtual void onBumpChainFinished() = 0;
    };
    CC_SYNTHESIZE(GameListener*, gameListener, GameListener);

public:
    ~MainLayer();

    virtual bool init();

    void startPlay(LevelConfiguration* config);

    // override
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

    Drop* hitTest(const CCPoint& p);

    // override
    virtual void update(float dt);

    bool canAddWater() { return bullets->count() == 0; }
    void addSprite(CCSprite* sprite);

    void removeSprite(CCSprite* sprite);

    void onDropChanged(Drop* drop);

    void removeAllDropsAndBullets();

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

#endif
