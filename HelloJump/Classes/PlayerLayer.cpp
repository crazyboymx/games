
#include "pch.h"
#include "project.h"
#include "CCMoveBySingleDirection.h"

bool PlayerLayer::init(LandsLayer* landsLayer)
{
	player = CocosUtils::getSprite("player.png");
	addChild(player);
	player->retain();

	this->lands = landsLayer;
	this->lands->retain();

	return true;
}

PlayerLayer* PlayerLayer::create(LandsLayer* landsLayer)
{
	PlayerLayer* ret = new PlayerLayer();
	if (ret && ret->init(landsLayer))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		delete ret;
		return NULL;
	}
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

		jumpAction = CCSequence::create(up,
			CCCallFunc::create(this, callfunc_selector(PlayerLayer::upFinished)),
			down, NULL);
		jumpAction->retain();
	}
	downwards = false;
	player->runAction(jumpAction);
}

void PlayerLayer::upFinished()
{
	downwards = true;
}

void PlayerLayer::update(float time)
{
	{
		bool xmove = xMoving;
		stopXMove();
		float width = CocosUtils::getScreenSize().width;
		float x = player->getPositionX();
		if (x < 0)
			x += width;
		else if (x >= width)
			x -= width;
		player->setPositionX(x);
		if (xmove)
			restartXMove();
	}
	if (!downwards)
		return;
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
		unscheduleUpdate();
	}
}

void PlayerLayer::changeXSpeed( float dx )
{
	float width = CocosUtils::getScreenSize().width;
	stopXMove();
	if (fabs(dx) >= 1)
	{
		CC_SAFE_RELEASE_NULL(xMoveAction);
		xMoveAction = CCMoveBySingleDirection::create(width/dx, width, CCMoveBySingleDirection::DIRECTION_X);
		xMoveAction->retain();
		restartXMove();
	}
}

void PlayerLayer::restartXMove()
{
	CC_ASSERT(xMoveAction);
	player->runAction(xMoveAction);
	xMoving = true;
}

void PlayerLayer::stopXMove()
{
	if (xMoveAction && xMoving)
	{
		stopAction(xMoveAction);
		xMoving = false;
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
	stopXMove();
	stopJump();
	player->setPosition(ccp(CocosUtils::getScreenSize().width/2, 0));

	scheduleJump();
	unscheduleUpdate();
	scheduleUpdate();
}