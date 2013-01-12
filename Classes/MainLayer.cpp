
#include "pch.h"
#include "TenDrops.h"

MainLayer::~MainLayer()
{
	CC_SAFE_RELEASE_NULL(drops);
	CC_SAFE_RELEASE_NULL(bullets);
}

void MainLayer::addDrops()
{
	int ndrops = Utils::rand(ncells*3/4, ncells);

	int *pos = new int[ncells];
	forn(i, 0, ncells)
		pos[i] = i;
	Utils::shuffle(pos, 0, ncells);

	forn(i, 0, ndrops)
	{
		Drop *drop = new Drop();
		drop->init(Utils::rand(1, 4), this);
		drop->setPosition(ccp(pos[i] % xcells * cellW + cellW/2,
			pos[i] / xcells * cellH + cellH/2));
		addSprite(drop);
	}

	delete[] pos;
}

void MainLayer::removeOutBullets()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	for(int i = bullets->count() - 1; i >= 0; --i)
	{
		CCSprite* bullet = (CCSprite*)bullets->objectAtIndex(i);
		if (!CocosUtils::getSpriteRect(bullet).intersectsRect(CCRectMake(0, 0,
			screenSize.width, screenSize.height)))
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

void MainLayer::onDropBomp( Drop* drop )
{
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
	removeOutBullets();
	if (isReadyToOver())
	{
		GameController::sharedInstance()->gameOver();
		return;
	}
	conflictDetect();
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
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	Drop* drop = hitTest(touch->getLocation());
	if (!drop)
		return;
	drop->addWater();
}

bool MainLayer::init()
{
	CCLayer::init();
	drops = CCArray::create();
	drops->retain();

	bullets = CCArray::create();
	bullets->retain();

	addDrops();
	setTouchEnabled(true);
	scheduleUpdate();
	return true;
}