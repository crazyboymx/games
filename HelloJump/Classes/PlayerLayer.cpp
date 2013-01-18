
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
	setAccelerometerEnabled(true);
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

static float last_dx = 0;
void PlayerLayer::changeXSpeed( float dx )
{
	CCLog("changeXSpeed: %f", dx);
	float width = CocosUtils::getScreenSize().width;
	float fdx = fabs(dx);
	if (fdx < 1e-3)
	{
		stopXMove();
		CC_SAFE_RELEASE_NULL(xMoveAction);
	}
	else if (fabs(last_dx) < 1e-3 || (dx > 0 && last_dx < 0) || (dx < 0 && last_dx > 0) || !xMoveAction)
	{
		// if (fdx > 1e-3)
		{
			float move = dx > 0 ? width : -width;
			xMoveAction = CCSpeed::create(
				CCMoveBySingleDirection::create(1.0f*1000, move*1000, CCMoveBySingleDirection::DIRECTION_X), fdx);
			xMoveAction->retain();
			restartXMove();
		}
	}
	else
	{
		xMoveAction->setSpeed(fdx);
	}
	last_dx = dx;
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
	downwards = false;
	if (jumpAction)
		player->stopAction(jumpAction);
}

void PlayerLayer::scheduleJump()
{
	this->scheduleOnce(schedule_selector(PlayerLayer::jumpOnSchedule), 1.0f);
	// jump();
}

void PlayerLayer::didAccelerate( CCAcceleration* pAccelerationValue )
{
	// CCLog("PlayerLayer::didAccelerate: (%f,%f,%f)", pAccelerationValue->x, pAccelerationValue->y, pAccelerationValue->z);
	changeXSpeed(pAccelerationValue->x);
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
	CCLog("PlayerLayer::ccTouchesEnded");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// stopXMove();
	CCTouch* touch = (CCTouch*) pTouches->anyObject();
	float width = CocosUtils::getScreenSize().width;
	changeXSpeed(touch->getLocation().x/width - 0.5f);
#endif
}

void PlayerLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	CCLog("PlayerLayer::ccTouchesMode");
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// struct cc_timeval now;
	// CCTime::gettimeofdayCocos2d(&now, NULL);
	// changeXSpeed(touch->getDelta().x * 1000 / (CCTime::timersubCocos2d(&last_touch_time, &now)));
	// last_touch_time = now;
	// int dir = touch->getDelta().x > 0 ? DIR_RIGHT : DIR_LEFT;
	// if (touchDir != dir)
	// {
	// 	touchDir = dir;
	// 	changeXSpeed(touchDir == DIR_RIGHT ? 160 : -160);
	// }

#endif
}

void PlayerLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	CCLog("PlayerLayer::ccTouchesBegan");
	touchDir = DIR_NONE;
	// CCTime::gettimeofdayCocos2d(&last_touch_time, NULL);
}