
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

	// override
	void update(float time);

	void changeXSpeed(float dx);

	static PlayerLayer* create(LandsLayer* landsLayer);
	void upFinished();
	void restartXMove();
};

#endif
