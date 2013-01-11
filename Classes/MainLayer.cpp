
MainLayer::~MainLayer()
{
	if (drops)
		drops->release();
	if (bullets)
		bullets->release();
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
		Drop *drop = new Drop(Utils::rand(1, 4), this);
		drop->getSprite()->setPosition(pos[i] % xcells * cellW + cellW/2,
			pos[i] / xcells * cellH + cellH/2);
	}

	delete[] pos;
}

void MainLayer::removeOutBullets()
{
	CCSprite* bullet = NULL;
	CCARRAY_FOREACH_REVERSE(bullets, bullet)
	{
		if (!getSpriteRect(bullet).intersectsRect(CCRectMake(0, 0,
			screenSize.width, screenSize.height)))
			onSpriteRemoved(bullet);
	}
}

void MainLayer::conflictDetect()
{
	CCSprite* bullet = NULL;
	CCSprite* drop = NULL;
	CCARRAY_FOREACH_REVERSE(bullets, bullet)
	{
		bool bulletNeedRemove = false;
		CCARRAY_FOREACH_REVERSE(drop, drops)
		{
			if (getSpriteRect(bullet).intersectsRect(getSpriteRect(drop)))
			{
				bulletNeedRemove = true;
				drop->addWater();
				break;
			}
		}
		if (bulletNeedRemove)
			onSpriteRemoved(bullet);
	}
}

void MainLayer::onDropBomp( Drop* drop )
{
	const CCPoint moves[4] = {CCPointMake(0, 1), CCPointMake(0, -1),
		CCPointMake(-1, 0), CCPointMake(1,0)};
	forn(i, 0, 4)
	{
		CCSprite* bullet = CCSprite::spriteWithFile(abs(moves[0]) < 0.1
			? "bullet_ver.png" : "bullet_hor.png");
		bullet->setTag(SPRITE_BULLET);
		CCAction* action = CCRepeat::create(CCMoveBy::create(
			0.5, moves[i]));
		onSpriteAdded(bullet)
			bullet->runAction(action);
	}
	drop->destroy();
}

void MainLayer::onSpriteRemoved( CCSprite* sprite )
{
	CCArray* array = sprite->getTag() == SPRITE_DROP ? drops : bullets;
	array->removeObject(sprite);
	removeChild(sprite);
}

void MainLayer::onSpriteAdded( CCSprite* sprite )
{
	CCArray* array = sprite->getTag() == SPRITE_DROP ? drops : bullets;
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
	Drop* drop = NULL;
	CCARRAY_FOREACH(drops, drop)
	{
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
	drops = CCArray::create();
	drops->retain();

	bullets = CCArray::create();
	bullets->retain();

	addDrops();
	setTouchEnabled(true);
	scheduleUpdate();
}