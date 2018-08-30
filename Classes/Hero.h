#pragma once
#include "BZDMX.h"
class Hero  : public cocos2d::CCNode
{
public:
	Hero(void);
	~Hero(void);
	//��̬���������ڴ�����ʿʵ��
	static Hero *heroWithinLayer();
	//����ʿ��ָ�������ƶ�һ��
	void move(int i);
	void jump();
	void animateDone(CCNode *sender);
	bool isHeroMoving;
	bool isJumpDone;
	float hspeed;
	float vspeed;
	void setLayerEmpty(CCPoint start,int width,int height);
	bool isanimate;
	MoveDirection dir;//�ж��ƶ�����
	//��ʼ������
	bool heroInit();
	bool isDead;
	bool isWin;
	//CollisionType checkCollision(CCPoint targetosition);
	void setViewpointCenter(Point p);
	CollisionType checkCollisionOnly(Point heroPosition);
	CollisionType checHeadkCollision(Point heroPosition);
private:
	//������ʾ��ʿ����ľ���
	Sprite *heroSprite;
	//��ʱ����Ŀ���Tilemap����
	Point targetTileCoord;
	Point targetPosition;
	float speed;
};

