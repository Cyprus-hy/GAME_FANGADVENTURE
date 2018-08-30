#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "BZDMX.h"
#include "Singleton.h"

//������Ϸ�Ĺؿ�
#define GAMESTAGE int

class Game_1_1;
class Game_2_1;
class Game_3_1;
class Game_4_1;
//class Game_5_1;
//TODO
class Hero;
class GameMap;
class ControlLayer;
class FailedLayer;
class GameoverScene;
class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);
	Game_1_1 *game_1_1;
	Game_2_1 *game_2_1;
	Game_3_1 *game_3_1;
	Game_4_1 *game_4_1;
//	Game_5_1 *game_5_1;
	GameMap *gameMap;
	Hero *hero;
	ControlLayer *controlLayer;
	FailedLayer *faledLayer;
	GameoverScene *gameoverLayer;
	bool isMusicOn;
	bool isEffectOn;
	int gameStage;
	int IQ;
	GAMESTAGE stage;	//������Ϸͨ���Ĺؿ�
	GAMESTAGE now_stage;
};
#define sGlobal Global::instance()

#endif
