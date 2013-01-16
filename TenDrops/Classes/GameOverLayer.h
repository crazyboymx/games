
#ifndef __PINGANY_GAMEOVERLAYER_H__
#define __PINGANY_GAMEOVERLAYER_H__

class GameOverLayer : public CCLayer
{
public:
    bool init();
    CREATE_FUNC(GameOverLayer);
	void menuCallback(CCObject* o);
};

#endif
