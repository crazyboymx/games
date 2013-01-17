
#include "pch.h"
#include "project.h"

enum
{
	LAYER_PLAYER = 1,
	LAYER_BACKGROUND,
	LAYER_LANDS
};

bool MainScene::init()
{
	CCScene::init();

	BackgroundLayer* background = BackgroundLayer::create();
	background->setTag(LAYER_BACKGROUND);
	addChild(background);

	LandsLayer* lands = LandsLayer::create();
	lands->setTag(LAYER_LANDS);
	addChild(lands);

	PlayerLayer* playerLayer = PlayerLayer::create(lands);
	playerLayer->setTag(LAYER_PLAYER);
	addChild(playerLayer);

	this->landsLayer = lands;
	lands->retain();

	this->playerLayer = playerLayer;
	playerLayer->retain();
	return true;
}

void MainScene::startPlay( LevelConfiguration* config )
{
	playerLayer->startPlay(config);
}