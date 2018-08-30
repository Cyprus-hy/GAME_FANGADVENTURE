#ifndef ENEMY_H_
#define ENEMY_H_
#include "cocos2d.h"
USING_NS_CC;

class Enemy :public Sprite{
public:
	virtual bool init();
	static Enemy* create(int);//”Œœ∑≥°æ∞
	//void createnew(int);
    
	void down(int);
	void hit();
	
	int type;
	int blood;
	int Score;





};
#endif