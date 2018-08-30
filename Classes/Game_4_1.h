#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "BZDMX.h"
class Game_4_1  : public cocos2d::Layer
{
public:
	Game_4_1(void);
	~Game_4_1(void);
 // static	CCSprite *hero;
	typedef enum{
		die=0,
		normal=1,
		left=3,
		kright=4,
	} State;
	static cocos2d::Scene* scene();
	virtual bool init();  
	CREATE_FUNC(Game_4_1);
	void update(float dt);
	void backItemCallback(Object* pSender);
	//¿ªÊ¼´¥Ãþ
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
	//½áÊø´¥Ãþ
	void onTouchesEnded(const std::vector<Touch*>& touches, Event  *event);
	bool haveTouchBiqi;

	bool M_move;
	bool isNPCshowed;
	bool isWordshowed;
	bool isFlee;
	bool isShoot;
	bool animDone;
	bool monsterDone;
	bool monsterRemove;
	
	MenuItemImage *backItem;
};

