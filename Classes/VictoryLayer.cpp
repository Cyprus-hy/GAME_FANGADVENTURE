#include "VictoryLayer.h"
CCSprite* victorySprite;
CCSprite* boxSprite2;
CCSprite* winSprite;
CCMenuItemImage *replayItem2;
CCMenuItemImage *goItem2;

VictoryLayer::VictoryLayer(void)
{
	sGlobal->IQ=300;
}


VictoryLayer::~VictoryLayer(void)
{
}

Scene *VictoryLayer::scene()
{
	//------将结束场景加入到Scene中------
	auto Sce=Scene::create();
	auto gSce=VictoryLayer::create();
	Sce->addChild(gSce);
	return Sce;
}

bool VictoryLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	Size size = Director::getInstance()->getWinSize();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("win.wav",false);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("conNpc.plist");
	//------背景图片-------
	Sprite* bgSprite=Sprite::create("bkg.png");
	bgSprite->setPosition(size.width / 2, size.height/2);
	this->addChild(bgSprite);

	//------显示成功的框图------
	auto bg = Sprite::create("win_bkg.png");
	bg->setPosition(size.width/2, size.height/2);
	this->addChild(bg);

	//------刷新按钮------
	replayItem2 = CCMenuItemImage::create(
		"back_but1.png",
		"back_but2.png",
		this,
		menu_selector(VictoryLayer::backItemCallback));
	//------下一关按钮------
	goItem2 = CCMenuItemImage::create(
		"go1.png",
		"go2.png",
		this,
		menu_selector(VictoryLayer::goItemCallback));
	// Place the menu item bottom-right conner.
	goItem2 ->setPosition(200,size.height-200);
	// Place the menu item bottom-right conner.
	replayItem2 ->setPosition(70,size.height-30);
	Menu* backItemMenu = Menu::create(replayItem2,goItem2, NULL);
	backItemMenu->setPosition(Point::ZERO);
	addChild(backItemMenu);



	return true;
}

void VictoryLayer::backItemCallback(Ref*)
{
	Director::getInstance()->popScene();
	Scene* gamemenu=GameMenu::scene();
	Director::getInstance()->pushScene(gamemenu);
}

void VictoryLayer::goItemCallback(Ref*)
{
	Director::getInstance()->popScene();
	Scene* gamemenu=StageSelect::scene();
	Director::getInstance()->pushScene(gamemenu);
}