
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

static CCTexture2D* getTextureByWater( int water )
{
	return CCTextureCache::sharedTextureCache()
		->addImage(CCString::createWithFormat("drop%d.png", water)
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
	CCTexture2D* tex = getTextureByWater(water);
	setTexture(tex);

	CCRect rect = CCRectZero;
    rect.size = tex->getContentSize();
    this->setTextureRect(rect);
}