
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
	CCLayerColor* backgroundLayer = CCLayerColor::create(
		ccc4(172, 177, 181, 255));
	addChild(backgroundLayer);

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

bool ExitButtonLayer::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create();
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setTarget(this, menu_selector(ExitButtonLayer::menuCloseCallback));
		pCloseItem->setNormalSpriteFrame(CocosUtils::getSpriteFrameByName("CloseNormal.png"));
		pCloseItem->setSelectedSpriteFrame(CocosUtils::getSpriteFrameByName("CloseSelected.png"));

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