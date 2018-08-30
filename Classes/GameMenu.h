#pragma once
#include "cocos2d.h"
#include "PhotoSelect.h"
#include "Box2D/Box2D.h"
#include "StageSelect.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class GameMenu : public cocos2d::Layer
{
public:
	GameMenu(void);
	~GameMenu(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* scene();
	void startButtonCallback(Ref*);
    void 	aboutItemCallback(Ref*);
    void 	optionItemCallback(Ref*);
	// a selector callback
	void menuCloseCallback(Ref*);

	// implement the "static node()" method manually
	CREATE_FUNC(GameMenu);
};

