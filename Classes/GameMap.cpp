#include "GameMap.h"
Sprite *hideBlock;
Sprite* goldSprite;
GameMap::GameMap(void)
{
	sGlobal->gameMap=this;
}


GameMap::~GameMap(void)
{
	this->unscheduleAllSelectors();
}
void GameMap::removeFloor(CCPoint point)
{
	
	int maxy=sGlobal->gameMap->getMapSize().height;
	int heroheight=sGlobal->hero->getContentSize().height;
	for (int y=maxy;y>=point.y;y--)
	{
		int id=platformDynamicLayer->tileGIDAt(point);
		if(id)
		{
			Sprite *sprite=platformDynamicLayer->tileAt(point);
			float s=(maxy-point.y)*this->getTileSize().height+heroheight;//Ҫ�ߵľ���
			MoveTo *ccmoveto=MoveTo::create(s/9.0f,ccp(point.x*this->getTileSize().width,-heroheight));
		    sprite->runAction(ccmoveto);
			platformDynamicLayer->removeTileAt(point);
		}
	}
}

//��̬��������������GameMapʵ��
GameMap* GameMap::gameMapWithTMXFile(const char *tmxFile)
{
	//newһ������
	GameMap *pRet = new GameMap();
	//����init����
	if (pRet->initWithTMXFile(tmxFile))
	{
		//���ö����init����
		pRet->extraInit();
		//��ʵ������autorelease�أ�ͳһ��������ƶ������������
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//TliedMap����ĳ�ʼ������
void GameMap::extraInit()
{
	//��������ͼ����������
	enableAnitiAliasForEachLayer();
	//��ʼ���������
	 platformLayer = this->layerNamed("Platform");
	platformDynamicLayer = this->layerNamed("PlatformDynamic");
	hideBlockLayer = this->layerNamed("HideBlock");
	biqiLayer = this->layerNamed("biqi");
	hideBlockLayer->setVisible(false);
	//platformDynamicLayer->setVisible(false);
	//itemLayer = this->layerNamed("item");
	//doorLayer = this->layerNamed("door");

	
}
void GameMap::enableAnitiAliasForEachLayer()
{
	Vector<Node*> pChildrenArray = this->getChildren();
	SpriteBatchNode* child = NULL;
	Object* pObject = NULL;
	//����Tilemap������ͼ��
	for(auto pChildren:pChildrenArray)
	{
		child = (SpriteBatchNode*)pObject;
		if(!child)
			break;
		//��ͼ��������������
		child->getTexture()->setAntiAliasTexParameters();
	}
}

//��cocos2d-x����ת��ΪTilemap����
Point GameMap::tileCoordForPosition(Point position)
{
	int x = position.x / this->getTileSize().width;
	int y = (((this->getMapSize().height) * this->getTileSize().height) - position.y) / this->getTileSize().height;
	return Point(x, y);
}

//��Tilemap����ת��Ϊcocos2d-x����
Point GameMap::positionForTileCoord(Point tileCoord)
{
	Point pos =  ccp((tileCoord.x * this->getTileSize().width),
		((this->getMapSize().height - tileCoord.y) * this->getTileSize().height));
	return pos;
}
//���صذ��
TMXLayer* GameMap::getPlatformLayer()
{
	return platformLayer;
}
TMXLayer* GameMap::getPlatformDynamicLayer()
{
	return platformDynamicLayer;
}
TMXLayer* GameMap::getHideBlockLayer()
{
	return hideBlockLayer;
}
TMXLayer* GameMap::getBiqiLayer()
{
	return biqiLayer;
}
void GameMap::hideBlockAnimate(CCPoint target)
{
	
	target=positionForTileCoord(target);
	target=ccp(target.x,target.y-24);
	hideBlock=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(whyBlockKey));
	hideBlock->setAnchorPoint(ccp(0,0));
	hideBlock->setPosition(target);
	//sGlobal->game_1_1->addChild(hideBlock );
	switch(sGlobal->now_stage)
	{
	case 2:
		sGlobal->game_1_1->addChild(hideBlock );
		break;
	case 3:
		sGlobal->game_2_1->addChild(hideBlock );
		break;
	case 4:
		sGlobal->game_3_1->addChild(hideBlock );
		break;
	case 5:
		sGlobal->game_4_1->addChild(hideBlock );
		break;
	default:
		break;
	}
	//TODO

	
	PointArray* array=PointArray::create(2);
	array->addControlPoint(ccp(target.x,target.y+10));
	array->addControlPoint(target);
	CardinalSplineTo *cardinal=CardinalSplineTo::create(0.4f,array,0);
	//CCFiniteTimeAction* action=cardinal->release();
	FiniteTimeAction* actionMoveDone=CallFuncN::create(this,callfuncN_selector(GameMap::blockMoveFinished));
	
	hideBlock->runAction(Sequence::create(cardinal,actionMoveDone,NULL));
	goldSprite=Sprite::createWithSpriteFrame(sAnimationMgr->getSpritFrame(goldCoinkey));
	goldSprite->setAnchorPoint(Point::ZERO);
    goldSprite->setPosition(target.x+10,target.y+48);
    FiniteTimeAction *actionMove=MoveBy::create(0.9f,Point(0,60));

	FiniteTimeAction* goldMoveDone=CallFuncN::create(this,callfuncN_selector(GameMap::removeGold));

	//sGlobal->game_1_1->addChild(goldSprite );
	switch(sGlobal->now_stage)
	{
	case 2:
		sGlobal->game_1_1->addChild(goldSprite );
		break;
	case 3:
		sGlobal->game_2_1->addChild(goldSprite );
		break;
	case 4:
		sGlobal->game_3_1->addChild(goldSprite );
		break;
	case 5:
		sGlobal->game_4_1->addChild(goldSprite );
		break;
	default:
		break;
	}
	//TODO
	goldSprite->runAction(Sequence::create(actionMove,goldMoveDone,NULL));

}
void GameMap::blockMoveFinished(Node *sender)
{

	hideBlock->setDisplayFrame(sAnimationMgr->getSpritFrame(firmBlockKey));
}

void GameMap::removeGold(CCNode *sender)
{
	FadeOut* fadeout=FadeOut::create(0.8f);
	goldSprite->runAction(fadeout);
}