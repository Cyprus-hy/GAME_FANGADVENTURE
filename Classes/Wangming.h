#ifndef WANGMING_H
#define WANGMING_H
#include "cocos2d.h"
#include "Enemy.h"
#include "FailedLayer.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

class Wangming:public Layer
{
private:
	Point vec;
	Vector<Sprite*> bullets_vec;
	//Vector<Enemy*> enemy_vec;
	Vector<Sprite*> ufo1_vec;
	Vector<Sprite*> ufo2_vec;
	bool doubleBullet;
	bool isPaused;
	int DBulletNum;
	int bombNum;
	int planeScore;
	int Hp;
	int speed;
	bool flag;

public:
    static cocos2d::Scene* createScene();
	void bulletUpdate(float delta);
	void enemy1Create(float delta);
	void enemy2Create(float delta);
	void enemy3Create(float delta);
	void ufo1Create(float delta);
	void ufo2Create(float delta);
	void bombLabelUpdate(float delta);
	void bombNumUpdate(float delta);
	void pauseUpdate(Ref* pSender);
	void bombUpdate(Ref* pSender);
	virtual bool init();  

    CREATE_FUNC(Wangming);
	bool m_left;
	bool m_right;
	bool m_up;
	bool m_down;
	bool m_jump;
	void update(float dt);
	int m_high;
	int m_score;
	int m_boom;
	bool type3;


	void createSmallEnemy(float);
	void createMiddleEnemy(float);
	void createBigEnemy(float);
	void createEnemyByType(int type);
	Vector<Enemy*> m_vEnemys;
	void updateBombLabel() ;
	void musicItemCallback(Ref*);



};
#endif