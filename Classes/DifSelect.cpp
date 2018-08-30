#include "DifSelect.h"

DifSelect::DifSelect()
{

}

DifSelect::~DifSelect()
{

}

Scene* DifSelect::scene()
{
	Scene * scene = NULL;
	do 
	{
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		DifSelect *layer = DifSelect::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool DifSelect::init()
{
	bool bRet = false;
	do 
	{
		Size size = Director::getInstance()->getWinSize();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pass1.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pass1_2.plist");

		//------返回按钮------
		MenuItemImage *backItem = MenuItemImage::create(
			"back_but1.png",
			"back_but2.png",
			this,
			menu_selector(DifSelect::backItemCallback));
		CC_BREAK_IF(! backItem );

		// Place the menu item bottom-right conner.
		backItem ->setPosition(70,size.height-30);
		Menu* backItemMenu = Menu::create(backItem , NULL);
		backItemMenu->setPosition(Point::ZERO);
		addChild(backItemMenu,1);

		//------背景图片------
		Sprite* bgSprite=Sprite::create("pass1_bkg2.png");
		bgSprite->setPosition(size.width / 2, size.height/2);
		this->addChild(bgSprite,0);

		//------选择错误的提示------
		Sprite* falseSprite=Sprite::create("word2.png");
		falseSprite->setPosition(size.width / 2, size.height*4/5+30);
		falseSprite->setVisible(false);
		this->addChild(falseSprite,1,77);

		//------选择难度的四个菜单按钮------
		auto easy = Sprite::createWithSpriteFrameName("jiandan.png");
		auto easyPressed = Sprite::createWithSpriteFrameName("jiandan2.png");
		auto menuItemEasy = MenuItemSprite::create(easy, easyPressed, CC_CALLBACK_1(DifSelect::TouchFalse, this));
		//menuItemPhoto1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemEasy->setPosition(size.width/5, size.height/2);

		auto general = Sprite::createWithSpriteFrameName("yiban1.png");
		auto generalPressed = Sprite::createWithSpriteFrameName("yiban2.png");
		auto menuItemgeneral = MenuItemSprite::create(general, generalPressed, CC_CALLBACK_1(DifSelect::TouchFalse, this));
		menuItemgeneral->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
		menuItemgeneral->setPosition(size.width*2/5+40, size.height/2);

		auto diffcult = Sprite::createWithSpriteFrameName("kunnan1.png");
		auto diffcultPressed = Sprite::createWithSpriteFrameName("kunnan2.png");
		auto menuItemdiffcult = MenuItemSprite::create(diffcult, diffcultPressed, CC_CALLBACK_1(DifSelect::TouchFalse, this));
		menuItemdiffcult->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemdiffcult->setPosition(size.width*3/5-30, size.height/2+10);

		auto diyu = Sprite::createWithSpriteFrameName("diyu1.png");
		auto diyuPressed = Sprite::createWithSpriteFrameName("diyu2.png");
		auto menuItemdiyu = MenuItemSprite::create(diyu, diyuPressed, CC_CALLBACK_1(DifSelect::TouchTrue, this));
		//menuItemPhoto4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemdiyu->setPosition(size.width*4/5, size.height/2+15);

		auto menu = Menu::create(menuItemEasy, menuItemgeneral, menuItemdiffcult,menuItemdiyu,NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);


		bRet=true;
	}while(0);

	return bRet;
}

void DifSelect::backItemCallback(Ref*)
{
	Director::getInstance()->popScene();
}

void DifSelect::TouchTrue(Ref*)
{
	sGlobal->stage = 2;
	UserDefault::getInstance()->setIntegerForKey("GAMESTAGE",sGlobal->stage);
	Scene* loading=Loading::scene();
	Director::getInstance()->pushScene( (TransitionSlideInR::create(0.3, loading)));
}

void DifSelect::TouchFalse(Ref*)
{
	//出现提示语
	/*auto falseTip=this->getChildByTag(77);
	falseTip->setVisible(true);*/

	//sGlobal->hero->isDead=true;

	//------控制层用于死亡时动画生成------
	/*auto gameover=GameoverScene::create();
	gameover->setAnchorPoint(Point::ANCHOR_MIDDLE);
	gameover->setPosition(Point::ZERO);
	this->addChild(gameover,2);*/

	Scene* gameover=GameoverScene::scene(2);
	Director::getInstance()->pushScene(gameover);

	/*Size size = Director::getInstance()->getWinSize();
	Sprite* falseSprite=Sprite::createWithSpriteFrameName("word2.png");
	falseSprite->setPosition(size.width / 2, size.height*4/5+10);
	gameover->addChild(falseSprite,0);*/


}
