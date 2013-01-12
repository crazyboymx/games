
#include "pch.h"
#include "TenDrops.h"

bool InformationLayer::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize screenSize = CocosUtils::getScreenSize();

		CCSprite* background = CCSprite::create("info_bg.png");
		addChild(background);

		int h = background->getTextureRect().size.height;
		int w = background->getTextureRect().size.width;
		CCLabelTTF* levelInfo = CCLabelTTF::create("0", "Consola", 14);
		// Coordinates related to center of background
		levelInfo->setPosition(ccp(0, h/2-19));
		levelInfo->setColor(ccc3(0, 255, 0));
		addChild(levelInfo);

		CCLabelTTF* scoreInfo = CCLabelTTF::create("0", "Consola", 14);
		scoreInfo->setPosition(ccp(0, h/2-32));
		scoreInfo->setColor(ccc3(0, 255, 0));
		addChild(scoreInfo);

		CCLabelTTF* leftDropInfo = CCLabelTTF::create("0", "Consola", 32);
		leftDropInfo->setPosition(ccp(0, h/2-137));
		addChild(leftDropInfo);

		this->levelInfo = levelInfo;
		levelInfo->retain();
		this->scoreInfo = scoreInfo;
		scoreInfo->retain();
		this->leftDropInfo = leftDropInfo;
		leftDropInfo->retain();

		setContentSize(background->getTextureRect().size);
		return true;
	} while(false);
	return false;
}

void InformationLayer::setLevel( int level )
{
	levelInfo->setString(CocosUtils::toString(level)->getCString());
}

void InformationLayer::setScore( int score )
{
	scoreInfo->setString(CocosUtils::toString(score)->getCString());
}

void InformationLayer::setLeftDrops( int leftDrops )
{
	leftDropInfo->setString(CocosUtils::toString(leftDrops)->getCString());
}

void InformationLayer::addScore( int score )
{
	setScore(this->score + score);
}

void InformationLayer::addDrops( int drops )
{
	setLeftDrops(this->leftDrops + drops);
}