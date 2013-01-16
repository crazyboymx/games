
#ifndef __PINGANY_LEVELCONFIGURATION_H__
#define __PINGANY_LEVELCONFIGURATION_H__

class LevelConfiguration : public CCObject
{
    const static int ncells = 36;
    char waters[100];
    CC_SYNTHESIZE_READONLY(int, leftDrops, LeftDrops);
    LevelConfiguration(){}
    bool init() { return true; }

    CREATE_FUNC(LevelConfiguration);
public:
    char* getWaters() { return waters; }
    static LevelConfiguration* getRandomConfiguration();
};

#endif
