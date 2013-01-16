
#ifndef __PINGANY_GAMEOVERLAYER_H__
#define __PINGANY_GAMEOVERLAYER_H__

class GameOverLayer : public CCLayer
{
	GameOverLayer(){}
	bool init(){ return true; }
public:
	~GameOverLayer(){}
	CREATE_FUNC(GameOverLayer);
};

#endif
