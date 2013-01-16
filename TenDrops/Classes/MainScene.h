
#ifndef __PINGANY_MAINSCENE_H__
#define __PINGANY_MAINSCENE_H__

class MainScene : public CCScene
{
    CC_SYNTHESIZE_READONLY(InformationLayer*, infoLayer, InfoLayer);
    CC_SYNTHESIZE_READONLY(MainLayer*, mainLayer, MainLayer);
public:
    ~MainScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    void startPlay(LevelConfiguration* config);
};

#endif
