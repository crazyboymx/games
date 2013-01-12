
#include "CocosUtils.h"

cocos2d::CCRect CocosUtils::getSpriteRect( CCSprite* sprite )
{
	CCPoint p = sprite->getPosition();
	CCRect r = sprite->getTextureRect();
	int w = r.size.width;
	int h = r.size.height;
	return CCRectMake(p.x - w/2, p.y - h/2, w, h);
}