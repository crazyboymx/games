
#ifndef __PINGANY_INFORMATIONLAYER_H__
#define __PINGANY_INFORMATIONLAYER_H__

class InformationLayer : public CCLayer
{
    bool init();
    CCLabelTTF *levelInfo, *scoreInfo, *leftDropInfo;

    CC_SYNTHESIZE_READONLY(int, level, Level);
    CC_SYNTHESIZE_READONLY(int, score, Score);
    CC_SYNTHESIZE_READONLY(int, leftDrops, LeftDrops);
public:
    InformationLayer(): levelInfo(NULL), scoreInfo(NULL), leftDropInfo(NULL)
    {}
    ~InformationLayer()
    {
        CC_SAFE_RELEASE_NULL(levelInfo);
        CC_SAFE_RELEASE_NULL(scoreInfo);
        CC_SAFE_RELEASE_NULL(leftDropInfo);
    }
    void setLevel(int level);
    void setScore(int score);
    void setLeftDrops(int leftDrops);

    void addScore(int score);
    void addDrops(int drops);

    CREATE_FUNC(InformationLayer);
};

#endif
