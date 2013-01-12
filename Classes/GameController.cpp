
#include "pch.h"
#include "TenDrops.h"

/*static*/ GameController* GameController::instance = NULL;

void GameController::startGame()
{
	if (!started)
	{
		started = true;
		CCDirector::sharedDirector()->runWithScene(MainScene::create());
	}
	else
		CCDirector::sharedDirector()->replaceScene(MainScene::create());
}

void GameController::exitGame()
{
	CCDirector::sharedDirector()->end();
	this->release();
}

void GameController::gameOver()
{
	CCDirector::sharedDirector()->replaceScene(GameOverScene::create());
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