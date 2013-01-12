#ifndef __PINGANY_COCOS_UTILS_H_
#define __PINGANY_COCOS_UTILS_H_

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"
using namespace cocos2d;

class CocosUtils
{
public:
	static CCRect getSpriteRect(CCSprite* sprite);
	static CCSize getScreenSize();
};

#endif