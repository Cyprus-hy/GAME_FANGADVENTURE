#include "Game_1_1.h"

	Hero *hero;
	Sprite* shi;
	Sprite* daodan;
	int shicount;
	int daodancount;
	MenuItemImage *backItem;
Game_1_1::Game_1_1(void)
{
	sGlobal->game_1_1=this;
}


Game_1_1::~Game_1_1(void)
{
}
Scene* Game_1_1::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Game_1_1 *layer = Game_1_1::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool Game_1_1::init()
{
	bool bRet = false;
		daodancount=0;
		shicount=0;
		haveTouchBiqi=true;
		Size size = CCDirector::getInstance()->getWinSize();
		this->setTouchEnabled(true);
	  //CCTMXTiledMap	*_tileMap=CCTMXTiledMap::create("TMX_1_5.tmx");
		//addChild(_tileMap);
		GameMap *gameMap=GameMap::gameMapWithTMXFile("TMX_2_1.tmx");
		this->addChild(gameMap);
		//返回按钮
		backItem = MenuItemImage::create(
			"back_but1.png",
			"back_but2.png",
			this,
			menu_selector(Game_1_1::backItemCallback));
		if(! backItem )
			return false;

		// Place the menu item bottom-right conner.
		backItem ->setPosition(Point(70,size.height-30));
		//this->addChild(skipItem);
		Menu* backItemMenu = Menu::create(backItem , NULL);
		backItemMenu->setPosition(Point::ZERO);
		addChild(backItemMenu,2);
      //初始化精灵
		//hero=CCSprite::create("Hero_image.png",CCRectMake(0,50,50,50));
		//hero->setAnchorPoint(ccp(0,0));
		//hero->setPosition(ccp(46*3,46*2+2));
		//addChild(hero,2);
		hero=Hero::heroWithinLayer();
		addChild(hero);
		hero->setPosition(46*3,46*9);
		ControlLayer *controlLayer=ControlLayer::create();
		addChild(controlLayer);
		controlLayer->setPosition(0,0);
		bRet = true;
		if (sGlobal->isMusicOn)
		{
			  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("gameBgm.wav",true);
		}
		
		
		
	
	//创建一个事件监听器，AllAtOne为多点触摸
    auto listener = EventListenerTouchAllAtOnce::create();
 
	//事件回调函数
	listener->onTouchesBegan = CC_CALLBACK_2(Game_1_1::onTouchesBegan, this);
    //listener->onTouchesMoved = CC_CALLBACK_2(Touches::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(Game_1_1::onTouchesEnded, this);
    
	//添加监听器
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return bRet;
}
void Game_1_1::backItemCallback(Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->popScene();
}
Animation* Game_1_1::createAnimationByState(State direction)
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
void  Game_1_1::onTouchesBegan (const std::vector<Touch*>& touches, Event  *event)
{

}
void  Game_1_1::onTouchesEnded (const std::vector<Touch*>& touches, Event  *eventt)
{

}
void Game_1_1::update(float dt)
{
	Size size = Director::getInstance()->getWinSize();
	backItem ->setPosition(36-this->getPositionX(),size.height-36);
	//产生导弹
	
	
	//产生便便
	
	/*if (sGlobal->hero->getPositionX()+50>=22*48&&shicount==0&&sGlobal->hero->isDead==false)
	{
		shi=Sprite::create("shi.png",CCRectMake(0,0,47,57));
		shicount++;
		shi->setAnchorPoint(ccp(0,0));
		shi->setPosition(ccp(22*48,480));
		this->addChild(shi);
	}
	if (shicount==1)
	{
		shi->setPosition(22*48,shi->getPositionY()-6);
		if (shi->getPositionY()<-50)
		{
			shi->setPosition(ccp(22*48,480));
		}
		Rect herRect=CCRectMake(sGlobal->hero->getPositionX(),sGlobal->hero->getPositionY(),45,45);
		if (herRect.intersectsRect(CCRectMake(shi->getPositionX()+6,shi->getPositionY()+6,47,57)))
		{
			sGlobal->hero->isDead=true;
			shicount=0;
		}
	}*/
}