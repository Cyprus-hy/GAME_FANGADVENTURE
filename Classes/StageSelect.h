#pragma once
#include "cocos2d.h"
#include "Game_1_1.h"
#include "PhotoSelect.h"
#include "DifSelect.h"

USING_NS_CC;
class StageSelect : public cocos2d::CCLayer
{
public:
	StageSelect(void);
	~StageSelect(void);
	static cocos2d::Scene* scene();
	virtual bool init();  
	CREATE_FUNC(StageSelect);
	void backItemCallback(Ref*);
	//void stageOneItemCallback(Ref*);

	void createStageBtn(int, Menu*);
};

