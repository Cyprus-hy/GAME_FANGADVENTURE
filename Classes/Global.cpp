#include "Global.h"
DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{
	isEffectOn=true;
	isMusicOn=true;
	gameStage=1;
	now_stage=1;
	IQ=250;
	stage = 1;
}


Global::~Global(void)
{
	game_1_1=NULL;
	gameMap=NULL;
}
