#pragma once
#include "BZDMX.h"
class AnimationManager : public Singleton<AnimationManager>
{
public:
	AnimationManager(void);
	~AnimationManager(void);
	//��ʼ������ģ�滺���
	bool initAnimationMap();
	//�������ֵõ�һ������ģ��
	Animation* getAnimation(int key);
	//����һ������ʵ��
	Animate* createAnimate(int key);
	//����һ������ʵ��
	Animate* createAnimate(const char* key);
	SpriteFrame * getSpritFrame(int key);
	
protected:
	//������ʿ���߶���ģ��
	Animation* createHeroMovingAnimationByDirection(HeroDirection direction);
	Animation* createCryAnimation();
	Animation* createVictoryAnimation();
	Animation* createBiqiSmile();
};

//���嶯��������ʵ���ı���
#define sAnimationMgr AnimationManager::instance()
