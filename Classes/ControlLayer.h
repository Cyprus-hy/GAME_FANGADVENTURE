#pragma once
#include "BZDMX.h"
class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);
		virtual bool init();

		CREATE_FUNC(ControlLayer);
		void  update(float delta);
		int failedLayerInitTimes;
	   int 	winLayerInitTimes;
};

