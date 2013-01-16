
#include "pch.h"
#include "project.h"

bool BackgroundLayer::init()
{
	CCLayer::init();
	addChild(CocosUtils::getSprite("background.png"));
	return true;
}