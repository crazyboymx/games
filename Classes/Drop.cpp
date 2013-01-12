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
	this->retain();
	CCPoint pos = sprite->getPosition();
	listener->onSpriteRemoved(sprite);
	sprite->release();
	sprite = getSpriteByWater(water);
	sprite->setPosition(pos);
	sprite->setUserData(this);
	sprite->retain();
	listener->onSpriteAdded(sprite);
	this->release();
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