
#include "pch.h"
#include "project.h"

bool LandsLayer::init()
{
	CCLayer::init();
	CCSize size = CocosUtils::getScreenSize();

	lands = CCArray::create();
	lands->retain();

	int ncol = 2, nrow = 3;
	float cellW = size.width/ncol, cellH = size.height/nrow;
	forn(col, 0, ncol)
		forn(row, 0, nrow)
		{
			CCSprite* sprite = CocosUtils::getSprite(Utils::rand(1, 2) == 1 ? "cloud1.png" : "cloud2.png");
			addChild(sprite);
			lands->addObject(sprite);
			float x = col*cellW;
			float y = row*cellH;
			sprite->setPosition(ccp(Utils::rand(x, x + cellW), Utils::rand(y, y + cellH)));
		}

	return true;
}

void LandsLayer::move( float dy )
{
	forarray_reverse(CCNode*, land, lands)
	{
		if (CocosUtils::totallyOutOfScreen(land))
		{
			removeChild(land, true);
			lands->removeObject(land);
		}
		else
		{
			CCPoint p = land->getPosition();
			land->setPosition(p.x, p.y + dy);
		}
	}
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