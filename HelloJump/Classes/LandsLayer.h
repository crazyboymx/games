
#ifndef __PINGANY_LANDSLAYER_H__
#define __PINGANY_LANDSLAYER_H__

class LevelConfiguration;
class LandsLayer : public CCLayer
{
	CCArray* lands;
	LandsLayer(){}
	bool init();
public:
	~LandsLayer(){}
	void move(float dy);
	CCNode* getLand(CCNode* node);

	CREATE_FUNC(LandsLayer);
	void startPlay(LevelConfiguration* config);
	void addLands(float offsetY);
	void update(float time);
};

#endif
