#include "Game_3_1.h"

Hero *hero_3_1;
	
Game_3_1::Game_3_1(void)
{
	sGlobal->game_3_1=this;
}


Game_3_1::~Game_3_1(void)
{
}
Scene* Game_3_1::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Game_3_1 *layer = Game_3_1::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool Game_3_1::init()
{
	bool bRet = false;
		haveTouchBiqi=true;
		Size size = CCDirector::getInstance()->getWinSize();
		this->setTouchEnabled(true);
	  //CCTMXTiledMap	*_tileMap=CCTMXTiledMap::create("TMX_1_5.tmx");
		//addChild(_tileMap);
		GameMap *gameMap=GameMap::gameMapWithTMXFile("TMX_4_1.tmx");
		this->addChild(gameMap);
		//b
		//���ذ�ť
		backItem = MenuItemImage::create(
			"Thumb_back.png",
			"Thumb_back_pressed.png",
			this,
			menu_selector(Game_3_1::backItemCallback));
		if(! backItem )
			return false;

		// Place the menu item bottom-right conner.
		backItem ->setPosition(36,size.height-36);
		//this->addChild(skipItem);
		Menu* backItemMenu = Menu::create(backItem , NULL);
		backItemMenu->setPosition(Point::ZERO);
		addChild(backItemMenu,2);
      //��ʼ������
		//hero=CCSprite::create("Hero_image.png",CCRectMake(0,50,50,50));
		//hero->setAnchorPoint(ccp(0,0));
		//hero->setPosition(ccp(46*3,46*2+2));
		//addChild(hero,2);
		hero_3_1=Hero::heroWithinLayer();
		addChild(hero_3_1,0,111);
		hero_3_1->setPosition(46*3,46*9);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Npc.plist");
		//GGC->setVisible(false);

		
		
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
	listener->onTouchesBegan = CC_CALLBACK_2(Game_3_1::onTouchesBegan, this);
    //listener->onTouchesMoved = CC_CALLBACK_2(Touches::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Game_3_1::onTouchesEnded, this);
    
	//��Ӽ�����
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();
	return bRet;
}
void Game_3_1::backItemCallback(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->popScene();
}
Animation* Game_3_1::createAnimationByState(State direction)
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
void  Game_3_1::onTouchesBegan (const std::vector<Touch*>& touches, Event  *event)
{

}
void  Game_3_1::onTouchesEnded (const std::vector<Touch*>& touches, Event  *eventt)
{

}
void Game_3_1::update(float dt)
{
	auto hero=this->getChildByTag(111);
	Size size = Director::getInstance()->getWinSize();
	backItem ->setPosition(36-this->getPositionX(),size.height-36);
	

	if (sGlobal->hero->getPositionX()>=15*24&&sGlobal->hero->getPositionX()<=17*24&&sGlobal->hero->isDead==false&&sGlobal->hero->getPositionY()>=10*24&&sGlobal->hero->getPositionY()<=11*24)
	{
		/*float x=hero->getPositionX();
		float y=hero->getPositionY();
		hero->setPosition(x,y-24);*/
		hero->setVisible(false);
		sGlobal->hero->isDead=true;

	}
	//�����ش�
	if (sGlobal->hero->getPositionX()>=17*48&&sGlobal->hero->getPositionX()<=18*48&&sGlobal->hero->isDead==false&&sGlobal->hero->getPositionY()<=5*24)
	{
		auto sting=Sprite::create("sting.png");
		sting->setAnchorPoint(Point(0,0));
		sting->setPosition(18*48,4*24);
		this->addChild(sting);
		sGlobal->hero->isDead=true;

	}
}

