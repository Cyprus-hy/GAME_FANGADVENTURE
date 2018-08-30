#pragma once
#include "BZDMX.h"
class HideScene : public cocos2d::CCLayer
{
public:
	HideScene(void);
	~HideScene(void);
	static cocos2d::Scene* scene();
	virtual bool init();  
	CREATE_FUNC(HideScene);
};

