
static GameController* GameController::instance = NULL;

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
	delete this;
}

void GameController::gameOver()
{
	CCDirector::sharedDirector()->replaceScene(GameOverScene::create());
}

GameController* GameController::sharedInstance()
{
	if (!instance)
		instance = new GameController();
	return instance;
}