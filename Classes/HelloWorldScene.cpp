#include "HelloWorldScene.h"
#include "GameMenu.h"
using namespace cocos2d;

Scene* HelloWorld::scene()
{
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio_bgm_startup_cg.mp3",true);
        /*Sprite *sprite1=Sprite::create("StageCG_bkg1_zh.png");*/
		Sprite *sprite1=Sprite::create("start1_1.png");
		sprite1->setAnchorPoint(ccp(0,0));
		sprite1->setPosition(ccp(0,0));
		
		addChild(sprite1);
		
		FadeIn* fadein=FadeIn::create(1.0f);
		FadeIn* fadein2=FadeIn::create(0.1f);
		//sprite1->runAction(fadein);
		/*
		 SpriteFrame * frame0=SpriteFrame::create("StageCG_bkg1_zh.png",CCRectMake(0,0,800,480)); 
	     SpriteFrame * frame1=SpriteFrame::create("StageCG_bkg2_zh.png",CCRectMake(0,0,800,480));
	     SpriteFrame * frame2=SpriteFrame::create("StageCG_bkg3_zh.png",CCRectMake(0,0,800,480));
		 SpriteFrame * frame3=SpriteFrame::create("StageCG_bkg4_zh.png",CCRectMake(0,0,800,480));*/

		 SpriteFrame * frame0=SpriteFrame::create("start1_1.png",CCRectMake(0,0,800,480)); 
	     SpriteFrame * frame1=SpriteFrame::create("start1_2.png",CCRectMake(0,0,800,480));
	     SpriteFrame * frame2=SpriteFrame::create("start2_1.png",CCRectMake(0,0,800,480));
		 SpriteFrame * frame3=SpriteFrame::create("start2_2.png",CCRectMake(0,0,800,480));
		 SpriteFrame * frame4=SpriteFrame::create("start2_3.png",CCRectMake(0,0,800,480)); 
	     SpriteFrame * frame5=SpriteFrame::create("start3.png",CCRectMake(0,0,800,480));
	     SpriteFrame * frame6=SpriteFrame::create("start4_1.png",CCRectMake(0,0,800,480));
		 SpriteFrame * frame7=SpriteFrame::create("start4_2.png",CCRectMake(0,0,800,480));
		 SpriteFrame * frame8=SpriteFrame::create("start4_3.png",CCRectMake(0,0,800,480)); 
	





      //CCArray* array=CCArray::createWithCapacity(4);
		Vector<SpriteFrame*> array;
	  array.pushBack(frame0);
	  array.pushBack(frame1);
	  array.pushBack(frame2);
	  array.pushBack(frame2);
	  array.pushBack(frame2);
	  array.pushBack(frame3);
	  array.pushBack(frame4);
	  array.pushBack(frame5);
	  array.pushBack(frame6);
	  array.pushBack(frame7);
	  array.pushBack(frame8);

	  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("levelOption_pro.plist");
	  Animation* animation=Animation::createWithSpriteFrames(array,2.0f);
	  
	  CCFiniteTimeAction* actionMoveDone=CCCallFuncN::create(this,callfuncN_selector(HelloWorld::animateFinished));
	  sprite1->runAction(CCSequence::create(CCSpawn::createWithTwoActions(fadein,CCAnimate::create(animation)),actionMoveDone,NULL));
		//addChild(sprite2);
        CC_BREAK_IF(! CCLayer::init());
		//Ìø¹ý
		MenuItemImage *skipItem = MenuItemImage::create(
			"StageCG_skip_normal_zh.png",
			"StageCG_skip_pressed_zh.png",
			this,
			menu_selector(HelloWorld::skipCallback));
		CC_BREAK_IF(! skipItem);

		// Place the menu item bottom-right conner.
		skipItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, CCDirector::sharedDirector()->getWinSize().height-50));
		//this->addChild(skipItem);
		Menu* pMenu = Menu::create(skipItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);
        bRet = true;
    } while (0);

    return bRet;
}
 void  HelloWorld::skipCallback(Ref*)
 {
	 Scene *gameMenu=GameMenu::scene();
	 Director::getInstance()->replaceScene( CCTransitionJumpZoom::create(1.0f,gameMenu));
 }
void HelloWorld::animateFinished(Node *sender)
{

	Scene *gameMenu=GameMenu::scene();
	Director::sharedDirector()->replaceScene( CCTransitionJumpZoom::create(1.0f,gameMenu));
}
void HelloWorld::menuCloseCallback(Ref*)
{
    // "close" menu item clicked
    Director::getInstance()->end();
}

