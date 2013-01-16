
#ifndef __PINGANY_MAINSCENE_H__
#define __PINGANY_MAINSCENE_H__

class LevelConfiguration;
class LandsLayer;
class PlayerLayer;

class MainScene : public CCScene
{
	CC_SYNTHESIZE_READONLY(LandsLayer*, landsLayer, LandsLayer);
	CC_SYNTHESIZE_READONLY(PlayerLayer*, playerLayer, PlayerLayer);
	MainScene(){}
	bool init();
public:
	~MainScene(){}
	CREATE_FUNC(MainScene);

	void startPlay(LevelConfiguration* config);
};

#endif
