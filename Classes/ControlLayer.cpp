#include "ControlLayer.h"

Sprite *leftSprite;
Sprite *rightSprite;
Sprite *jumpSprite;
bool leftSpriteTouched;
bool rightSpriteTouched;
bool jumpSpriteTouched;

Size size;
ControlLayer::ControlLayer(void)
{
	sGlobal->controlLayer;
}


ControlLayer::~ControlLayer(void)
{
}
bool ControlLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("operationButton.plist");	
	winLayerInitTimes=0;
	failedLayerInitTimes=0;
	leftSpriteTouched=false;
	rightSpriteTouched=false;
	jumpSpriteTouched=false;
	size=Director::getInstance()->getWinSize();
	this->setTouchEnabled(true);
	leftSprite=Sprite::createWithSpriteFrameName("left_butt1.png");
	leftSprite->setPosition(Point(40,40));
	this->addChild(leftSprite);
	rightSprite=Sprite::createWithSpriteFrameName("right_butt1.png");
	rightSprite->setPosition(Point(40+80+20,40));
	this->addChild(rightSprite);
	jumpSprite=Sprite::createWithSpriteFrameName("jump_butt1.png");
	jumpSprite->setPosition(ccp(size.width-70,40));
	addChild(jumpSprite);

	//创建一个事件监听器，AllAtOne为多点触摸
    auto listener = EventListenerTouchAllAtOnce::create();
 
	//事件回调函数
	listener->onTouchesBegan = [=](const vector<Touch *> &pTouches, Event *pEvent){
	for(auto touch:pTouches)
	{
			Point	location=touch->getLocationInView();
			// touch==NULL;
			location=Director::getInstance()->convertToGL(location);
			//左按钮
			if (location.x<80&&location.y<80)
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("left_butt1.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("left_butt2.png"));
				Anim->setDelayPerUnit(0.05f);
				leftSprite->runAction(Animate::create(Anim));
				leftSpriteTouched=true;
			}else if (location.x>100&&location.x<180&&location.y<80)//右按钮
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("right_butt1.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("right_butt2.png"));
				Anim->setDelayPerUnit(0.05f);
				rightSprite->runAction(Animate::create(Anim));
				rightSpriteTouched=true;
			}
			if (location.x>size.width-110&&location.y<80)//跳
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump_butt1.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump_butt2.png"));
				Anim->setDelayPerUnit(0.05f);
				jumpSprite->runAction(Animate::create(Anim));
				jumpSpriteTouched=true;
			}
		}
	};

    listener->onTouchesMoved = [=](const vector<Touch *> &pTouches, Event *pEvent){
	for(auto touch:pTouches)
	{
		Point	location=touch->getLocationInView();
		// touch==NULL;
		location=Director::getInstance()->convertToGL(location);
		if (!(location.x<80&&location.y<80))
		{
			if (location.x<size.width/2)
			{	/*
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("left_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				leftSprite->runAction(Animate::create(Anim));*/
				leftSpriteTouched=false;
			}
		}
		if (!(location.x>100&&location.x<180&&location.y<80))
		{
			if (location.x<size.width/2)
			{
				/*auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("right_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				rightSprite->runAction(Animate::create(Anim));*/
				rightSpriteTouched=false;
			}
		}
		if (!(location.x>size.width-110&&location.y<80))
		{
			if (location.x>size.width/2)
			{/*
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				jumpSprite->runAction(Animate::create(Anim));*/
				jumpSpriteTouched=false;
			}
		}
	}
		
	};
    listener->onTouchesEnded = [=](const vector<Touch *> &pTouches, Event *pEvent){
		for(auto touch:pTouches)
		{
			Point	location=touch->getLocationInView();
			// touch==NULL;
			location=Director::getInstance()->convertToGL(location);
			if (location.x<80&&location.y<80)
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("left_butt2.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("left_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				leftSprite->runAction(Animate::create(Anim));
				leftSpriteTouched=false;
			}else if (location.x>100&&location.x<180&&location.y<80)
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("right_butt2.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("right_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				rightSprite->runAction(Animate::create(Anim));
				rightSpriteTouched=false;
			}
			if (location.x>size.width-110&&location.y<80)
			{
				auto Anim = Animation::create();
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump_butt2.png"));
				Anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump_butt1.png"));
				Anim->setDelayPerUnit(0.05f);
				jumpSprite->runAction(Animate::create(Anim));
				jumpSpriteTouched=false;
			}
		}
		
	};
	//添加监听器
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void ControlLayer::update(float dt)
{
	
	if (sGlobal->hero->isDead)
	{
		this->setTouchEnabled(false);
	}
	if (sGlobal->hero->isDead&&failedLayerInitTimes==0)
	{

	   CCLayer *failedLayer=FailedLayer::create();
	   
	   Layer* game = sGlobal->game_1_1;
	   switch(sGlobal->now_stage)
	   {
	   case 2:
		   game = sGlobal->game_1_1;
		   break;
	   case 3:
		   game = sGlobal->game_2_1;
		   break;
	   case 4:
		   game = sGlobal->game_3_1;
		   break;
	   case 5:
		   game = sGlobal->game_4_1;
		   break;

		   //TODO
	   }
	   if(!game == NULL)
		   game->addChild(failedLayer,2);
	   
	//	CCLayer *victoryLayer=VictoryLayer::create();
	//	sGlobal->game_1_1->addChild(victoryLayer);
		failedLayerInitTimes=1;
		if (sGlobal->isEffectOn)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("lose.wav",false);
		}
	}
	if(sGlobal->hero->isWin&&winLayerInitTimes==0)
	{
		/*CCLayer *victoryLayer=VictoryLayer::create();
			sGlobal->game_1_1->addChild(victoryLayer);*/

		//保存游戏进度
		int store_stage = (sGlobal->now_stage+1 >sGlobal->stage)?sGlobal->now_stage+1:sGlobal->stage;
		UserDefault::getInstance()->setIntegerForKey("GAMESTAGE",store_stage);
		//UserDefault::getInstance()->setIntegerForKey("GAMESTAGE",6);

		Scene* victoryLayer=VictoryLayer::scene();
		Director::getInstance()->pushScene( (CCTransitionSlideInR::create(0.3, victoryLayer)));
		winLayerInitTimes=1;
		if (sGlobal->isEffectOn)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("win.wav",false);
		}
	}
	int hspeed=0;
	if (leftSpriteTouched)
	{
		hspeed=-3;
	}else if (rightSpriteTouched)
	{
		hspeed=3;
	}else{
		hspeed=0;
	}
	
	sGlobal->hero->move(hspeed);
	if (jumpSpriteTouched&&sGlobal->hero->isDead==false)
	{
		if (sGlobal->hero->isJumpDone)
		{
			if (sGlobal->isEffectOn)
			{		
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("jump.wav",false);
			}
			sGlobal->hero->isJumpDone=false;
			sGlobal->hero->vspeed=8;
		}

	}
  sGlobal->hero->jump();
  int x=0,y=0;
  switch(sGlobal->now_stage)
  {
  case 2:
	  x=0-sGlobal->game_1_1->getPositionX();
	  y=0-sGlobal->game_1_1->getPositionY();
	  break;
  case 3:
	  x=0-sGlobal->game_2_1->getPositionX();
	  y=0-sGlobal->game_2_1->getPositionY();
	  break;
  case 4:
	  x=0-sGlobal->game_3_1->getPositionX();
	  y=0-sGlobal->game_3_1->getPositionY();
	  break;
  case 5:
	  x=0-sGlobal->game_4_1->getPositionX();
	  y=0-sGlobal->game_4_1->getPositionY();
	  break;
	  //TODO
  }
  this->setPosition(ccp(x,y));
}