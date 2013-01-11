
bool MainScene::init()
{
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
	return CCScene::init();
}

bool ExitButtonLayer::init()
{
	bool ret = false
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

			this->addChild(pMenu, 1);
			ret = true;
		}

		return ret;
}

void ExitButtonLayer::menuCloseCallback( CCObject* pSender )
{
	// "close" menu item clicked
	GameController::sharedInstance()->exitGame();
}