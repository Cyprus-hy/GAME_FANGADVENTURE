#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "BZDMX.h"

using namespace cocos2d;

class GameoverScene:public Layer
{
public:
	GameoverScene(void);
	~GameoverScene(void);
	static Scene *scene(int);
	static GameoverScene* create(int);
	virtual bool init(int);
	//CREATE_FUNC(GameoverScene);
	void backItemCallback(Ref*);
	void turntoTipScene(Ref *);
private:
	int type;

};



#endif