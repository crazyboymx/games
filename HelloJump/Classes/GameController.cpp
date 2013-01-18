
#include "pch.h"
#include "project.h"

/*static*/ GameController* GameController::instance = NULL;

static void addSpritesToCache()
{
	#ifdef HAS_TEXTURE_PACKED
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage("sprites.png");

		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(0,0,320,480)), "background.png");
		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(336,16,256,108)), "cloud1.png");
		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(336,128,257,110)), "cloud2.png");
		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(336,240,252,119)), "cloud3.png");

		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(608,16,44,32)), "player.png");
		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(608,64,102,36)), "land1.png");
		cache->addSpriteFrame(CCSpriteFrame::createWithTexture(tex, CCRectMake(608,128,90,32)), "land2.png");

	#endif
}

bool GameController::init()
{
	soundManager = SoundManager::create();
	soundManager->retain();
	addSpritesToCache();
	return true;
}

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

void GameController::levelComplete()
{
	// soundManager->playEffect("level_complete");
	mainScene->addChild(GameOverLayer::create(), 1);
}

void GameController::levelFailed()
{
	// soundManager->playEffect("level_failed");
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

	setScore(0);
	mainScene->startPlay(config);
}

void GameController::setScore( int s )
{
	this->score = s;
}

GameController::~GameController()
{
	CC_SAFE_RELEASE_NULL(soundManager);
	mainScene = NULL;
}
