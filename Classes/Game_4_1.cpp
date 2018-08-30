#include "Game_4_1.h"

Hero *hero_4_1;
Game_4_1::Game_4_1(void)
{
	sGlobal->game_4_1=this;
}


Game_4_1::~Game_4_1(void)
{
}
Scene* Game_4_1::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Game_4_1 *layer = Game_4_1::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool Game_4_1::init()
{
	M_move = true;
	isShoot = false;
	isFlee = false;
	isNPCshowed = false;
	isWordshowed = false;
	animDone = false;
	monsterDone = false;
	bool bRet = false;
	haveTouchBiqi=true;
	monsterRemove = false;
	Size size = CCDirector::getInstance()->getWinSize();
	this->setTouchEnabled(true);
	//地图导入
	GameMap *gameMap=GameMap::gameMapWithTMXFile("ZC.tmx");
	this->addChild(gameMap);
	//返回按钮
	backItem = MenuItemImage::create("back_but1.png","back_but2.png",this,
																	menu_selector(Game_4_1::backItemCallback));
	if(! backItem )
		return false;
	// Place the menu item bottom-right conner.
	backItem ->setPosition(ccp(36,size.height-36));
	//this->addChild(skipItem);
	Menu* backItemMenu = Menu::create(backItem , NULL);
	backItemMenu->setPosition(Point::ZERO);
	addChild(backItemMenu,2);


		
		
	//预先创建NPC
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Npc.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("conNpc.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pass4.plist");
	auto NPC = Sprite::createWithSpriteFrameName("Npc2_1.png");
	NPC->setPosition(Point(48*9,400));
	addChild(NPC,1,9);
	//添加飞机飞行动画
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc2_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc2_2.png"));
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);
	//将动画转换为动作
	const auto NPC_fly = Animate::create(animation);
	NPC_fly->setTag(99);
	//执行动作
	NPC->runAction(NPC_fly);
	NPC->runAction(ScaleBy::create(0.5f,2));

	//monster
	auto monster = Sprite::createWithSpriteFrameName("centipede_1.png");
	monster->setAnchorPoint(Point(0.5,0));
	monster->setPosition(Point(48*19,48*2));
	addChild(monster,0,8);
	monster->runAction(ScaleBy::create(0.5f,0.7));
	//monstermove
	auto monstermove = Animation::create();
	monstermove->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("centipede_1.png"));
	monstermove->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("centipede_2.png"));
	monstermove->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("centipede_3.png"));
	monstermove->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("centipede_4.png"));
	monstermove->setDelayPerUnit(0.2f);
	monstermove->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(monstermove,"Mon_move");

	auto wordSP = Sprite::createWithSpriteFrameName("conNpc2_1.png");
	wordSP->setPosition(10*48,300);
	addChild(wordSP,3,10);
	wordSP->setVisible(false);

	auto boat = Sprite::createWithSpriteFrameName("boat.png");
	boat->setPosition(32*48,100+50);
	addChild(boat,3,10);

	//Hero
	hero_4_1=Hero::heroWithinLayer();
	addChild(hero_4_1);
	hero_4_1->setPosition(46*3,48*3);
	ControlLayer *controlLayer=ControlLayer::create();
	addChild(controlLayer);
	controlLayer->setPosition(0,0);
	bRet = true;
	if (sGlobal->isMusicOn)
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("gameBgm.wav",true);

	//创建一个事件监听器，AllAtOne为多点触摸
	auto listener = EventListenerTouchAllAtOnce::create();
	//事件回调函数
	listener->onTouchesBegan = CC_CALLBACK_2(Game_4_1::onTouchesBegan, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(Touches::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Game_4_1::onTouchesEnded, this);
	//添加监听器
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
	return bRet;
}
void Game_4_1::backItemCallback(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->popScene();
}

void  Game_4_1::onTouchesBegan (const std::vector<Touch*>& touches, Event  *event)
{

}
void  Game_4_1::onTouchesEnded (const std::vector<Touch*>& touches, Event  *eventt)
{

}
void Game_4_1::update(float dt)
{
	Size size = Director::getInstance()->getWinSize();
	backItem ->setPosition(36-this->getPositionX(),size.height-36);
	//产生导弹
	
	if (sGlobal->hero->getPositionX()<=8*48&&!isNPCshowed&&!sGlobal->hero->isDead)
	{
		isNPCshowed = true;
		//播放智者的动画
		auto show = MoveBy::create(3.0f,Point(0,-237));
		auto NPC = getChildByTag(9);
		NPC->runAction(show);
	}
	if (sGlobal->hero->getPositionX()>=8*48&&!isWordshowed&&!sGlobal->hero->isDead)
	{
		isWordshowed = true;
		auto NPC = getChildByTag(9);
		//播放智者的动画
		NPC->stopActionByTag(99);
		auto animation = Animation::create();
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc2_g1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc2_g2.png"));
		animation->setDelayPerUnit(1.5f);
		//将动画转换为动作
		const auto NPC_gun = Animate::create(animation);

		auto word = CallFuncN::create([this](Node *node){
			auto anim = Animation::create();
			anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("conNpc2_1.png"));
			anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("conNpc2_2.png"));
			anim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("conNpc_2_3.png"));
			anim->setDelayPerUnit(1.5f);
			auto wordSP = getChildByTag(10);
			wordSP->setVisible(true);
			wordSP->runAction(Animate::create(anim));
		});
		auto callFunc1 = CallFuncN::create([this](Node *node){
			//this->removeChild(sGlobal->controlLayer);
		});
		auto callFunc2 = CallFuncN::create([this](Node *node){
			//this->addChild(sGlobal->controlLayer);
			auto wordSP = getChildByTag(10);
			wordSP->setVisible(false);
			animDone = true;
		});
		//执行动作
		NPC->runAction(Sequence::create(callFunc1,word,NPC_gun,callFunc2,NULL));
	}
	if((animDone&&(sGlobal->hero->getPositionX()>=12*48||sGlobal->hero->getPositionX()<=6.5*48) )|| monsterDone)
	{
		monsterDone = true;
		auto monster = getChildByTag(8);
		auto NPC = getChildByTag(9);
		monster->setPositionX((monster->getPositionX()-2>13*48)?monster->getPositionX()-2 : 13*48 );
		if(monster->getPositionX()>13*48 && !M_move)
		{
			M_move = true;
			auto Mon_move = AnimationCache::getInstance()->getAnimation("Mon_move");
			monster->runAction(Animate::create(Mon_move));
		}
		Rect herRect=CCRectMake(sGlobal->hero->getPositionX(),sGlobal->hero->getPositionY(),32,64);
			if(herRect.intersectsRect(monster->getBoundingBox()))
				sGlobal->hero->isDead=true;


		if(sGlobal->hero->getPositionX() > 12*48 && !isShoot && !isFlee)
		{
			isShoot = true;
			auto bullet = Sprite::create("back_but2.png");
			bullet->runAction(ScaleBy::create(0.01f,0.1));
			bullet->runAction(FlipX::create(true));
			bullet->setPosition(NPC->getPosition()-Point(0,20));
			addChild(bullet,0,7);
		}

		if(sGlobal->hero->getPositionX() < 6.5*48 && !isFlee && !isShoot)
		{
			isFlee = true;
			NPC->runAction(FlipX::create(true));
			auto bullet = Sprite::create("back_but2.png");
			bullet->runAction(ScaleBy::create(0.01f,0.1));
			bullet->setPosition(NPC->getPosition()-Point(0,20));
			addChild(bullet,0,7);
		}
		if(isFlee)
		{
			auto bullet = getChildByTag(7);
			bullet->setPositionX(bullet->getPositionX()-2);
			Rect herRect=CCRectMake(sGlobal->hero->getPositionX(),sGlobal->hero->getPositionY(),32,64);
			if(herRect.intersectsRect(bullet->getBoundingBox()))
				sGlobal->hero->isDead=true;
		}
		if(isShoot)
		{
			auto bullet = getChildByTag(7);
			bullet->setPositionX(bullet->getPositionX()+2);
			Rect herRect=CCRectMake(sGlobal->hero->getPositionX(),sGlobal->hero->getPositionY(),32,64);
			if(herRect.intersectsRect(bullet->getBoundingBox()))
				sGlobal->hero->isDead=true;
			if(!monsterRemove)
			{
				if(monster->getBoundingBox().intersectsRect(bullet->getBoundingBox()))
				{
					monster->setVisible(false);
					monster->setPosition(0,3000);
					monsterRemove = true;
				}
			}
		}
	}



	

}