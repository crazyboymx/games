
#include "pch.h"
#include "TenDrops.h"

/*static*/ GameController* GameController::instance = NULL;

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

void GameController::gameOver()
{
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