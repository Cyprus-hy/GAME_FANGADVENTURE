#include "FailedLayer.h"

Sprite* crySprite;
Sprite* boxSprite;
Sprite* loseSprite;
LabelTTF* pLabel2;
LabelTTF* pLabel3;
MenuItemImage *replayItem;
FailedLayer::FailedLayer(void)
{
	sGlobal->faledLayer=this;
}


FailedLayer::~FailedLayer(void)
{
}
bool FailedLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	Size size=Director::getInstance()->getWinSize();
	//原来弹框
	char temp[20];
	SpriteFrame *box=SpriteFrame::create("prompt_box.png",CCRectMake(0,0,400,280));
	sprintf(temp, "%d", failedboxkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(box,temp);
	
	boxSprite=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(failedboxkey));
	
	switch(sGlobal->now_stage)
	{
	case 2:
		boxSprite->setPosition(size.width/2-sGlobal->game_1_1->getPositionX(),size.height+200);
		break;
	case 3:
		boxSprite->setPosition(size.width/2-sGlobal->game_2_1->getPositionX(),size.height+200);
		break;
	case 4:
		boxSprite->setPosition(size.width/2-sGlobal->game_3_1->getPositionX(),size.height+200);
		break;
	case 5:
		boxSprite->setPosition(size.width/2-sGlobal->game_4_1->getPositionX(),size.height+200);
		break;
		//TODO
	}

	
	this->addChild(boxSprite);
	
	/*原来哭的动画
	crySprite=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(cryFramekey));
	crySprite->setPosition(boxSprite->getPositionX()-113,boxSprite->getPositionY()-50);
	crySprite->runAction(RepeatForever::create(Animate::create(sAnimationMgr->getAnimation(heroCry))));
	this->addChild(crySprite);
	*/

	this->scheduleUpdate();
	FiniteTimeAction *actionMove=MoveBy::create(0.9f,ccp(0,-(size.height/2+200)));
    
	boxSprite->runAction(actionMove);

/*		
		loseSprite=Sprite::create("lose.png",CCRectMake(0,0,163,57));
		loseSprite->setPosition(boxSprite->getPositionX()+75,boxSprite->getPositionY()+60);
		addChild(loseSprite);
		
		pLabel2 = LabelTTF::create("IQ:", "Arial",24);
		pLabel2->setColor(Color3B(0,0,0));
		pLabel2->setPosition(boxSprite->getPositionX()+75,boxSprite->getPositionY()+10);

		this->addChild(pLabel2,2);
*/
	sGlobal->IQ=sGlobal->IQ-50;
	int iq=sGlobal->IQ;
//	char temp[20];

	sprintf(temp, "%d", iq);
	//CCStringMake(sGlobal->IQ);
	pLabel3 = LabelTTF::create(temp, "Arial",30);
	pLabel3->setColor(Color3B(0,0,0));
//	pLabel3->setPosition(boxSprite->getPositionX()+75,boxSprite->getPositionY()-10);

	addChild(pLabel3,2);

	//刷新按钮
	replayItem = MenuItemImage::create(
		"refresh1.png",
		"refresh2.png",
		this,
		menu_selector(FailedLayer::backItemCallback));
	

	// Place the menu item bottom-right conner.
//	replayItem ->setPosition(boxSprite->getPositionX()+75,boxSprite->getPositionY()-80);
	//this->addChild(skipItem);
	Menu* backItemMenu = Menu::create(replayItem , NULL);
	backItemMenu->setPosition(Point::ZERO);
	addChild(backItemMenu,2);

	return true;
}
void FailedLayer::update(float dt)
{
	//crySprite->setPosition(boxSprite->getPositionX()-113,boxSprite->getPositionY()-50);
	//loseSprite->setPosition(boxSprite->getPositionX()+75,boxSprite->getPositionY()+60);
		replayItem ->setPosition(boxSprite->getPositionX()+80,boxSprite->getPositionY()-140);
	//	pLabel2->setPosition(boxSprite->getPositionX()-30+75,boxSprite->getPositionY());
		pLabel3->setPosition(boxSprite->getPositionX()+68,boxSprite->getPositionY()-25);
}
void FailedLayer::backItemCallback(Ref*)
{
	
	Director::getInstance()->popScene();
	Scene* game=Game_1_1::scene();
	switch(sGlobal->now_stage)
	{
	case 2:
		game=Game_1_1::scene();
		break;
	case 3:
		game=Game_2_1::scene();
		break;
	case 4:
		game=Game_3_1::scene();
		break;
	case 5:
		game=Game_4_1::scene();
		break;
	default:
		game=Game_1_1::scene();
		//TODO
	}
	
	Director::getInstance()->pushScene(game);
}