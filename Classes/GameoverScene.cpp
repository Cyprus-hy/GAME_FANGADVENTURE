#include "GameoverScene.h"

GameoverScene::GameoverScene()
{
	sGlobal->gameoverLayer=this;
}

GameoverScene::~GameoverScene()
{

}

Scene *GameoverScene::scene(int a)
{
	//------将结束场景加入到Scene中------
	auto Sce=Scene::create();
	auto gSce=GameoverScene::create(a);
	Sce->addChild(gSce);
	return Sce;
}

GameoverScene* GameoverScene::create(int a)
{
	//------创建结束场景并初始化------
	auto g_scene=new GameoverScene();
	if(g_scene&&g_scene->init(a))
	{
		g_scene->autorelease();
		return g_scene;
	}
	else
	{
		delete g_scene;
		g_scene=NULL;
		return NULL;
	}
}

bool GameoverScene::init(int a)
{
	if ( !Layer::init() )
	{
		return false;
	}

	type=a;
	//sGlobal->hero->isDead=true;//英雄死亡
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameOver.plist");
	Size size = Director::getInstance()->getWinSize();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lose.wav",false);


	//------背景图片-------
	Sprite* bgSprite=Sprite::create("bkg.png");
	bgSprite->setPosition(size.width / 2, size.height/2);
	this->addChild(bgSprite);


	//------显示失败的框图------
	auto bg = Sprite::createWithSpriteFrameName("prompt_box.png");
	bg->setPosition(size.width/2, size.height/2);
	this->addChild(bg); 

	//------显示IQ分数------
	sGlobal->IQ=sGlobal->IQ-50;
	int iq=sGlobal->IQ;
	char temp[20];
	sprintf(temp, "%d", iq);
	LabelTTF* pLabel = LabelTTF::create(temp, "Arial",40);
	pLabel->setColor(Color3B::BLACK);
	pLabel->setPosition(size.width/2+70, size.height/2-10);
	addChild(pLabel);

	//------重新游戏的按钮------
	auto restart1 = Sprite::create("refresh1.png");
	auto restart2 = Sprite::create("refresh2.png");//这张图片颜色更深
	auto menuItemBack = MenuItemSprite::create(restart1, restart2, CC_CALLBACK_1(GameoverScene::backItemCallback, this));
	menuItemBack->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	menuItemBack->setPosition(size.width*3/4+5,size.height/3);

	//------提示按钮------
	auto tip1 = Sprite::create("hint1.png");
	auto tip2 = Sprite::create("hint2.png");//这张图片颜色更深
	auto menuItemTip = MenuItemSprite::create(tip1, tip2, CC_CALLBACK_1(GameoverScene::turntoTipScene, this));
	menuItemTip->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	menuItemTip->setPosition(size.width*3/4,size.height/3);

	auto menu = Menu::create(menuItemBack,menuItemTip, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}


void GameoverScene::backItemCallback(Ref*)
{
	Director::getInstance()->popScene();
	/*Scene* game_1_1=Game_1_1::scene();
	Director::getInstance()->pushScene(game_1_1);*/
}

void GameoverScene::turntoTipScene(Ref *)
{
	/*auto tip=TipScene1::create();
	tip->setAnchorPoint(Point::ANCHOR_MIDDLE);
	tip->setPosition(Point::ZERO);
	this->addChild(tip,2);*/
	/*auto tip=TipScene1::createScene();
	tip->setPosition(Point::ZERO);*/

	Size size = Director::getInstance()->getWinSize();
	//------返回按钮------
	MenuItemImage *backItem = MenuItemImage::create(
		"back_but1.png",
		"back_but2.png",
		this,
		menu_selector(GameoverScene::backItemCallback));

	backItem ->setPosition(70,size.height-30);
	Menu* backItemMenu = Menu::create(backItem , NULL);
	backItemMenu->setPosition(Point::ZERO);
	addChild(backItemMenu,2);

	Sprite* bgSprite;
	//------选择提示图片------
	if(type==1)
		bgSprite=Sprite::create("hint_1.png");
	else if(type==2)
		bgSprite=Sprite::create("hint_2.png");
	else if(type==3)
		bgSprite=Sprite::create("hint_bkg1.png");
	else if(type==4)
		bgSprite=Sprite::create("hint_bkg2.png");
	else if(type==5)
		bgSprite=Sprite::create("hint_bkg3.png");
	else if(type==6)
		bgSprite=Sprite::create("hint_bkg4.png");

	bgSprite->setPosition(size.width / 2, size.height/2);
	this->addChild(bgSprite);
}