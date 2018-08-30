#pragma once
#include "BZDMX.h"
class AboutScene : public cocos2d::CCLayer
{
public:
	AboutScene(void);
	~AboutScene(void);
	virtual bool init();  
	static cocos2d::Scene* scene();
	CREATE_FUNC(AboutScene);
	void musicItemCallback(Ref*);
};

