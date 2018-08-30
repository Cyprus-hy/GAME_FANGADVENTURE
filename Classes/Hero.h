#pragma once
#include "BZDMX.h"
class Hero  : public cocos2d::CCNode
{
public:
	Hero(void);
	~Hero(void);
	//静态方法，用于创建勇士实例
	static Hero *heroWithinLayer();
	//让勇士向指定方向移动一格
	void move(int i);
	void jump();
	void animateDone(CCNode *sender);
	bool isHeroMoving;
	bool isJumpDone;
	float hspeed;
	float vspeed;
	void setLayerEmpty(CCPoint start,int width,int height);
	bool isanimate;
	MoveDirection dir;//判断移动方向
	//初始化方法
	bool heroInit();
	bool isDead;
	bool isWin;
	//CollisionType checkCollision(CCPoint targetosition);
	void setViewpointCenter(Point p);
	CollisionType checkCollisionOnly(Point heroPosition);
	CollisionType checHeadkCollision(Point heroPosition);
private:
	//用于显示勇士形象的精灵
	Sprite *heroSprite;
	//临时保存目标的Tilemap坐标
	Point targetTileCoord;
	Point targetPosition;
	float speed;
};

