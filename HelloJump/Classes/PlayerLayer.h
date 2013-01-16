
#ifndef __PINGANY_PLAYERLAYER_H__
#define __PINGANY_PLAYERLAYER_H__

class LandsLayer;
class LevelConfiguration;

class PlayerLayer : public CCLayer
{
	CCSprite* player;
	CCAction* jumpAction, *xMoveAction;
	LandsLayer* lands;

	PlayerLayer(): player(NULL), jumpAction(NULL), xMoveAction(NULL), lands(NULL)
	{}
	bool init();
public:
	~PlayerLayer();
	void startPlay(LevelConfiguration* config);
	void jump();
	void stopJump();
	void scheduleJump();

	// override
	void update(float time);

	void changeXSpeed(float dx);

	CREATE_FUNC(PlayerLayer);
};

#endif
