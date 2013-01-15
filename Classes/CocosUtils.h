#ifndef __PINGANY_COCOS_UTILS_H_
#define __PINGANY_COCOS_UTILS_H_

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"
using namespace cocos2d;

#define forset(Type, o, set) \
	Type o; \
	for(CCSetIterator __it = (set)->begin(); (__it != (set)->end() && ((o) = (Type)(*__it), true)); ++__it)

class CocosUtils
{
public:
	static CCRect getSpriteRect(CCSprite* sprite);
	static CCSize getScreenSize();

	static CCString* toString(int value)
	{
		return CCString::createWithFormat("%d", value);
	}
	static bool containsRect(const CCRect& r1, const CCRect& r2);

	static CCSpriteFrame* getSpriteFrameByName(const char* name);
};

#endif