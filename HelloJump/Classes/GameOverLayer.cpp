
#include "pch.h"
#include "project.h"

enum
{
	MENU_ITEM_REPLAY = 1,
	MENU_ITEM_NEXT_LEVEL = 2
};

bool GameOverLayer::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCLayerColor* backgroundLayer = CCLayerColor::create(
			ccc4(255, 255, 255, 128));
		addChild(backgroundLayer);

		CCSize screenSize = CocosUtils::getScreenSize();

		CCMenuItemFont* nextLevel = CCMenuItemFont::create("Next", this,
			menu_selector(GameOverLayer::menuCallback));
		nextLevel->setTag(MENU_ITEM_NEXT_LEVEL);
		nextLevel->setFontName("Consola");
		nextLevel->setFontSize(36);

		CCMenuItemFont* replay = CCMenuItemFont::create("Replay", this,
			menu_selector(GameOverLayer::menuCallback));
		replay->setTag(MENU_ITEM_REPLAY);
		replay->setFontName("Consola");
		replay->setFontSize(36);

		CCMenu* menu = CCMenu::create(nextLevel, replay, NULL);
		menu->alignItemsVertically();

		menu->setPosition(screenSize.width/2, screenSize.height/2);
		addChild(menu);

		return true;
	} while (false);

	return false;
}

void GameOverLayer::menuCallback(CCObject* o)
{
	switch(((CCNode*)o)->getTag())
	{
		case MENU_ITEM_REPLAY:
			removeFromParentAndCleanup(true);
			GameController::sharedInstance()->replayThisLevel();
			break;
		case MENU_ITEM_NEXT_LEVEL:
			removeFromParentAndCleanup(true);
			GameController::sharedInstance()->enterNextLevel();
			break;
	}
}
