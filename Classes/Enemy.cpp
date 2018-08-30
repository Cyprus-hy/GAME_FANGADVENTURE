#include "Enemy.h"
#include "SimpleAudioEngine.h"

bool Enemy::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LastPass.plist");
	auto animation1 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//ƴ���ַ������μ�C�е�printf����
		auto png = StringUtils::format("little_down%d.png", i);
		//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation1->addSpriteFrame(spriteFrame);
	}
	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
	animation1->setDelayPerUnit(0.2f);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation1, "SmallEnemyDown");


	auto animation2 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//ƴ���ַ������μ�C�е�printf����
		auto png = StringUtils::format("middle_down%d.png", i);
		//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation2->addSpriteFrame(spriteFrame);
	}
	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
	animation2->setDelayPerUnit(0.2f);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation2, "MiddleEnemyDown");

	
	
	auto animation3 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//ƴ���ַ������μ�C�е�printf����
		auto png = StringUtils::format("boss_down%d.png", i);
		//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation3->addSpriteFrame(spriteFrame);
	}
	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
	animation3->setDelayPerUnit(0.2f);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(animation3, "BigEnemyDown");



	//hit
	auto hit2= Animation::create();

	//ƴ���ַ������μ�C�е�printf����
	//auto png1 = ;
	//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("middle_hurt.png");
	hit2->addSpriteFrame(spriteFrame);

	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
	hit2->setDelayPerUnit(0.2f);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(hit2, "MiddleEnemyhit");

	
	auto hit3= Animation::create();

	//ƴ���ַ������μ�C�е�printf����;
	//���ݾ���֡���ƴӾ���֡�����л�ȡ����֡
	hit3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_hurt.png"));

	//Ĭ�϶���ִֻ��һ�Σ���������ȱʡ
	hit3->setDelayPerUnit(0.2f);
	//��Ϊ��������ִ�У��������ڶ��������л�������
	AnimationCache::getInstance()->addAnimation(hit3, "BigEnemyhit");


	
	
	switch (type)
	{
	case 1://small
		{
			blood=1;
			//���õ���init������create
			Sprite::initWithSpriteFrameName("little1.png");
			break;
		}
	case 2://middle
		{
			blood=5;
			//���õ���init������create
			Sprite::initWithSpriteFrameName("middle1.png");
			break;
		}
	case 3://big
		{
			blood=10000000;
			//���õ���init������create
			Sprite::initWithSpriteFrameName("boss1.png");
			//��ɻ��ķ��ж���
			auto flyAnim = Animation::create();
			flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss1.png"));			
			flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss2.png"));
			flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss3.png"));
			flyAnim->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss4.png"));
			flyAnim->setDelayPerUnit(0.2f);
			flyAnim->setLoops(-1);
			this->runAction(Animate::create(flyAnim));	
			break;
		}
	default:
		break;
	}


	
	

	
	
	
	
	
	
	
	
	
	
	
	return true;
}

//�л�������ʱ���õĺ�������Ҫ������ִ�б�ը�����ʹӸ�Ԫ�����Ƴ��Լ������ٻ��ƣ�
void Enemy::down(int type) {
	stopAllActions();
	switch (type)
	{
	case 1://small
	{	//���õ���init������create
		//SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
		Score=1;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy1_down.wav");
		auto animation1 = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
		auto animate1 = Animate::create(animation1);
		//CallFuncN���������ڶ��������в�����룬����N����ִ�����������Ԫ������
		auto callFunc = CallFuncN::create([](Node *node){
		//���Լ��Ӹ��������Ƴ�
		node->removeFromParentAndCleanup(true);
		});
		//Sequen��֤�˶���ִ�е��Ⱥ�˳��ĩβ��NULL��ʾ�������е���ֹ������ʡ��
		this->runAction(Sequence::create(animate1, callFunc, NULL));
		break;
	}
	case 2://Middle
	{	//���õ���init������create
		//SimpleAudioEngine::getInstance()->playEffect("enemy2_down.wav");
		Score=2;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy2_down.wav");
		auto animation2 = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
		auto animate2 = Animate::create(animation2);
		//CallFuncN���������ڶ��������в�����룬����N����ִ�����������Ԫ������
		auto callFunc = CallFuncN::create([](Node *node){
		//���Լ��Ӹ��������Ƴ�
		node->removeFromParentAndCleanup(true);
		});
		//Sequen��֤�˶���ִ�е��Ⱥ�˳��ĩβ��NULL��ʾ�������е���ֹ������ʡ��
		this->runAction(Sequence::create(animate2, callFunc, NULL));
		break;
	}

	case 3://small
	{	//���õ���init������create
		//SimpleAudioEngine::getInstance()->playEffect("enemy3_down.wav");
		Score=3;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy3_down.wav");
		auto animation3 = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
		auto animate3 = Animate::create(animation3);
		//CallFuncN���������ڶ��������в�����룬����N����ִ�����������Ԫ������
		auto callFunc = CallFuncN::create([](Node *node){
		//���Լ��Ӹ��������Ƴ�
		node->removeFromParentAndCleanup(true);
		});
		//Sequen��֤�˶���ִ�е��Ⱥ�˳��ĩβ��NULL��ʾ�������е���ֹ������ʡ��
		this->runAction(Sequence::create(animate3, callFunc, NULL));
		break;
	}

	default:
		break;
	}
	
}

Enemy* Enemy::create(int type)
{
	//type = mtype;
	auto pp=new Enemy();//�����任
	if(pp && pp->init())
	{
		pp->autorelease();
		return pp;

	}
	else {
		delete pp;
		pp = NULL;
		return NULL;
	}

}



void Enemy::hit()
{
	if(type==2)
	{
		auto hit2 = Animate::create(AnimationCache::getInstance()->getAnimation("MiddleEnemyhit"));
		//CallFuncN���������ڶ��������в�����룬����N����ִ�����������Ԫ������
		auto callFunc = CallFuncN::create([](Node *node){
		//���Լ��Ӹ��������Ƴ�
		//node->removeFromParentAndCleanup(true);
		});
		//Sequen��֤�˶���ִ�е��Ⱥ�˳��ĩβ��NULL��ʾ�������е���ֹ������ʡ��
		this->runAction(Sequence::create(hit2, callFunc, NULL));
	}

	if(type==3)
	{
		auto hit3= Animate::create(AnimationCache::getInstance()->getAnimation("BigEnemyhit"));
		//CallFuncN���������ڶ��������в�����룬����N����ִ�����������Ԫ������
		auto callFunc = CallFuncN::create([](Node *node){
		//���Լ��Ӹ��������Ƴ�
		//node->removeFromParentAndCleanup(true);
		});
		//Sequen��֤�˶���ִ�е��Ⱥ�˳��ĩβ��NULL��ʾ�������е���ֹ������ʡ��
		this->runAction(Sequence::create(hit3, callFunc, NULL));
	}


}


