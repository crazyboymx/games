
#include "pch.h"
#include "project.h"
#include "CCMoveBySingleDirection.h"

bool PlayerLayer::init()
{
	player = CocosUtils::getSprite("player.png");
	player->setPosition(ccp(0, CocosUtils::getScreenSize().width/2));
	addChild(player);
	player->retain();

	lands = GameController::sharedInstance()->getMainScene()->getLandsLayer();
	lands->retain();

	return true;
}

void PlayerLayer::jump()
{
	if (!jumpAction)
	{
		float height = CocosUtils::getScreenSize().height;
		CCMoveBySingleDirection* up1 = CCMoveBySingleDirection::create(1.0f,
			height/3, CCMoveBySingleDirection::DIRECTION_Y),
		*down1 = CCMoveBySingleDirection::create(2.0f,
			-height, CCMoveBySingleDirection::DIRECTION_Y);

		CCEaseIn *up = CCEaseIn::create(up1, 2.0f);
		CCEaseOut *down = CCEaseOut::create(down1, 2.0f);

		jumpAction = CCSequence::create(up, down, NULL);
		jumpAction->retain();
	}
	player->runAction(jumpAction);
}

void PlayerLayer::update(float time)
{
	CCNode* land = lands->getLand(player);
	if (land)
	{
		stopJump();
		scheduleJump();
		lands->move(30 - land->getPositionY());
	}
	else if (CocosUtils::totallyOutOfScreen(player))
	{
		GameController::sharedInstance()->levelFailed();
	}
}

void PlayerLayer::changeXSpeed( float dx )
{
	float width = CocosUtils::getScreenSize().width;
	if (xMoveAction)
	{
		stopAction(xMoveAction);
		xMoveAction->release();
		xMoveAction = NULL;
	}
	if (fabs(dx) > 1e-4)
	{
		xMoveAction = CCMoveBySingleDirection::create(1.0f * dx, width, CCMoveBySingleDirection::DIRECTION_X);
		xMoveAction->retain();
		player->runAction(xMoveAction);
	}
}

void PlayerLayer::stopJump()
{
	if (jumpAction)
		player->stopAction(jumpAction);
}

void PlayerLayer::scheduleJump()
{
	// this->scheduleOnce(0.1, schedule_selectior(PlayerLayer::jumpOnSchedule));
	jump();
}

PlayerLayer::~PlayerLayer()
{
	CC_SAFE_RELEASE_NULL(lands);
	CC_SAFE_RELEASE_NULL(jumpAction);
	CC_SAFE_RELEASE_NULL(xMoveAction);
	CC_SAFE_RELEASE_NULL(player);
}

void PlayerLayer::startPlay( LevelConfiguration* config )
{
	scheduleJump();
	unscheduleUpdate();
	scheduleUpdate();
}