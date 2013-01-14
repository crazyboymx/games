
#include "pch.h"
#include "TenDrops.h"

/*static*/ GameController* GameController::instance = NULL;

static void addSpritesToCache()
{
	#ifdef HAS_TEXTURE_PACKED
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pack.plist", "pack.png");
	#else
		const char* names[] = {
			"drop1.png",
			"drop2.png",
			"drop3.png",
			"drop4.png",
			"bullet_ver.png",
			"bullet_hor.png",
			"bg.png",
			"info_bg.png",
			"CloseNormal.png",
			"CloseSelected.png"
		};
		forn(i, 0, (sizeof(names)/sizeof(names[0])))
		{
			const char* name = names[i];
			CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(name);
			CCRect rect = CCRectZero;
			rect.size = tex->getContentSize();
			CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(tex, rect);
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(frame, name);
		}
	#endif
}

bool GameController::init()
{
	soundManager = SoundManager::create();
	addSpritesToCache();
	return true;
}

void GameController::startGame()
{
	if (!started)
	{
		started = true;
		mainScene = MainScene::create();
		mainScene->getMainLayer()->setGameListener(this);
		CCDirector::sharedDirector()->runWithScene(mainScene);
		replayThisLevel();
	}
	else
	{
		replayThisLevel();
	}
}

void GameController::exitGame()
{
	CCDirector::sharedDirector()->end();
	this->release();
}

void GameController::levelComplete()
{
	soundManager->playEffect("level_complete");
	mainScene->addChild(GameOverLayer::create(), 1);
}

void GameController::levelFailed()
{
	soundManager->playEffect("level_failed");
	mainScene->addChild(GameOverLayer::create(), 1);
}

void GameController::openMenu()
{
	// TODO
	mainScene->addChild(GameOverLayer::create(), 1);
}

/*static*/ GameController* GameController::sharedInstance()
{
	if (!instance)
	{
		instance = GameController::create();
		instance->retain();
	}
	return instance;
}

LevelConfiguration* GameController::getLevelConfig( int level )
{
	// TODO:
	return LevelConfiguration::getRandomConfiguration();
}

void GameController::enterLevel( int level )
{
	LevelConfiguration* config = getLevelConfig(level);

	this->level = level;
	mainScene->getInfoLayer()->setLevel(level);

	setLeftDrops(config->getLeftDrops());
	setScore(0);
	mainScene->startPlay(config);
}

void GameController::setScore( int s )
{
	this->score = s;
	mainScene->getInfoLayer()->setScore(score);
}

void GameController::setLeftDrops( int drops )
{
	if (drops <= 0)
	{
		levelFailed();
		return;
	}
	leftDrops = drops;
	mainScene->getInfoLayer()->setLeftDrops(drops);
}

void GameController::onDropChanged( Drop* drop )
{
	if (drop->getWater() <= 4)
		return;
	soundManager->playEffect("drop_break");
	bumpedDropForThisTouch ++;
	if (bumpedDropForThisTouch >= 3)
	{
		bumpedDropForThisTouch = 0;
		soundManager->playEffect("add_drops");
		addLeftDrops(1);
	}
}

void GameController::onTouchDrop( Drop* drop )
{
	if (drop == NULL)
	{
		soundManager->playEffect("no_touch");
		return;
	}
	soundManager->playEffect("inwater");
	addLeftDrops(-1);
	bumpedDropForThisTouch = 0;
}

void GameController::beforeDropHitByBullet( Drop* drop )
{
	if (drop->getWater() < 4) // otherwise it will bomp
		soundManager->playEffect("drop_bigger");
}