
#include "pch.h"
#include "TenDrops.h"

enum
{
	MENU_ITEM_REPLAY = 1,
	MENU_ITEM_NEXT_LEVEL = 2
};

bool GameOverScene::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		CCLayerColor* backgroundLayer = CCLayerColor::create(
			ccc4(255, 255, 255, 128));
		addChild(backgroundLayer);

		CCSize screenSize = CocosUtils::getScreenSize();

		CCMenuItemFont* nextLevel = CCMenuItemFont::create("Next", this,
			menu_selector(GameOverScene::menuCallback));
		nextLevel->setTag(MENU_ITEM_NEXT_LEVEL);
		nextLevel->setFontName("Consola");
		nextLevel->setFontSize(36);

		CCMenuItemFont* replay = CCMenuItemFont::create("Replay", this,
			menu_selector(GameOverScene::menuCallback));
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

void GameOverScene::menuCallback(CCObject* o)
{
	switch(((CCNode*)o)->getTag())
	{
		case MENU_ITEM_REPLAY:
			CCDirector::sharedDirector()->popScene();
			GameController::sharedInstance()->replayThisLevel();
			break;
		case MENU_ITEM_NEXT_LEVEL:
			CCDirector::sharedDirector()->popScene();
			GameController::sharedInstance()->enterNextLevel();
			break;
	}
}
