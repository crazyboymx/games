
#include "pch.h"
#include "project.h"

bool BackgroundLayer::init()
{
	CCLayer::init();
	CCSprite* background = CocosUtils::getSprite("background.png");

	CCSize screenSize = CocosUtils::getScreenSize();
	background->setScaleX(screenSize.width / background->getContentSize().width);
	background->setScaleY(screenSize.height / background->getContentSize().height);
	background->setAnchorPoint(ccp(0, 0));
	background->setPosition(ccp(0, 0));
	addChild(background);
	return true;
}