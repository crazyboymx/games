
#include "CocosUtils.h"

cocos2d::CCRect CocosUtils::getSpriteRect( CCSprite* sprite )
{
	CCPoint p = sprite->getPosition();
	CCRect r = sprite->getTextureRect();
	return CCRectMake(p.x, p.y, r.size.width, r.size.height);
}