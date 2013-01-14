
#include "pch.h"
#include "TenDrops.h"

bool Drop::init(int water, Listener* listener)
{
	do
	{
		CC_BREAK_IF(!CCSprite::init());

		this->water = water;
		this->listener = listener;
		this->setTag(SPRITE_DROP);
		updateImage();

		return true;
	} while (false);

	return false;
}

static const char* getSpriteFrameNameByWater( int water )
{
	return (CCString::createWithFormat("drop%d.png", water)
			->getCString());
}

void Drop::addWater()
{
	water ++;
	listener->onDropChanged(this);
	if (water <= 4)
		updateImage();
}

void Drop::updateImage()
{
	setDisplayFrame(CocosUtils::getSpriteFrameByName(
		getSpriteFrameNameByWater(water)));
}