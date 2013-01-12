
#include "pch.h"
#include "TenDrops.h"

bool MainScene::init()
{
	CCScene::init();
	CCLayerColor* backgroundLayer = CCLayerColor::create(
		ccc4(255, 255, 255, 255));
	addChild(backgroundLayer);

	ExitButtonLayer* exitButtonLayer = ExitButtonLayer::create();
	addChild(exitButtonLayer);

	MainLayer* mainLayer = MainLayer::create();
	addChild(mainLayer);
	return true;
}

bool GameOverScene::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		CCLayerColor* backgroundLayer = CCLayerColor::create(
			ccc4(255, 255, 255, 255));
		addChild(backgroundLayer);

		CCSize screenSize = CocosUtils::getScreenSize();

		CCMenuItemFont* restartItem = CCMenuItemFont::create("Restart", this,
			menu_selector(GameOverScene::menuCallback));
		restartItem->setFontName("Consola");
		restartItem->setFontSize(36);

		CCMenu* menu = CCMenu::create(restartItem, NULL);
		menu->alignItemsVertically();

		menu->setPosition(screenSize.width/2, screenSize.height/2);
		addChild(menu);

		return true;
	} while (false);

	return false;
}

void GameOverScene::menuCallback(CCObject* o)
{
	GameController::sharedInstance()->startGame();
}

bool ExitButtonLayer::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(ExitButtonLayer::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		this->addChild(pMenu);
		ret = true;
	} while(false);

	return ret;
}

void ExitButtonLayer::menuCloseCallback( CCObject* pSender )
{
	// "close" menu item clicked
	GameController::sharedInstance()->exitGame();
}