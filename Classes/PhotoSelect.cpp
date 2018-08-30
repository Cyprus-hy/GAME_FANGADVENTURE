#include "PhotoSelect.h"

PhotoSelect::PhotoSelect()
{

}

PhotoSelect::~PhotoSelect()
{

}

Scene* PhotoSelect::scene()
{
	Scene * scene = NULL;
	do 
	{
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		PhotoSelect *layer = PhotoSelect::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool PhotoSelect::init()
{
	bool bRet = false;
	do 
	{
		Size size = Director::getInstance()->getWinSize();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pass1.plist");

		//------返回按钮------
		MenuItemImage *backItem = MenuItemImage::create(
			"back_but1.png",
			"back_but2.png",
			this,
			menu_selector(PhotoSelect::backItemCallback));
		CC_BREAK_IF(! backItem );

		backItem ->setPosition(70,size.height-30);
		Menu* backItemMenu = Menu::create(backItem , NULL);
		backItemMenu->setPosition(Point::ZERO);
		addChild(backItemMenu,1);

		//------背景图片------
		Sprite* bgSprite=Sprite::create("pass_bkg.png");
		bgSprite->setPosition(size.width / 2, size.height/2);
		this->addChild(bgSprite,0);

		//------选择错误的提示------
		/*Sprite* falseSprite=Sprite::create("word1.png");
		falseSprite->setPosition(size.width / 2, size.height*4/5+30);
		falseSprite->setVisible(false);
		this->addChild(falseSprite,1,66);*/

		

		//------选择头像的九个菜单按钮------
		auto photo1 = Sprite::createWithSpriteFrameName("head1_1.png");
		auto photoPressed1 = Sprite::createWithSpriteFrameName("head1_2.png");
		auto menuItemPhoto1 = MenuItemSprite::create(photo1, photoPressed1, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto1->setPosition(0, size.height/2);

		auto photo2 = Sprite::createWithSpriteFrameName("head2_1.png");
		auto photoPressed2 = Sprite::createWithSpriteFrameName("head2_2.png");
		auto menuItemPhoto2 = MenuItemSprite::create(photo2, photoPressed2, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto2->setPosition(size.width*2/7, size.height/2+18);

		auto photo3 = Sprite::createWithSpriteFrameName("head3_1.png");
		auto photoPressed3 = Sprite::createWithSpriteFrameName("head3_2.png");
		auto menuItemPhoto3 = MenuItemSprite::create(photo3, photoPressed3, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto3->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto3->setPosition(size.width*3/7, size.height/2+10);

		auto photo4 = Sprite::createWithSpriteFrameName("head4_1.png");
		auto photoPressed4 = Sprite::createWithSpriteFrameName("head4_2.png");
		auto menuItemPhoto4 = MenuItemSprite::create(photo4, photoPressed4, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto4->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto4->setPosition(size.width*4/7, size.height/2);

		auto photo5 = Sprite::createWithSpriteFrameName("head5_1.png");
		auto photoPressed5 = Sprite::createWithSpriteFrameName("head5_2.png");
		auto menuItemPhoto5 = MenuItemSprite::create(photo5, photoPressed5, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto5->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto5->setPosition(size.width/7+5, size.height/5);

		auto photo6 = Sprite::createWithSpriteFrameName("head6_1.png");
		auto photoPressed6 = Sprite::createWithSpriteFrameName("head6_2.png");
		auto menuItemPhoto6 = MenuItemSprite::create(photo6, photoPressed6, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto6->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto6->setPosition(size.width*2 / 7-3, size.height/5+10);

		auto photo7 = Sprite::createWithSpriteFrameName("head7_1.png");
		auto photoPressed7 = Sprite::createWithSpriteFrameName("head7_2.png");
		auto menuItemPhoto7 = MenuItemSprite::create(photo7, photoPressed7, CC_CALLBACK_1(PhotoSelect::TouchTrue, this));
		menuItemPhoto7->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto7->setPosition(size.width*3 / 7+5, size.height/5+5);

		auto photo8 = Sprite::createWithSpriteFrameName("head8_1.png");
		auto photoPressed8 = Sprite::createWithSpriteFrameName("head8_2.png");
		auto menuItemPhoto8 = MenuItemSprite::create(photo8, photoPressed8, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto8->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		menuItemPhoto8->setPosition(size.width*4/ 7+5, size.height/5);

		auto photo9 = Sprite::createWithSpriteFrameName("head0_1.png");
		auto photoPressed9 = Sprite::createWithSpriteFrameName("head0_2.png");
		auto menuItemPhoto9 = MenuItemSprite::create(photo9, photoPressed9, CC_CALLBACK_1(PhotoSelect::TouchFalse, this));
		menuItemPhoto9->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		menuItemPhoto9->setPosition(size.width*3/4, size.height/2+20);

		auto menu = Menu::create(menuItemPhoto1, menuItemPhoto2, menuItemPhoto3,menuItemPhoto4,
			menuItemPhoto5,menuItemPhoto6,menuItemPhoto7,menuItemPhoto8,menuItemPhoto9,NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);

		bRet=true;
	}while(0);

	return bRet;
}

void PhotoSelect::backItemCallback(Ref*)
{
	//Director::getInstance()->replaceScene(menu);
	Director::getInstance()->popScene();
}

void PhotoSelect::TouchTrue(Ref*)
{
	//跳转到难度选择
	Scene* difselect=DifSelect::scene();
	Director::getInstance()->pushScene( (TransitionSlideInR::create(0.3, difselect)));
}

void PhotoSelect::TouchFalse(Ref*)
{
	//出现提示语
	/*auto falseTip=this->getChildByTag(66);
	falseTip->setVisible(true);*/

	//------控制层用于死亡时动画生成------
	/*auto gameover=GameoverScene::create();
	gameover->setAnchorPoint(Point::ANCHOR_MIDDLE);
	gameover->setPosition(Point::ZERO);
	this->addChild(gameover,2);*/
	Scene* gameover=GameoverScene::scene(6);
	Director::getInstance()->pushScene(gameover);
	
	Size size = Director::getInstance()->getWinSize();
	Sprite* falseSprite=Sprite::createWithSpriteFrameName("word1.png");
	falseSprite->setPosition(size.width / 2, size.height*4/5+10);
	gameover->addChild(falseSprite,0);

}