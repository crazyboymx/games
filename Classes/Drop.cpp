
#include "pch.h"
#include "TenDrops.h"

Drop::~Drop()
{
	CC_SAFE_RELEASE_NULL(waveAction);
}

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
	stopWave();
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

void Drop::stopWave()
{
	if (waveAction)
		stopAction(waveAction);
	setScale(1);
}

void Drop::startWave()
{
	stopWave();
	if (!waveAction)
	{
		CCScaleBy* scale;
		waveAction = CCSequence::create(
			scale = CCScaleBy::create(0.2f, 1.3f),
			scale->reverse(),
			scale = CCScaleBy::create(0.2f, 1.2f),
			scale->reverse(),
			scale = CCScaleBy::create(0.2f, 1.1f),
			scale->reverse(),
			NULL);
		waveAction->retain();
	}
	runAction(waveAction);
}
