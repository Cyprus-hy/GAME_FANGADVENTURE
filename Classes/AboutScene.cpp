#include "AboutScene.h"


AboutScene::AboutScene(void)
{
}


AboutScene::~AboutScene(void)
{
}
Scene* AboutScene::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		AboutScene *layer = AboutScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool AboutScene::init()
{
	bool bRet = false;
	do 
	{
/*  Sprite* bgSprite=Sprite::create("Startup_bkg_gray.jpg");
	bgSprite->setAnchorPoint(Point(0,0));
	bgSprite->setPosition(Point(0,0));

	this->addChild(bgSprite);
*/
	Sprite* bgSprite2=Sprite::create("about_interface.png");
	//bgSprite->setAnchorPoint(ccp(0,0));
	Size size = Director::getInstance()->getWinSize();
	bgSprite2->setPosition(size.width / 2, size.height/2);
	
	//  float a=(float)480/800;
	// float b=(float)320/480;
	//  bgSprite2->setScaleX((float)480/800);
	//  bgSprite2->setScaleY((float)320/480);
	//bgSprite2->setScaleX(0.9f);
	//  bgSprite2->setScaleY(0.9f);
	this->addChild(bgSprite2);
	
	
	
	
	


	MenuItemImage *musicItem = MenuItemImage::create(
		"back_but1.png",
		"back_but2.png",
		this,
		menu_selector(AboutScene::musicItemCallback));
	//musicItem->setPosition(size.width/2,120);
	musicItem->setPosition(Point(70,size.height-36));
	Menu* pMenu = Menu::create(musicItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
	bRet=true;

	}while(0);
	return bRet;

}
void AboutScene::musicItemCallback(Ref*)
{
	Director::getInstance()->popScene();
}