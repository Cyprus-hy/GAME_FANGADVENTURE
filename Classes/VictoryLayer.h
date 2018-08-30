#pragma once
#include "BZDMX.h"

using namespace cocos2d;

class VictoryLayer : public Layer
{
public:
	VictoryLayer(void);
	~VictoryLayer(void);
	static Scene *scene();
	virtual bool init();
	CREATE_FUNC(VictoryLayer);
	//void update(float dt);
	void backItemCallback(Ref*);
	void goItemCallback(Ref*);
};

