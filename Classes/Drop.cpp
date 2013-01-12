#include "TenDrops.h"

bool Drop::init()
{
	sprite = getSpriteByWater(water);
	sprite->setUserData(this);
	sprite->retain();
	listener->onSpriteAdded(sprite);
	return true;
}

/*static*/ CCSprite* Drop::getSpriteByWater( int water )
{
	CCSprite* sprite = CCSprite::create(CCString::createWithFormat("drop%d.png", water)
		->getCString());
	sprite->setTag(SPRITE_DROP);
	return sprite;
}

void Drop::addWater()
{
	water ++;
	if (water > 4)
		listener->onDropBomp(this);
	else
		replaceImage();
}

void Drop::replaceImage()
{
	listener->onSpriteRemoved(sprite);
	sprite = getSpriteByWater(water);
	sprite->setUserData(this);
	listener->onSpriteAdded(sprite);
}

void Drop::destroy()
{
	if (sprite)
	{
		listener->onSpriteRemoved(sprite);
		sprite->release();
		sprite = NULL;
	}
}