#include "GameMenu.h"


GameMenu::GameMenu(void)
{
}


GameMenu::~GameMenu(void)
{
}
Scene* GameMenu::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameMenu *layer = GameMenu::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

 bool GameMenu::init()
 {
	 CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("startBgm.wav",true);
	 bool bRet = false;
	 do 
	 {
		  
		  //Sprite* bgSprite=Sprite::create("Startup_bkg_gray.jpg");
		 Sprite* bgSprite=Sprite::create("title_background.png");
		  bgSprite->setAnchorPoint(Point(0,0));
		  bgSprite->setPosition(Point(0,0));

		  addChild(bgSprite);
		  Size size = Director::getInstance()->getWinSize();

		  Sprite *ming = Sprite::create("ming1.png");
		  ming->setAnchorPoint (Point(0.7f,0.97f));
		  ming->setPosition(size.width/2,size.height -50);
		  ActionInterval * actionBy=RotateBy::create(2,-40);
		  ActionInterval * actionByBack=actionBy->reverse();
		  ming->runAction(RepeatForever::create(Sequence::create(actionBy,actionByBack,NULL)));
		  addChild(ming);



		  MenuItemImage *startItem = MenuItemImage::create(
			  "start_but1.png",
			  "start_but2.png",
			  this,
			  menu_selector(GameMenu::startButtonCallback));
		  CC_BREAK_IF(! startItem);

		  // Place the menu item bottom-right conner.
		  startItem->setPosition(600,100);
		  //this->addChild(skipItem);
		  Menu* pMenu = Menu::create(startItem, NULL);
		  pMenu->setPosition(CCPointZero);
		  addChild(pMenu);
		   //,,,,,,,,,,,,,,,,,,,,,,
		  MenuItemImage *aboutItem = MenuItemImage::create(
			  "about_but1.png",
			  "about_but2.png",
			  this,
			  menu_selector(GameMenu::aboutItemCallback));
		  CC_BREAK_IF(! aboutItem);

		  // Place the menu item bottom-right conner.
		  aboutItem->setPosition(ccp(360,150));
		  //this->addChild(skipItem);
		  Menu* aboutItemMenu = Menu::create(aboutItem, NULL);
		  aboutItemMenu->setPosition(CCPointZero);
		  addChild(aboutItemMenu);
		  //,,,,,,,,,,,,,,,,,,,,,,
		  MenuItemImage *optionItem = MenuItemImage::create(
			  "option_but1.png",
			  "option_but2.png",
			  this,
			  menu_selector(GameMenu::optionItemCallback));
		  CC_BREAK_IF(! optionItem );

		  // Place the menu item bottom-right conner.
		  optionItem ->setPosition(ccp(500,150));
		  //this->addChild(skipItem);
		  Menu* optionItemMenu = Menu::create(optionItem , NULL);
		  optionItemMenu->setPosition(CCPointZero);
		  addChild(optionItemMenu);
		  
		  bRet = true;
	 }while(0);
	 return bRet;

 }
 void GameMenu::startButtonCallback(Ref*)
 {
	 /*Scene *photo=PhotoSelect::scene();
	 Director::getInstance()->pushScene( (TransitionSlideInR::create(0.3, photo)));*/
	 auto select = StageSelect::scene();
	 Director::getInstance()->pushScene( (TransitionSlideInR::create(0.3f, select)));
 }
 void GameMenu::aboutItemCallback(Ref*)
 {
	 Scene *setting=AboutScene::scene();
	 Director::getInstance()->pushScene(setting);
 }
 void GameMenu::optionItemCallback(Ref*)
 {
	   Scene *setting=SettingScene::scene();
	  Director::getInstance()->pushScene(setting);
 }