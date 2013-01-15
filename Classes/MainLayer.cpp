
#include "pch.h"
#include "TenDrops.h"

MainLayer::~MainLayer()
{
	CC_SAFE_RELEASE_NULL(drops);
	CC_SAFE_RELEASE_NULL(bullets);
	CC_SAFE_RELEASE_NULL(spritesBatch);
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
				if (gameListener)
					gameListener->beforeDropHitByBullet(drop);
				drop->addWater();
				break;
			}
		}
		if (bulletNeedRemove)
			removeSprite(bullet);
	}
}

void MainLayer::onDropChanged( Drop* drop )
{
	if (gameListener)
		gameListener->onDropChanged(drop);
	if (drop->getWater() <= 4)
		return;

	const CCPoint moves[4] = {CCPointMake(0, cellH), CCPointMake(0, -cellH),
		CCPointMake(-cellW, 0), CCPointMake(cellW,0)};
	forn(i, 0, 4)
	{
		CCSprite* bullet = CCSprite::createWithSpriteFrame(CocosUtils::getSpriteFrameByName(fabs(moves[i].x) < 0.1
			? "bullet_ver.png" : "bullet_hor.png"));
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
	spritesBatch->removeChild(sprite, true);
}

void MainLayer::addSprite( CCSprite* sprite )
{
	bool isDrop = sprite->getTag() == SPRITE_DROP;
	CCArray* array = isDrop ? drops : bullets;
	array->addObject(sprite);
#ifdef HAS_TEXTURE_PACKED
	CC_ASSERT(spritesBatch->getTexture() == sprite->getTexture());
#endif
	spritesBatch->addChild(sprite);
}

void MainLayer::update( float dt )
{
	bool originalCanAddWater = canAddWater();
	removeOutBullets();
	if (isReadyToOver())
	{
		unscheduleUpdate();
		GameController::sharedInstance()->levelComplete();
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

void MainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	forset(CCTouch*, touch, pTouches)
	{
		Drop* drop = hitTest(touch->getLocation());
		if (drop)
		{
			drop->runWave();
		}
	}
}

void MainLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	#ifndef _DEBUG
	if (!canAddWater())
	{
		if (gameListener)
			gameListener->onTouchDrop(NULL); // touch disabled
		return;
	}
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

#ifdef HAS_TEXTURE_PACKED
	spritesBatch = CCSpriteBatchNode::createWithTexture(CCTextureCache::sharedTextureCache()->
		textureForKey("pack.png"));
	addChild(spritesBatch);
#else
	spritesBatch = this;
#endif
	spritesBatch->retain();

	// Add drop background
	forn(i, 0, ncells)
	{
		CCSprite* dropBg = CCSprite::createWithSpriteFrame(CocosUtils::getSpriteFrameByName("drop.png"));
		dropBg->setPosition(ccp(i % xcells * cellW + cellW/2,
			i / xcells * cellH + cellH/2));
		spritesBatch->addChild(dropBg);
	}

	bulletsArea = CCRectMake(0, 0, xcells*cellW, ycells*cellH);
	setTouchEnabled(true);
	return true;
}

void MainLayer::removeAllDropsAndBullets()
{
	CCObject* o;
	CCARRAY_FOREACH_REVERSE(bullets, o)
		removeSprite((CCSprite*)o);
	CCARRAY_FOREACH_REVERSE(drops, o)
		removeSprite((CCSprite*)o);
}

void MainLayer::startPlay(LevelConfiguration* config)
{
	removeAllDropsAndBullets();

	addDrops(config);

	// avoid call scheduleUpdate many times, which doesn't work
	unscheduleUpdate();
	scheduleUpdate();

}
