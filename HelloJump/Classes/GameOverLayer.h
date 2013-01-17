
#ifndef __PINGANY_GAMEOVERLAYER_H__
#define __PINGANY_GAMEOVERLAYER_H__

class GameOverLayer : public CCLayer
{
	GameOverLayer(){}
	bool init();
public:
	void menuCallback(CCObject* o);
	~GameOverLayer(){}
	CREATE_FUNC(GameOverLayer);
};

#endif
