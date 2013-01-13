#ifndef __PINGANY_TENDROPS_H__
#define __PINGANY_TENDROPS_H__

#include "cocos2d.h"

#include "Utils.h"
#include "CocosUtils.h"

using namespace cocos2d;
using namespace CocosDenshion;

class MainScene;
class MainLayer;
class InformationLayer;
class GameOverLayer;

class GameController;
class LevelConfiguration;
class SoundManager;

enum
{
    SPRITE_DROP = 1,
    SPRITE_BULLET
};

#include "MainLayer.h"
#include "MainScene.h"
#include "GameController.h"
#include "Drop.h"
#include "InformationLayer.h"
#include "LevelConfiguration.h"
#include "GameOverLayer.h"
#include "SoundManager.h"

#endif