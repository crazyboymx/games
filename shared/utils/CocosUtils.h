#ifndef __PINGANY_COCOS_UTILS_H_
#define __PINGANY_COCOS_UTILS_H_

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"
using namespace cocos2d;

#define forset(__Type__, __o__, __set__) \
	__Type__ __o__; \
	for(CCSetIterator __it__ = (__set__)->begin(), __end__ = (__set__)->end(); \
		(__it__ != __end__ && ((__o__) = (__Type__)(*__it__), true)); \
		++__it__)

#define forarray(__Type__, __object__, __array__) \
    __Type__ __object__; \
	if ((__array__) && (__array__)->data->num > 0)                                                            \
	for(CCObject** arr = (__array__)->data->arr, **end = (__array__)->data->arr + (__array__)->data->num-1;   \
		arr <= end && (((__object__) = (__Type__)*arr), true/* different with CCArray.h */);              \
		arr++)

#define forarray_reverse(__Type__, __object__, __array__) \
    __Type__ __object__; \
	if ((__array__) && (__array__)->data->num > 0)                                                          \
	for(CCObject** arr = (__array__)->data->arr + (__array__)->data->num-1, **end = (__array__)->data->arr; \
		arr >= end && (((__object__) = (__Type__)*arr), true/* different with CCArray.h */);            \
		arr--)

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