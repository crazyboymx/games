
#ifndef __PINGANY_PLAYERLAYER_H__
#define __PINGANY_PLAYERLAYER_H__

class LandsLayer;
class LevelConfiguration;

class PlayerLayer : public CCLayer
{
	CCSprite* player;
	CCAction* jumpAction, *xMoveAction;
	LandsLayer* lands;
	bool xMoving;
	bool downwards;
	cc_timeval last_touch_time;

	PlayerLayer(): player(NULL), jumpAction(NULL), xMoveAction(NULL), lands(NULL),
		xMoving(false), downwards(false)
	{}
	bool init(LandsLayer* landsLayer);
public:
	~PlayerLayer();
	void startPlay(LevelConfiguration* config);
	void jump();
	void stopXMove();
	void stopJump();
	void scheduleJump();
	void upFinished();
	void restartXMove();

	// override
	void update(float time);

	void changeXSpeed(float dx);

	static PlayerLayer* create(LandsLayer* landsLayer);

	 // override
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

};

#endif
