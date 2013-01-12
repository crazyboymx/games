
#include "pch.h"
#include "TenDrops.h"

/*static*/ GameController* GameController::instance = NULL;

void GameController::startGame()
{
	if (!started)
	{
		started = true;
		mainScene = MainScene::create();
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
	CCDirector::sharedDirector()->pushScene(GameOverScene::create());
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