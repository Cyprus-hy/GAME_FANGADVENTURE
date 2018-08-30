#include "Enemy.h"
#include "SimpleAudioEngine.h"

bool Enemy::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LastPass.plist");
	auto animation1 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//拼接字符串，参见C中的printf函数
		auto png = StringUtils::format("little_down%d.png", i);
		//根据精灵帧名称从精灵帧缓存中获取精灵帧
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation1->addSpriteFrame(spriteFrame);
	}
	//默认动画只执行一次，所以这里缺省
	animation1->setDelayPerUnit(0.2f);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(animation1, "SmallEnemyDown");


	auto animation2 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//拼接字符串，参见C中的printf函数
		auto png = StringUtils::format("middle_down%d.png", i);
		//根据精灵帧名称从精灵帧缓存中获取精灵帧
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation2->addSpriteFrame(spriteFrame);
	}
	//默认动画只执行一次，所以这里缺省
	animation2->setDelayPerUnit(0.2f);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(animation2, "MiddleEnemyDown");

	
	
	auto animation3 = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		//拼接字符串，参见C中的printf函数
		auto png = StringUtils::format("boss_down%d.png", i);
		//根据精灵帧名称从精灵帧缓存中获取精灵帧
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
		animation3->addSpriteFrame(spriteFrame);
	}
	//默认动画只执行一次，所以这里缺省
	animation3->setDelayPerUnit(0.2f);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(animation3, "BigEnemyDown");



	//hit
	auto hit2= Animation::create();

	//拼接字符串，参见C中的printf函数
	//auto png1 = ;
	//根据精灵帧名称从精灵帧缓存中获取精灵帧
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("middle_hurt.png");
	hit2->addSpriteFrame(spriteFrame);

	//默认动画只执行一次，所以这里缺省
	hit2->setDelayPerUnit(0.2f);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(hit2, "MiddleEnemyhit");

	
	auto hit3= Animation::create();

	//拼接字符串，参见C中的printf函数;
	//根据精灵帧名称从精灵帧缓存中获取精灵帧
	hit3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_hurt.png"));

	//默认动画只执行一次，所以这里缺省
	hit3->setDelayPerUnit(0.2f);
	//因为不会立即执行，所以先在动画缓存中缓存起来
	AnimationCache::getInstance()->addAnimation(hit3, "BigEnemyhit");


	
	
	switch (type)
	{
	case 1://small
		{
			blood=1;
			//调用的事init而不是create
			Sprite::initWithSpriteFrameName("little1.png");
			break;
		}
	case 2://middle
		{
			blood=5;
			//调用的事init而不是create
			Sprite::initWithSpriteFrameName("middle1.png");
			break;
		}
	case 3://big
		{
			blood=10000000;
			//调用的事init而不是create
			Sprite::initWithSpriteFrameName("boss1.png");
			//大飞机的飞行动画
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

//敌机被击中时调用的函数，主要功能是执行爆炸动画和从父元素中移除自己（不再绘制）
void Enemy::down(int type) {
	stopAllActions();
	switch (type)
	{
	case 1://small
	{	//调用的事init而不是create
		//SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
		Score=1;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy1_down.wav");
		auto animation1 = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
		auto animate1 = Animate::create(animation1);
		//CallFuncN运行我们在动画序列中插入代码，其中N代表执行这个动作的元素自身
		auto callFunc = CallFuncN::create([](Node *node){
		//将自己从父容器中移除
		node->removeFromParentAndCleanup(true);
		});
		//Sequen保证了动画执行的先后顺序，末尾的NULL表示动画序列的终止，不可省略
		this->runAction(Sequence::create(animate1, callFunc, NULL));
		break;
	}
	case 2://Middle
	{	//调用的事init而不是create
		//SimpleAudioEngine::getInstance()->playEffect("enemy2_down.wav");
		Score=2;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy2_down.wav");
		auto animation2 = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
		auto animate2 = Animate::create(animation2);
		//CallFuncN运行我们在动画序列中插入代码，其中N代表执行这个动作的元素自身
		auto callFunc = CallFuncN::create([](Node *node){
		//将自己从父容器中移除
		node->removeFromParentAndCleanup(true);
		});
		//Sequen保证了动画执行的先后顺序，末尾的NULL表示动画序列的终止，不可省略
		this->runAction(Sequence::create(animate2, callFunc, NULL));
		break;
	}

	case 3://small
	{	//调用的事init而不是create
		//SimpleAudioEngine::getInstance()->playEffect("enemy3_down.wav");
		Score=3;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy3_down.wav");
		auto animation3 = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
		auto animate3 = Animate::create(animation3);
		//CallFuncN运行我们在动画序列中插入代码，其中N代表执行这个动作的元素自身
		auto callFunc = CallFuncN::create([](Node *node){
		//将自己从父容器中移除
		node->removeFromParentAndCleanup(true);
		});
		//Sequen保证了动画执行的先后顺序，末尾的NULL表示动画序列的终止，不可省略
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
	auto pp=new Enemy();//场景变换
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
		//CallFuncN运行我们在动画序列中插入代码，其中N代表执行这个动作的元素自身
		auto callFunc = CallFuncN::create([](Node *node){
		//将自己从父容器中移除
		//node->removeFromParentAndCleanup(true);
		});
		//Sequen保证了动画执行的先后顺序，末尾的NULL表示动画序列的终止，不可省略
		this->runAction(Sequence::create(hit2, callFunc, NULL));
	}

	if(type==3)
	{
		auto hit3= Animate::create(AnimationCache::getInstance()->getAnimation("BigEnemyhit"));
		//CallFuncN运行我们在动画序列中插入代码，其中N代表执行这个动作的元素自身
		auto callFunc = CallFuncN::create([](Node *node){
		//将自己从父容器中移除
		//node->removeFromParentAndCleanup(true);
		});
		//Sequen保证了动画执行的先后顺序，末尾的NULL表示动画序列的终止，不可省略
		this->runAction(Sequence::create(hit3, callFunc, NULL));
	}


}


