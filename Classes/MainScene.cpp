
#include "pch.h"
#include "TenDrops.h"

class ExitButtonLayer: public CCLayer
{
public:
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(ExitButtonLayer);
};

bool MainScene::init()
{
	CCScene::init();
	// CCLayerColor* backgroundLayer = CCLayerColor::create(
	// 	ccc4(172, 177, 181, 255));
	CCLayer* backgroundLayer = CCLayer::create();
	addChild(backgroundLayer);
	CCSprite* backgroundImage = CCSprite::createWithSpriteFrame(CocosUtils::getSpriteFrameByName(
		"bg.png"));
	backgroundImage->setPosition(ccp(0, 0));
	backgroundImage->setAnchorPoint(ccp(0, 0));
	backgroundLayer->addChild(backgroundImage);

	CCSize size = CocosUtils::getScreenSize();
	// put InformationLayer in right top
	InformationLayer* infoLayer = InformationLayer::create();
	// infoLayer->ignoreAnchorPointForPosition(false);
	// infoLayer->setAnchorPoint(ccp(0, 0));
	CCSize s = infoLayer->getContentSize();
	infoLayer->setPosition(size.width - s.width/2, size.height - s.height/2);
	addChild(infoLayer);

	ExitButtonLayer* exitButtonLayer = ExitButtonLayer::create();
	addChild(exitButtonLayer);

	MainLayer* mainLayer = MainLayer::create();
	addChild(mainLayer);

	this->infoLayer = infoLayer;
	infoLayer->retain();

	this->mainLayer = mainLayer;
	mainLayer->retain();

	return true;
}

MainScene::~MainScene()
{
	CC_SAFE_RELEASE_NULL(mainLayer);
	CC_SAFE_RELEASE_NULL(infoLayer);
}

void MainScene::startPlay(LevelConfiguration* config)
{
	mainLayer->startPlay(config);
}

enum
{
	ITEM_OPEN_MENU = 1,
	ITEM_EXIT_GAME
};

bool ExitButtonLayer::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create();
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setTag(ITEM_EXIT_GAME);
		pCloseItem->setTarget(this, menu_selector(ExitButtonLayer::menuCloseCallback));
		pCloseItem->setNormalSpriteFrame(CocosUtils::getSpriteFrameByName("CloseNormal.png"));
		pCloseItem->setSelectedSpriteFrame(CocosUtils::getSpriteFrameByName("CloseSelected.png"));

		CCSize size = CocosUtils::getScreenSize();
		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(size.width - 20, 20));

		CCMenuItemFont* pOpenMenuItem = CCMenuItemFont::create("Menu", this,
			menu_selector(ExitButtonLayer::menuCloseCallback));
		CC_BREAK_IF(!pOpenMenuItem);
		pOpenMenuItem->setTag(ITEM_OPEN_MENU);
		pOpenMenuItem->setFontSize(24);
		pOpenMenuItem->setPosition(ccp(size.width - 100, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, pOpenMenuItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		this->addChild(pMenu);
		ret = true;
	} while(false);

	return ret;
}

void ExitButtonLayer::menuCloseCallback( CCObject* pSender )
{
	switch(((CCNode*)pSender)->getTag())
	{
		case ITEM_OPEN_MENU:
			GameController::sharedInstance()->openMenu();
			break;
		case ITEM_EXIT_GAME:
			GameController::sharedInstance()->exitGame();
			break;
	}
}