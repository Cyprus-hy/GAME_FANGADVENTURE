#include "SettingScene.h"

Sprite* musicSwitch;
Sprite* effectSwitch;
SettingScene::SettingScene(void)
{
}


SettingScene::~SettingScene(void)
{
}
Scene* SettingScene::scene()
{
	Scene * scene = NULL;
	do 
	{

		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		SettingScene *layer = SettingScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool SettingScene::init()
{
	bool bRet = false;
	do 
	{
		this->setTouchEnabled(true);
		isMusicSwitchOn=sGlobal->isMusicOn;
		isEffectSwitchOn=sGlobal->isEffectOn;
		
		Sprite* bgSprite=Sprite::create("option_interface.png");
		bgSprite->setAnchorPoint(ccp(0,0));
		bgSprite->setPosition(ccp(0,0));

		addChild(bgSprite);

/*
		Sprite* bgSprite2=Sprite::create("Startup_frame.png");
		//bgSprite->setAnchorPoint(ccp(0,0));
		Size size = Director::getInstance()->getWinSize();
		bgSprite2->setPosition(ccp(size.width / 2, size.height/2));
		//  float a=(float)480/800;
		// float b=(float)320/480;
		//  bgSprite2->setScaleX((float)480/800);
		//  bgSprite2->setScaleY((float)320/480);
		//bgSprite2->setScaleX(0.9f);
		//  bgSprite2->setScaleY(0.9f);
		addChild(bgSprite2);
		Sprite* photo_border=Sprite::create("Startup_photo_border.png");
		photo_border->setPosition(ccp(190,190));

		addChild(photo_border);
		Sprite* herface=Sprite::create("Option_gear.png");
		herface->setPosition(ccp(190,190));

		addChild(herface,2);
		Sprite* option=Sprite::create("Startup_lbl_option_zh.png");
		option->setPosition(ccp(size.width/2,240+120));

		addChild(option,2);

		Sprite*  music=Sprite::create("Option_lbl_music_zh.png");
		music->setPosition(ccp(size.width/2-30,240));

		addChild(music,2);

		Sprite*  effect=Sprite::create("Option_lbl_sound_zh.png");
		effect->setPosition(ccp(size.width/2-30,180));

		addChild(effect,2);
*/

/*
		musicSwitch=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(onkey));
		effectSwitch=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(onkey));
*/
		//SpriteFrame *onFrame=SpriteFrame::create("Switch_on.png",CCRectMake(0,0,130,58));
	//	musicSwitch=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(onkey));
		musicSwitch = Sprite::create("music_but1.png");
		//Sprite* bgSprite2=Sprite::create("");
		//effectSwitch=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(onkey));
		effectSwitch=Sprite::create("voice_but1.png");
		Size size = Director::getInstance()->getWinSize();
		//musicSwitch->setPosition(ccp(size.width/2+100,240));
		//effectSwitch->setPosition(ccp(size.width/2+100,180));
		musicSwitch->setPosition(ccp(size.width/2+200,300));
		effectSwitch->setPosition(ccp(size.width/2+200,170));
		addChild(musicSwitch);
		addChild(effectSwitch);
		//......
		MenuItemImage *musicItem = MenuItemImage::create(
			"back_but1.png",
			"back_but2.png",
			this,
			menu_selector(SettingScene::musicItemCallback));
		musicItem->setPosition(Point(70,size.height-36));
		Menu* pMenu = Menu::create(musicItem, NULL);
		pMenu->setPosition(CCPointZero);
		addChild(pMenu);
		
		//..............
		/*
		if (isMusicSwitchOn)
		{
			musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));

		}else
		{
			musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));

		}
		if (isEffectSwitchOn)
		{
			effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));

		}else
		{
			effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));

		}
		*/
		/*
		if (isMusicSwitchOn)
		{
	        musicSwitch = Sprite::create("Switch_on.png");

		}else
		{
			musicSwitch = Sprite::create("Switch_off.png");

		}
		if (isEffectSwitchOn)
		{
			effectSwitch=Sprite::create("Switch_on.png");

		}else
		{
			effectSwitch=Sprite::create("Switch_off.png");

		}
		*/
		bRet=true;
		
	}while(0);


	//创建一个事件监听器，AllAtOne为多点触摸
    auto listener = EventListenerTouchAllAtOnce::create();
 
	//事件回调函数
	listener->onTouchesBegan = [=](const vector<Touch *> &pTouches, Event *pEvent){
	Size size = Director::getInstance()->getWinSize();
	//Touch *touch=(Touch *)pTouches->anyObject();
	for(auto touch:pTouches)
	{
		Point	location=touch->getLocationInView();
		// touch==NULL;
		location=Director::getInstance()->convertToGL(location);
		//if (location.x>size.width/2+100-65&&location.x<size.width/2+100+65&&location.y>210&&location.y<270)size.width/2+300
		//if (location.x>size.width/2+200-effectSwitch->getContentSize ().width/2&&location.x<size.width/2+200+effectSwitch->getContentSize ().width/2&&location.y>180-effectSwitch->getContentSize ().height/2&&location.y<180+effectSwitch->getContentSize ().height/2)
		if (location.x>size.width/2+200-musicSwitch->getContentSize().width/2&& location.x<size.width/2+200+musicSwitch->getContentSize().width/2&&location.y>300-musicSwitch->getContentSize ().height/2&&location.y<300+musicSwitch->getContentSize ().height/2)
		{
			removeChild(musicSwitch);
			if (isMusicSwitchOn)
			{
			/*
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));
				isMusicSwitchOn=false;
				sGlobal->isMusicOn=false;
			*/
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				musicSwitch = Sprite::create("music_but2.png");
				musicSwitch->setPosition(ccp(size.width/2+200,300));
				addChild(musicSwitch);
				isMusicSwitchOn=false;
				sGlobal->isMusicOn=false;
			
			}else
			{
			/*
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio_bgm_home.mp3",true);
				musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));
				isMusicSwitchOn=true;
				sGlobal->isMusicOn=true;

			*/
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("startBgm.wav",true);
				musicSwitch = Sprite::create("music_but1.png");
				musicSwitch->setPosition(ccp(size.width/2+200,300));
				isMusicSwitchOn=true;
				addChild(musicSwitch);
				sGlobal->isMusicOn=true;

			}
		}
	
		if (location.x>size.width/2+200-effectSwitch->getContentSize ().width/2&&location.x<size.width/2+200+effectSwitch->getContentSize ().width/2&&location.y>170-effectSwitch->getContentSize ().height/2&&location.y<170+effectSwitch->getContentSize ().height/2)
		{
			removeChild(effectSwitch);
			if (isEffectSwitchOn)
			{
				//effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));
				effectSwitch=Sprite::create("voice_but2.png");
				effectSwitch->setPosition(ccp(size.width/2+200,170));
				addChild(effectSwitch);
				isEffectSwitchOn=false;
				sGlobal->isEffectOn=false;
			}else
			{
				//effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));
				effectSwitch=Sprite::create("voice_but1.png");
				effectSwitch->setPosition(ccp(size.width/2+200,180));
				addChild(effectSwitch);
				isEffectSwitchOn=true;
				sGlobal->isEffectOn=true;
			}
		}
		//addChild(effectSwitch);
	}		
		
	};
   
	//添加监听器
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return bRet;

}
void SettingScene::musicItemCallback(Ref*)
{
	Director::getInstance()->popScene();
}
/*void  SettingScene::onTouchesEnded (const vector<Touch *> &pTouches, Event *pEvent)
{
	Size size = Director::getInstance()->getWinSize();
	//Touch *touch=(Touch *)pTouches->anyObject();
	for(auto touch:pTouches)
	{
	Point	location=touch->getLocationInView();
	// touch==NULL;
	location=Director::getInstance()->convertToGL(location);
	if (location.x>size.width/2+100-65&&location.x<size.width/2+100+65&&location.y>210&&location.y<270)
	{
		if (isMusicSwitchOn)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));
			isMusicSwitchOn=false;
			sGlobal->isMusicOn=false;
			
		}else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Audio_bgm_home.mp3",true);
			musicSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));
			isMusicSwitchOn=true;
			sGlobal->isMusicOn=true;
		}
	}
	if (location.x>size.width/2+100-65&&location.x<size.width/2+100+65&&location.y>150&&location.y<210)
	{
		if (isEffectSwitchOn)
		{
			effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(offkey));
			isEffectSwitchOn=false;
			sGlobal->isEffectOn=false;
		}else
		{
			effectSwitch->setDisplayFrame(sAnimationMgr->getSpritFrame(onkey));
			isEffectSwitchOn=true;
			sGlobal->isEffectOn=true;
		}
	}
	}
}*/