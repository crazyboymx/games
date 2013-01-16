
#include "pch.h"

#include "CocosUtils.h"

cocos2d::CCRect CocosUtils::getSpriteRect( CCNode* sprite )
{
	CCPoint p = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	int w = size.width;
	int h = size.height;
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

CCSpriteFrame* CocosUtils::getSpriteFrameByName(const char* name)
{
#ifdef HAS_TEXTURE_PACKED
	return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
#else
	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(name);
	CCRect rect = CCRectZero;
	rect.size = tex->getContentSize();
	CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(tex, rect);
	return frame;
#endif
}

CCSprite* CocosUtils::getSprite( const char* name )
{
	return CCSprite::createWithSpriteFrame(getSpriteFrameByName(name));
}

bool CocosUtils::totallyOutOfScreen( CCNode* node )
{
	return !getScreenRect().intersectsRect(getSpriteRect(node));
}

cocos2d::CCRect CocosUtils::getScreenRect()
{
	CCSize size = getScreenSize();
	return CCRectMake(0, 0, size.width, size.height);
}