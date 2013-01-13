
#include "pch.h"

#include "CocosUtils.h"

cocos2d::CCRect CocosUtils::getSpriteRect( CCSprite* sprite )
{
	CCPoint p = sprite->getPosition();
	CCRect r = sprite->getTextureRect();
	int w = r.size.width;
	int h = r.size.height;
	return CCRectMake(p.x - w/2, p.y - h/2, w, h);
}

CCSize CocosUtils::getScreenSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

bool CocosUtils::containsRect(const CCRect& r1, const CCRect& r2)
{
	return r1.containsPoint(r2.origin) && r1.containsPoint(ccp(
		r2.origin.x + r2.size.width - 1, r2.origin.y + r2.size.height - 1));
}