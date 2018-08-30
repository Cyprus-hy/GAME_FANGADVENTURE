#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "BZDMX.h"
class Game_2_1  : public cocos2d::Layer
{
public:
	Game_2_1(void);
	~Game_2_1(void);
 // static	CCSprite *hero;
	typedef enum{
		die=0,
		normal=1,
		left=3,
		kright=4,
	} State;
	static cocos2d::Scene* scene();
	virtual bool init();  
	CREATE_FUNC(Game_2_1);
	void update(float dt);
	void backItemCallback(Object* pSender);
	Animation* createAnimationByState(State direction);
	//void  ccTouchesBegan (cocos2d::Set *pTouches, cocos2d::Event *pEvent);
	//��ʼ����
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	//void  ccTouchesEnded (cocos2d::Set *pTouches, cocos2d::Event *pEvent); 
	//��������
	void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	bool haveTouchBiqi;
	void runggcmove();
	MenuItemImage *backItem;
};

