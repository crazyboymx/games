
#include "pch.h"
#include "project.h"

bool LandsLayer::init()
{
	CCLayer::init();

	lands = CCArray::create();
	lands->retain();

	return true;
}

void LandsLayer::startPlay(LevelConfiguration* config)
{
	lands->removeAllObjects();
	removeAllChildrenWithCleanup(true);
	addLands(0);
	unscheduleUpdate();
	scheduleUpdate();
}

void LandsLayer::addLands(float offsetY)
{
	CCSize size = CocosUtils::getScreenSize();
	int ncol = 2, nrow = 3;
	float cellW = size.width/ncol, cellH = size.height/nrow;
	float last_y = offsetY;
	forn(col, 0, ncol)
		forn(row, 0, nrow*2)
		{
			CCSprite* sprite = CocosUtils::getSprite(Utils::rand(1, 2) == 1 ? "land1.png" : "land2.png");
			addChild(sprite);
			lands->addObject(sprite);
			float x = col*cellW;
			float y = offsetY + row*cellH;
			sprite->setPosition(ccp(Utils::rand(x, x + cellW), MIN(last_y + cellH, Utils::rand(y, y + cellH))));
			last_y = y;
		}
}

void LandsLayer::move( float dy )
{
	forarray_reverse(CCNode*, land, lands)
	{
		if (land->getPositionY() < 0)
		{
			removeChild(land, true);
			lands->removeObject(land);
		}
		else
		{
			land->runAction(CCMoveBy::create(1.0f, ccp(0, dy)));
		}
	}
}

void LandsLayer::update(float time)
{
	if (lands->count() < 12)
		addLands(((CCNode*)lands->lastObject())->getPositionY());
}

CCNode* LandsLayer::getLand(CCNode* node)
{
	forarray(CCNode*, land, lands)
	{
		CCRect nodeRect = CocosUtils::getSpriteRect(node);
		CCRect landRect = CocosUtils::getSpriteRect(land);
		if (nodeRect.intersectsRect(landRect) && fabs(nodeRect.getMinY() - landRect.getMaxY()) < 5)
			return land;
	}
	return NULL;
}