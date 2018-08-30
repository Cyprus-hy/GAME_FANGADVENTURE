#pragma once
#include "BZDMX.h"
class SettingScene : public Layer
{
public:
	SettingScene(void);
	~SettingScene(void);
	virtual bool init();  
	static cocos2d::Scene* scene();
	CREATE_FUNC(SettingScene);
	bool isMusicSwitchOn;
	bool isEffectSwitchOn;
	void 	musicItemCallback(Ref*);
	void 	effectItemCallback(Ref*);
//	void  onTouchesEnded (const vector<Touch *> &pTouches, Event *pEvent);
};

