#include "Game_2_1.h"

Hero *hero_2_1;
Game_2_1::Game_2_1(void)
{
	sGlobal->game_2_1=this;
}


Game_2_1::~Game_2_1(void)
{
}
Scene* Game_2_1::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Game_2_1 *layer = Game_2_1::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool Game_2_1::init()
{
		bool bRet = false;
		haveTouchBiqi=true;
		Size size = CCDirector::getInstance()->getWinSize();
		this->setTouchEnabled(true);
	  //CCTMXTiledMap	*_tileMap=CCTMXTiledMap::create("TMX_1_5.tmx");
		//addChild(_tileMap);
		GameMap *gameMap=GameMap::gameMapWithTMXFile("TMX_3_1.tmx");
		this->addChild(gameMap);
		backItem = MenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(Game_2_1::backItemCallback));
		if(! backItem )
			return false;

		// Place the menu item bottom-right conner.
		backItem ->setPosition(36,size.height-36);
		//this->addChild(skipItem);
		Menu* backItemMenu = Menu::create(backItem , NULL);
		backItemMenu->setPosition(Point::ZERO);
		addChild(backItemMenu,2);

		hero_2_1=Hero::heroWithinLayer();
		addChild(hero_2_1);
		hero_2_1->setPosition(46*3,46*9);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Npc.plist");
		auto GGC=Sprite::create("heroggc.png");
		GGC->setAnchorPoint(Point(0,0));
		GGC->setPosition(27*24,4*24);
		addChild(GGC,9,999);
		//GGC->setVisible(false);

		auto animationin = Animation::create();
	//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
		animationin->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc1_rs1.png"));
		animationin->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Npc1_rs2.png"));
	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
		animationin->setDelayPerUnit(0.2f);
		animationin->setLoops(-1);
	//��Ϊ��������ִ�У��������ڶ��������л�������
		AnimationCache::getInstance()->addAnimation(animationin, "GGCmove");
		
		
		ControlLayer *controlLayer=ControlLayer::create();
		addChild(controlLayer);
		controlLayer->setPosition(0,0);
		bRet = true;
		if (sGlobal->isMusicOn)
		{
			  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("gameBgm.wav",true);
		}
		
		
		
	
	//����һ���¼���������AllAtOneΪ��㴥��
    auto listener = EventListenerTouchAllAtOnce::create();
 
	//�¼��ص�����
	listener->onTouchesBegan = CC_CALLBACK_2(Game_2_1::onTouchesBegan, this);
    //listener->onTouchesMoved = CC_CALLBACK_2(Touches::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Game_2_1::onTouchesEnded, this);
    
	//��Ӽ�����
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();
	return bRet;
}
void Game_2_1::backItemCallback(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->popScene();
}
Animation* Game_2_1::createAnimationByState(State direction)
{
	Texture2D *heroTexture=TextureCache::getInstance()->addImage("hero.png");
	// CCSpriteFrame *frame0,*frame1,*frame2,*frame3;
	SpriteFrame *frame0=SpriteFrame::createWithTexture(heroTexture,CCRectMake(32*0, 32*direction, 32, 32)); 
	SpriteFrame *frame1=SpriteFrame::createWithTexture(heroTexture,CCRectMake(32*1, 32*direction, 32, 32)); 
	SpriteFrame *frame2=SpriteFrame::createWithTexture(heroTexture,CCRectMake(32*2, 32*direction, 32, 32)); 
	SpriteFrame *frame3=SpriteFrame::createWithTexture(heroTexture,CCRectMake(32*3, 32*direction, 32, 32)); 
	//CCArray *animFrames=CCArray::createWithCapacity(4);
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);
	Animation *animation =CCAnimation::createWithSpriteFrames(animFrames,0.07f);
	//animation->initWithAnimationFrames(animFrames,0.2f,1);
	animFrames.clear();
	return animation;
}
void  Game_2_1::onTouchesBegan (const std::vector<Touch*>& touches, Event  *event)
{

}
void  Game_2_1::onTouchesEnded (const std::vector<Touch*>& touches, Event  *eventt)
{

}
void Game_2_1::update(float dt)
{
	Size size = Director::getInstance()->getWinSize();
	backItem ->setPosition(36-this->getPositionX(),size.height-36);
	//�����ش�
	auto heroc=this->getChildByTag(999);
	if (sGlobal->hero->getPositionX()+50>=31*24&&sGlobal->hero->isDead==false)
	{

			if(sGlobal->hero->getPositionX()+50>=34*24)
			{   
				
				
				if(heroc->getPositionX()<=40*24)
				{
					heroc->setPositionX(heroc->getPositionX()+5);
					runggcmove();
				}
					if(sGlobal->hero->getBoundingBox().intersectsRect(heroc->getBoundingBox()))
						{sGlobal->hero->isDead=true;
							heroc->setPosition(0,3000);
					}
				
			}
	}

	if (sGlobal->hero->getPositionX()+50>=11*24&&sGlobal->hero->getPositionX()+50<=12*24&&sGlobal->hero->getPositionY()<=5*24&&sGlobal->hero->isDead==false)
	{
		
		auto sting1=Sprite::create("sting.png");
		auto sting2=Sprite::create("sting.png");
		sting1->setAnchorPoint(Point::ZERO);
		sting2->setAnchorPoint(Point::ZERO);
		sting1->setPosition(11*24,4*24);
		sting2->setPosition(12*24,4*24);
		this->addChild(sting1);
		this->addChild(sting2);
		sGlobal->hero->isDead=true;
	}
	
}

void Game_2_1::runggcmove()
	
{
	auto heroc=this->getChildByTag(999);
	auto animation2=AnimationCache::getInstance()->getAnimation("GGCmove");
				auto animate2=Animate::create(animation2);
				auto callFunc2 = CallFuncN::create([](Node *node){
						node->removeFromParentAndCleanup(true);
					});
				heroc->runAction(Sequence::create(animate2,callFunc2,NULL));



}