
#include "pch.h"
#include "TenDrops.h"

MainLayer::~MainLayer()
{
	CC_SAFE_RELEASE_NULL(drops);
	CC_SAFE_RELEASE_NULL(bullets);
}

void MainLayer::addDrops(LevelConfiguration* config)
{
	char *waters = config->getWaters();
	forn(i, 0, ncells)
	{
		if (waters[i] <= 0 || waters[i] > 4)
			continue;
		Drop *drop = new Drop();
		drop->init(waters[i], this);
		drop->setPosition(ccp(i % xcells * cellW + cellW/2,
			i / xcells * cellH + cellH/2));
		addSprite(drop);
	}
}

void MainLayer::removeOutBullets()
{
	for(int i = bullets->count() - 1; i >= 0; --i)
	{
		CCSprite* bullet = (CCSprite*)bullets->objectAtIndex(i);
		if (!CocosUtils::containsRect(bulletsArea,
				CocosUtils::getSpriteRect(bullet)))
			removeSprite(bullet);
	}
}

void MainLayer::conflictDetect()
{
	for(int i = bullets->count() - 1; i >= 0; --i)
	{
		CCSprite* bullet = (CCSprite*)bullets->objectAtIndex(i);
		bool bulletNeedRemove = false;

		for(int j = drops->count() - 1; j >= 0; --j)
		{
			Drop* drop = (Drop*)drops->objectAtIndex(j);
			if (CocosUtils::getSpriteRect(bullet).intersectsRect(drop->getRect()))
			{
				bulletNeedRemove = true;
				drop->addWater();
				break;
			}
		}
		if (bulletNeedRemove)
			removeSprite(bullet);
	}
}

void MainLayer::onDropBump( Drop* drop )
{
	if (gameListener)
		gameListener->onDropBump(drop);
	const CCPoint moves[4] = {CCPointMake(0, cellH), CCPointMake(0, -cellH),
		CCPointMake(-cellW, 0), CCPointMake(cellW,0)};
	forn(i, 0, 4)
	{
		CCSprite* bullet = CCSprite::create(fabs(moves[i].x) < 0.1
			? "bullet_ver.png" : "bullet_hor.png");
		bullet->setPosition(drop->getPosition());
		bullet->setTag(SPRITE_BULLET);
		CCAction* action = CCRepeatForever::create(CCMoveBy::create(
			0.5, moves[i]));
		addSprite(bullet);
		bullet->runAction(action);
	}
	removeSprite(drop);
}

void MainLayer::removeSprite( CCSprite* sprite )
{
	bool isDrop = sprite->getTag() == SPRITE_DROP;
	CCArray* array = isDrop ? drops : bullets;
	array->removeObject(sprite);
	removeChild(sprite, true);
}

void MainLayer::addSprite( CCSprite* sprite )
{
	bool isDrop = sprite->getTag() == SPRITE_DROP;
	CCArray* array = isDrop ? drops : bullets;
	array->addObject(sprite);
	addChild(sprite);
}

void MainLayer::update( float dt )
{
	bool originalCanAddWater = canAddWater();
	removeOutBullets();
	if (isReadyToOver())
	{
		unscheduleUpdate();
		GameController::sharedInstance()->gameOver();
		return;
	}
	if (!originalCanAddWater && canAddWater())
		bumpChainFinished();
	conflictDetect();
}

void MainLayer::bumpChainFinished()
{
	if (gameListener)
		gameListener->onBumpChainFinished();
}

Drop* MainLayer::hitTest( const CCPoint& p )
{
	CCObject* o;
	CCARRAY_FOREACH(drops, o)
	{
		Drop* drop = (Drop*)o;
		if (drop->getRect().containsPoint(p))
			return drop;
	}
	return NULL;
}

void MainLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	#ifndef _DEBUG
	if (!canAddWater())
		return;
	#endif

	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	Drop* drop = hitTest(touch->getLocation());
	if (!drop)
		return;
	if (gameListener)
		gameListener->onTouchDrop(drop);
	drop->addWater();
}

bool MainLayer::init()
{
	CCLayer::init();
	drops = CCArray::create();
	drops->retain();

	bullets = CCArray::create();
	bullets->retain();

	bulletsArea = CCRectMake(0, 0, xcells*cellW, ycells*cellH);
	setTouchEnabled(true);
	return true;
}

void MainLayer::startPlay(LevelConfiguration* config)
{
	drops->removeAllObjects();
	bullets->removeAllObjects();
	removeAllChildrenWithCleanup(true);

	addDrops(config);

	// avoid call scheduleUpdate many times, which doesn't work
	unscheduleUpdate();
	scheduleUpdate();

}
