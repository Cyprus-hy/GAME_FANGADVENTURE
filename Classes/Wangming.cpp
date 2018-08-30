#include "Wangming.h"
#include "GameoverScene.h"
#include "VictoryLayer.h"
#include "SimpleAudioEngine.h"


#define visibleSize Director::getInstance()->getVisibleSize()

USING_NS_CC;

Scene* Wangming::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Wangming::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Wangming::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	flag=false;
	type3=false;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lastPassBgm.wav",true);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LastPass.plist");
 	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("operationButton.plist");

	auto sp = Sprite::createWithSpriteFrameName("airplane_bkg.png");
	//拜访精灵
	//auto visiSize = Director::getInstance()->getVisibleSize();
	sp->setAnchorPoint (Point::ZERO);//设置锚点
	sp->runAction(ScaleBy::create(0.01f,1.2));
	sp->setPosition(0,0);//左下角
	//将该精灵放到层上面
    sp->getTexture()->setAliasTexParameters();//抗锯齿	
	this->addChild(sp,0,10);//一层





	auto bg2 = Sprite::createWithSpriteFrameName("airplane_bkg.png");//第二张图
	bg2->setAnchorPoint (Point(0,0));//设置锚点
	bg2->runAction(ScaleBy::create(0.01f,1.2));
	bg2->setPosition(sp->getContentSize().width-5,0);//横坐标为0 纵坐标接第一张图
	//bg2->setPosition(sp->getContentSize().width,visibleSize.height);
	//bg2->getTexture()->setAntiAliasTexParameters();//抗锯齿
	bg2->getTexture()->setAliasTexParameters();//抗锯齿
	this->addChild(bg2,0,11);//第二层
	
	

	
	// Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	//m_down=m_jump=m_left=m_right=m_up=FALSE;
	m_down=false;
	m_jump=false;
	m_left=false;
	m_right=false;
	m_up=false;
	
	
	
	m_high=0;
	m_score=0;

	
	auto sp3=Sprite::createWithSpriteFrameName("boat1.png");
	sp3->setPosition(Point(100,100));
	this->addChild(sp3,0,3);
 


	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boat1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boat2.png"));
	//切换的频率
	animation->setDelayPerUnit(0.2f);
	//切换的周期数 数字是几就切换几次 -1则为一直切换
	animation->setLoops(-1);
	//将动画转换为动作
	auto action = Animate::create(animation);
	//执行动作
	sp3->runAction(action);



	auto labelup=Sprite::createWithSpriteFrameName("jump_butt1.png");
	labelup->setPosition(Point(100,150));
	labelup->setTag(1003);
	this->addChild(labelup);

	auto labeldown=Sprite::create("down_butt1.png");
	labeldown->setPosition(Point(100,50));
	labeldown->setTag(1002);
	this->addChild(labeldown);

	auto labelleft=Sprite::createWithSpriteFrameName("left_butt1.png");
	labelleft->setPosition(Point(50,100));
	labelleft->setTag(1000);
	this->addChild(labelleft);

	auto labelright=Sprite::createWithSpriteFrameName("right_butt1.png");
	labelright->setPosition(Point(150,100));
	labelright->setTag(1001);
	this->addChild(labelright);
	
	auto listener=EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event *){
	
		log("==============began");
		for(auto touch:touches)
		{
			auto touchPos=touch->getLocation();
			if(!m_left)
			{
				m_left=labelleft->getBoundingBox().containsPoint(touchPos);
				
			}

			
			if(!m_down)
			{
				m_down=labeldown->getBoundingBox().containsPoint(touchPos);
			}

			if(!m_up)
			{
				m_up=labelup->getBoundingBox().containsPoint(touchPos);
			}


			if(!m_right)
			{
				m_right=labelright->getBoundingBox().containsPoint(touchPos);
			}

		}
	};

	listener->onTouchesMoved= [=](const std::vector<Touch*>& touches, Event *)
	{
	log("==============began");
	
	};
	listener->onTouchesEnded = [=](const std::vector<Touch*>& toucher, Event *){
	//m_down=m_jump=m_left=m_right=m_up=FALSE;
	log("==============end");
	m_down=false;
	m_jump=false;
	m_left=false;
	m_right=false;
	m_up=false;

			


	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,sp3);





 	speed = 0;
	doubleBullet = false;
	isPaused = false;
	DBulletNum = 0;
	bombNum = 0;
	Hp = 100;
	m_boom=0;



	schedule(schedule_selector(Wangming::ufo1Create),5.5f);
	schedule(schedule_selector(Wangming::ufo2Create),10.0f);
	schedule(schedule_selector(Wangming::bulletUpdate),0.2f);
	schedule(schedule_selector(Wangming::createSmallEnemy), 2, -1, 3);
	schedule(schedule_selector(Wangming::createMiddleEnemy), 5, -1, 6);
	//this->schedule(schedule_selector(newgame::createBigEnemy), 20, -1, 12);
	//schedule(schedule_selector(Wangming::createBigEnemy), 10, -1, 1);
	createBigEnemy(0.0);


	auto spriteBomb = Sprite::createWithSpriteFrameName("bomb.png");
	//创建了一个精灵菜单项，参数（平时显示的精灵，被点击时显示的精灵， 被点击时触发的代码）
	auto menuItemBomb = MenuItemSprite::create(spriteBomb, spriteBomb, [=](Ref *){
		   this->m_boom--;
		   CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pa.wav");
		    flag=true;
			auto animation = Animation::create();
			for (int i = 1; i <= 2; i++)
			{
				//拼接字符串，参见C中的printf函数
				auto png = StringUtils::format("boat_down%d.png", i);
				//根据精灵帧名称从精灵帧缓存中获取精灵帧
				auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
				animation->addSpriteFrame(spriteFrame);
			}
			//默认动画只执行一次，所以这里缺省
			animation->setDelayPerUnit(0.2f);
			auto animate = Animate::create(animation);
	
			auto callFunc = CallFunc::create([=]()
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				auto scene = GameoverScene::scene(6);
				Director::getInstance()->replaceScene(scene);
			});
			sp3->stopAllActions();
			//Director::getInstance()->pause();
			sp3->runAction(Sequence::create(animate, callFunc, NULL));
			
			updateBombLabel() ;



	});
	
	menuItemBomb->setPosition(visibleSize.width-150,50);
	menuItemBomb->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	//菜单项不可直接添加到层中渲染，需要菜单容器进行封装
	auto menu = Menu::create();
	menu->addChild(menuItemBomb,99,100);
	//默认菜单的坐标中中央，这里不方便定位，所以置零，让菜单项自己定位
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 99,101);	//注意Zorder
	
	


	//炸弹数会变化，选用类它提供的fnt字体
	auto lblBombCount = Label::createWithBMFont("font.fnt", "X0");
	lblBombCount->setPosition(menuItemBomb->getContentSize().width+visibleSize.width-150, 50);
	lblBombCount->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	lblBombCount->setColor(Color3B::BLACK);
	this->addChild(lblBombCount, 99, 91);

	updateBombLabel() ;




	this->scheduleUpdate();
	return true;

}


void Wangming::update(float dt)
{
	auto bghero3=this->getChildByTag(3);	

	//边界拦截
	float minX = bghero3->getContentSize().width/2;
	float maxX = visibleSize.width-minX;
	float minY = bghero3->getContentSize().height/2;
	float maxY = visibleSize.height-minY;


	 
	
	
	auto leftBtn = this->getChildByTag(1000);
	if(m_left)
	{
		bghero3->setPositionX(MAX(bghero3->getPositionX()-4,minX));
		auto animation = Animation::create();
		for(int i=2;i>=1;i--)
		{
			auto png = StringUtils::format("left_butt%d.png",i);
			//animation->addSpriteFrame();
			animation->addSpriteFrameWithFileName(png);
		}
		animation->setDelayPerUnit(0.3f);
		auto animate = Animate::create(animation);
		leftBtn->runAction(animate);
	}
	if(m_right)
	{
		auto rightBtn = this->getChildByTag(1001);
		bghero3->setPositionX(MIN(maxX,bghero3->getPositionX()+4));
		auto animation = Animation::create();
		for(int i=2;i>=1;i--)
		{
			auto png = StringUtils::format("right_butt%d.png",i);
			//animation->addSpriteFrame();
			animation->addSpriteFrameWithFileName(png);
		}
		animation->setDelayPerUnit(0.3f);
		auto animate = Animate::create(animation);
		rightBtn->runAction(animate);
	}
	if(m_up)
	{
		auto upBtn = this->getChildByTag(1003);
		bghero3->setPositionY(MIN(maxY,bghero3->getPositionY()+4));
		auto animation = Animation::create();
		for(int i=2;i>=1;i--)
		{
			auto png = StringUtils::format("jump_butt%d.png",i);
			//animation->addSpriteFrame();
			animation->addSpriteFrameWithFileName(png);
		}
		animation->setDelayPerUnit(0.3f);
		auto animate = Animate::create(animation);
		upBtn->runAction(animate);
	}
	if(m_down)
	{
		bghero3->setPositionY(MAX(minY,bghero3->getPositionY()-4));
		auto downBtn = this->getChildByTag(1002);
		auto animation = Animation::create();
		for(int i=2;i>=1;i--)
		{
			auto png = StringUtils::format("down_butt%d.png",i);
			//animation->addSpriteFrame();
			animation->addSpriteFrameWithFileName(png);
		}
		animation->setDelayPerUnit(0.3f);
		auto animate = Animate::create(animation);
		downBtn->runAction(animate);
	}



	//找到那个背景图片
	auto bg = this->getChildByTag(10);
	auto bg2 = this->getChildByTag(11);

	bg->setPosition(bg->getPositionX()-2,bg->getPositionY());
	bg2->setPositionX(bg->getPositionX()+bg->getContentSize().width-5);	
	if(bg2->getPositionX()<0)
	{
		bg->setPositionX(0);
		
	}

	//清除子弹
	Vector<Sprite*> remove_bullets;
	for (auto bul :bullets_vec)
	{
		bul->setPosition(bul->getPositionX()+20, bul->getPositionY() );
		if(bul->getPositionX() >= visibleSize.width)
			remove_bullets.pushBack(bul);
	}


	//道具1与英雄的碰撞
	auto plane = this->getChildByTag(3);
	Vector<Sprite *> removableUfos;
	for (auto ufo : this->ufo1_vec)
	{
		if (ufo->getBoundingBox().intersectsRect(plane->getBoundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getUfo.wav");
			doubleBullet = true;
			DBulletNum = 30;
			this->removeChild(ufo);
			removableUfos.pushBack(ufo);
		}
	}
	for(auto ufo : removableUfos) 
	{
		this->ufo1_vec.eraseObject(ufo);
	}
	removableUfos.clear();
	//道具2与英雄的碰撞
	for (auto ufo : this->ufo2_vec)
	{
		if (ufo->getBoundingBox().intersectsRect(plane->getBoundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("getUfo.wav");
			this->m_boom++;
			//auto lbl = (Label *)this->getChildByTag(91);
					//lbl->setString(StringUtils::format("X%d", this->m_boom));
		    this->updateBombLabel() ;
			this->removeChild(ufo);
			removableUfos.pushBack(ufo);
		}
	}
	for(auto ufo : removableUfos) 
	{
		this->ufo2_vec.eraseObject(ufo);
	}
	removableUfos.clear();

	
	
	
	Vector<Enemy*> vRemoveEnemys;//需要移除的敌机
    //敌机下掉
	for(auto ene :m_vEnemys)
	{
		if(ene->type!=3)
		{
		ene->setPositionX(ene->getPositionX()-8);
		}
		else
		{
			float minY=ene->getContentSize().height/2;
			float maxY=visibleSize.height-minY;
			if(!type3)
			{
				ene->setPositionY(ene->getPositionY()-5);
				if(ene->getPositionY()<=minY)
					type3=true;
			}
			else
			{
				ene->setPositionY(ene->getPositionY()+5);
				if(ene->getPositionY()>=maxY)
					type3=false;
			}
		}
		if(ene->getPositionX()<=0)
		{
			 this->removeChild(ene);
			 vRemoveEnemys.pushBack(ene);
		}
     }



	for(auto enemy :m_vEnemys)
	{

		if (enemy->getBoundingBox().intersectsRect(bghero3->getBoundingBox()))
		{
			  enemy->blood--;


					if(enemy->blood<=0)
					{
						m_score++;
				        enemy->down(enemy->type);
				        vRemoveEnemys.pushBack(enemy);
					}
	               if(enemy->type==3)
				   {
	                      if(flag==true)
						  {
							   CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
							   enemy->down(enemy->type);
							   vRemoveEnemys.pushBack(enemy);
							   auto s = VictoryLayer::scene();
							   Director::getInstance()->replaceScene(s);
						 }

				   }
			
				auto animation = Animation::create();
				for (int i = 1; i <= 2; i++)
				{
				//拼接字符串，参见C中的printf函数
					auto png = StringUtils::format("boat_down%d.png", i);
				//根据精灵帧名称从精灵帧缓存中获取精灵帧
					auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
					animation->addSpriteFrame(spriteFrame);
				}
			//默认动画只执行一次，所以这里缺省
				animation->setDelayPerUnit(0.2f);
				auto animate = Animate::create(animation);
				auto callFunc = CallFunc::create([=]()
				{
					 CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
					  auto scene = GameoverScene::scene(6);
				      Director::getInstance()->replaceScene(scene);
				});
				bghero3->stopAllActions();
	
			    bghero3->runAction(Sequence::create(animate, callFunc, NULL));

		

			
		}

}












	
	for(auto ene :m_vEnemys)
	{
		for(auto bul : bullets_vec)
		{
			if(ene->getBoundingBox().intersectsRect(bul->getBoundingBox()))
			{
				ene->blood--;
				ene->hit();
				remove_bullets.pushBack(bul);
				this->removeChild(bul);
				if(ene->blood<=0)
				{
					ene->down(ene->type);
					vRemoveEnemys.pushBack(ene);
	             }
				
		    }
		}
}




	for(auto ene:vRemoveEnemys)
	{
		m_vEnemys.eraseObject(ene);
	}
    
	vRemoveEnemys.clear();


	for (auto bul : remove_bullets )
	{
		bullets_vec.eraseObject(bul);
		this->removeChild(bul);
	}
	remove_bullets.clear();

}

void Wangming::bulletUpdate(float delta)
{
	auto plane = this->getChildByTag(3);
	//bullet
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.3f);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("so.wav");
	if(doubleBullet)
	{
		DBulletNum-=2;
		if(DBulletNum<=0)
		{
			doubleBullet = false;
		}
		auto LDbullet = Sprite::create("double_le_bul2.png");
		auto RDbullet = Sprite::create("double_ri_bul2.png");
		LDbullet->setPosition(plane->getPosition()+Point(plane->getContentSize().width/2,-20));
		RDbullet->setPosition(plane->getPosition()+Point(plane->getContentSize().width/2,20));
		this->addChild(LDbullet,0);
		this->addChild(RDbullet,0);
		bullets_vec.pushBack(LDbullet);		
		bullets_vec.pushBack(RDbullet);
	}
	else
	{
		auto bullet = Sprite::create("single_bul1.png");
		bullet->setPosition(plane->getPosition()+Point(plane->getContentSize().width/2,0));
		this->addChild(bullet,0);
		bullets_vec.pushBack(bullet);
	}
}


void Wangming::ufo1Create(float delta) 
{
	auto ufo = Sprite::create("ufo1.png");
	//设置随机水平位置坐标
	float minX = ufo->getContentSize().width/2;
	float maxX = visibleSize.width-minX;
	float x = rand() % (int)(maxX-minX)+minX;
	float y = visibleSize.height+ufo->getContentSize().height/2;
	ufo->setPosition(x, y);
	this->addChild(ufo, 0);
	this->ufo1_vec.pushBack(ufo);

	//移动道具（下-上-下-销毁）
	auto move1 = MoveBy::create(1.5f, Point(0, -400));
	auto move2 = MoveBy::create(1.5f, Point(0, 400));
	auto move3 = MoveTo::create(0.5f, Point(x, -ufo->getContentSize().height/2));
	auto callFunc = CallFuncN::create([](Node *node){
		node->removeFromParentAndCleanup(true);
	});
	ufo->runAction(Sequence::create(move1, move2, move3, callFunc, NULL));
}

void Wangming::ufo2Create(float delta) 
{
	auto ufo = Sprite::create("ufo2.png");
	//设置随机水平位置坐标
	float minX = ufo->getContentSize().width/2;
	float maxX = visibleSize.width-minX;
	float x = rand() % (int)(maxX-minX)+minX;
	float y = visibleSize.height+ufo->getContentSize().height/2;
	ufo->setPosition(x, y);
	this->addChild(ufo, 0);
	this->ufo2_vec.pushBack(ufo);

	//移动道具（下-上-下-销毁）
	auto move1 = MoveBy::create(1.5f, Point(100, -400));
	auto move2 = MoveBy::create(1.0f, Point(-50, 200));
	auto move3 = MoveTo::create(0.5f, Point(x+50, -ufo->getContentSize().height/2));
	auto callFunc = CallFuncN::create([](Node *node){
		node->removeFromParentAndCleanup(true);
	});
	ufo->runAction(Sequence::create(move1, move2, move3, callFunc, NULL));
}




/*
void Wangming::createSmallEnemy(float) {
	auto enemy =Sprite::create("little1.png");
	//随机小数*（max-min+1）+min+1
	float minY = enemy->getContentSize().height/2;
	float maxY = visibleSize.width-minY;
	float x = visibleSize.width+enemy->getContentSize().width/2;
	float y = rand() % (int)(maxY-minY)+minY;

	enemy->setPosition(x, y);
	this->addChild(enemy, 4);
	this->m_vEnemys1.pushBack(enemy);
	
}

*/


//创建敌机的函数
void Wangming::createEnemyByType(int type)
{

	auto enemy =Enemy::create(type);
	enemy->type=type;
	enemy->init();
		//边界拦截
	//随机小数*（max-min+1）+min+1
	float minY = enemy->getContentSize().height/2;
	float maxY = visibleSize.height-minY;
	float x = visibleSize.width+enemy->getContentSize().width/2;
	float y = rand() % (int)(maxY-minY)+minY;

	if(enemy->type==3)
		x=x-enemy->getContentSize().width;
	enemy->setPosition(x, y);
	this->addChild(enemy, 4);
	this->m_vEnemys.pushBack(enemy);
}

void Wangming::createSmallEnemy(float) {
	createEnemyByType(1);
}

void Wangming::createMiddleEnemy(float) {
	createEnemyByType(2);
}

void Wangming::createBigEnemy(float) {
	createEnemyByType(3);
}




void Wangming::updateBombLabel() 
{
	//先找到菜单，再通过菜单找到精灵菜单项
	auto menu = this->getChildByTag(101);
	auto item = menu->getChildByTag(100);
	//获得标签，思考为什么要强制类型转换

	auto lbl = (Label *)this->getChildByTag(91);

	if (this->m_boom <= 0)
	{
		item->setVisible(false);
		lbl->setVisible(false);
	} else if (this->m_boom == 1)
	{
		item->setVisible(true);
		lbl->setVisible(false);
	} else {
		item->setVisible(true);
		lbl->setVisible(true);
		//别忘了更新炸弹数
		lbl->setString(StringUtils::format("X%d", this->m_boom));
	}

}


