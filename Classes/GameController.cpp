
#include "pch.h"
#include "TenDrops.h"

/*static*/ GameController* GameController::instance = NULL;

bool GameController::init()
{
	soundManager = SoundManager::create();
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
	soundManager->playEffect("level_complete.ogg");
	mainScene->addChild(GameOverLayer::create(), 1);
}

void GameController::levelFailed()
{
	soundManager->playEffect("level_failed.mp3");
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

void GameController::onDropBump( Drop* drop )
{
	soundManager->playEffect("drop_break.ogg");
	bumpedDropForThisTouch ++;
	if (bumpedDropForThisTouch >= 3)
	{
		bumpedDropForThisTouch = 0;
		soundManager->playEffect("add_drops.ogg");
		addLeftDrops(1);
	}
}

void GameController::onTouchDrop( Drop* drop )
{
	if (drop == NULL)
	{
		soundManager->playEffect("no_touch.ogg");
		return;
	}
	soundManager->playEffect("inwater.ogg");
	addLeftDrops(-1);
	bumpedDropForThisTouch = 0;
}