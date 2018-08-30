#include "StageSelect.h"
#include "Wangming.h"

StageSelect::StageSelect(void)
{
}


StageSelect::~StageSelect(void)
{

}
CCScene* StageSelect::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		StageSelect *layer = StageSelect::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool StageSelect::init()
{
	//UserDefault::getInstance()->getIntegerForKey("GAMESTAGE",1);
	sGlobal->stage = UserDefault::getInstance()->getIntegerForKey("GAMESTAGE",1);
	Size visableSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("levelOption_pro.plist");//导入背景文件
	bool bRet = false;
	do 
	{
		Size size = Director::sharedDirector()->getWinSize();
		Sprite* bgSprite=Sprite::create("level_option_bkg.png");
		bgSprite->setPosition(Point(size.width / 2, size.height/2));
		this->addChild(bgSprite);

			CCMenuItemImage *backItem = CCMenuItemImage::create(
			"back_but1.png",
			"back_but2.png",
			this,
			menu_selector(StageSelect::backItemCallback));
		CC_BREAK_IF(! backItem );
		// Place the menu item bottom-right conner.
		backItem ->setPosition(ccp(120,size.height-110));
		//this->addChild(skipItem);
		CCMenu* backItemMenu = CCMenu::create(backItem , NULL);
		backItemMenu->setPosition(CCPointZero);
		addChild(backItemMenu);

		Menu* stageMenu = Menu::create();
		createStageBtn(sGlobal->stage, stageMenu);
		stageMenu->setPosition(Point(0,0));
		addChild(stageMenu);

		
		 bRet = true;
		
	}while(0);
	return bRet;
}
void StageSelect::backItemCallback(Ref*)
{
	CCDirector::sharedDirector()->popScene();
}
/*void StageSelect::stageOneItemCallback(Ref*)
{
	CCScene* game_1_1=Game_1_1::scene();
	 CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game_1_1)));

}*/

void StageSelect::createStageBtn(int openNum, Menu* menu)
{
	CCSize visableSize = CCDirector::sharedDirector()->getWinSize();

	for(int i=1;i<=openNum;i++){
		auto btn1 = Sprite::createWithSpriteFrameName(StringUtils::format("%dbutt1.png",i));
		auto btn2 = Sprite::createWithSpriteFrameName(StringUtils::format("%dbutt2.png",i));
		auto stageItem = MenuItemSprite::create(btn1,btn2,[=](Ref*){
			sGlobal->now_stage = i;
			if(i==1){
				CCScene* photoSelect=PhotoSelect::scene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, photoSelect)));
			}else if(i==2){
				CCScene* game_1_1=Game_1_1::scene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game_1_1)));
			}else if(i==3){
				CCScene* game_2_1=Game_2_1::scene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game_2_1)));
			}else if(i==4){
				CCScene* game_3_1=Game_3_1::scene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game_3_1)));
			}else if(i==5){
				CCScene* game_4_1=Game_4_1::scene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game_4_1)));
			}else if(i == 6){
				Scene* game=Wangming::createScene();
				CCDirector::sharedDirector()->pushScene( (CCTransitionSlideInR::create(0.3, game)));
			}
			
		});
		CC_BREAK_IF(! stageItem );

		// Place the menu item bottom-right conner.
		stageItem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		if(i<=3)
			stageItem ->setPosition(visableSize.width*(i+1)/7,visableSize.height*7/12+10);
		else
			stageItem ->setPosition(visableSize.width*(i-2)/7,visableSize.height*5/12-10);

		menu->addChild(stageItem);
	}
	for(int i=openNum+1;i<=STAGECOUNT;i++){
		auto btn1 = Sprite::createWithSpriteFrameName(StringUtils::format("lock%d.png",i));
		auto stageItem = MenuItemSprite::create(btn1,btn1,[=](Ref*){

		});
		CC_BREAK_IF(! stageItem );

		// Place the menu item bottom-right conner.
		stageItem->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		if(i<=3)
			stageItem ->setPosition(visableSize.width*(i+1)/7,visableSize.height*7/12+10);
		else
			stageItem ->setPosition(visableSize.width*(i-2)/7,visableSize.height*5/12-10);
		menu->addChild(stageItem);
	}
}