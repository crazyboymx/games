
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

	setTouchEnabled(true);
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
	//return;
	if (!jumpAction)
	{
		float height = CocosUtils::getScreenSize().height;
		CCMoveBySingleDirection* up1 = CCMoveBySingleDirection::create(1.0f,
			height/3, CCMoveBySingleDirection::DIRECTION_Y),
		*down1 = CCMoveBySingleDirection::create(2.0f,
			-height, CCMoveBySingleDirection::DIRECTION_Y);

		CCEaseOut *up = CCEaseOut::create(up1, 1.5f);
		CCEaseIn *down = CCEaseIn::create(down1, 1.5f);

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
		float width = CocosUtils::getScreenSize().width;
		float x = player->getPositionX();
		bool xOutOfScreen = true;
		if (x < 0)
			x += width;
		else if (x >= width)
			x -= width;
		else
			xOutOfScreen = false;

		if (xOutOfScreen)
		{
			bool xmove = xMoving;
			stopXMove();
			player->setPositionX(x);
			if (xmove)
				restartXMove();
		}
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
	else if (player->getPositionY() < 0)
	{
		GameController::sharedInstance()->levelFailed();
		unscheduleUpdate();
	}
}

void PlayerLayer::changeXSpeed( float dx )
{
	CCLOG("changeXSpeed: %f", dx);
	float width = CocosUtils::getScreenSize().width;
	stopXMove();
	if (fabs(dx) >= 1)
	{
		CC_SAFE_RELEASE_NULL(xMoveAction);
		float move = dx > 0 ? width : -width;
		xMoveAction = CCMoveBySingleDirection::create(move/dx, move, CCMoveBySingleDirection::DIRECTION_X);
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

enum
{
	DIR_NONE,
	DIR_RIGHT,
	DIR_LEFT
};
static int touchDir = DIR_NONE;

void PlayerLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	stopXMove();
#endif
}

void PlayerLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	// struct cc_timeval now;
	// CCTime::gettimeofdayCocos2d(&now, NULL);
	// changeXSpeed(touch->getDelta().x * 1000 / (CCTime::timersubCocos2d(&last_touch_time, &now)));
	// last_touch_time = now;
	int dir = touch->getDelta().x > 0 ? DIR_RIGHT : DIR_LEFT;
	if (touchDir != dir)
	{
		touchDir = dir;
		changeXSpeed(touchDir == DIR_RIGHT ? 160 : -160);
	}
#endif
}

void PlayerLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	touchDir = DIR_NONE;
	// CCTime::gettimeofdayCocos2d(&last_touch_time, NULL);
}