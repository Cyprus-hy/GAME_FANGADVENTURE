#include "AnimationManager.h"

DECLARE_SINGLETON_MEMBER(AnimationManager);
AnimationManager::AnimationManager(void)
{
}


AnimationManager::~AnimationManager(void)
{
}
bool AnimationManager::initAnimationMap()
{
	char temp[20];
	
	sprintf(temp, "%d", aRight);
	//加载勇士向右走的动画
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(hright), temp);
	sprintf(temp, "%d", aLeft);
	//加载勇士向左走的动画
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(hleft), temp);
	sprintf(temp, "%d", aDie);
	//加载勇士死亡的动画
	AnimationCache::getInstance()->addAnimation(createHeroMovingAnimationByDirection(hdie), temp);
	 
	sprintf(temp, "%d", heroCry);
	
	AnimationCache::getInstance()->addAnimation(createCryAnimation(), temp);

	sprintf(temp, "%d", victory);

	AnimationCache::getInstance()->addAnimation(createVictoryAnimation(), temp);
	
	sprintf(temp, "%d", biqiSmile);

	AnimationCache::getInstance()->addAnimation(createBiqiSmile(), temp);
	SpriteFrame *heronormal, *heroleftJump, *herorightJump;

	//第二个参数表示显示区域的x, y, width, height，根据direction来确定显示的y坐标

	Texture2D *heroTexture = TextureCache::getInstance()->addImage("Hero_image.png");
	heronormal = SpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(eSize*0, eSize*1, eSize, eSize));
	heroleftJump = SpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(eSize*0, eSize*2, eSize, eSize));
	herorightJump = SpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(eSize*1, eSize*2, eSize, eSize));
	SpriteFrame *controlLeft=SpriteFrame::create("Thumb_dpad_left.png",CCRectMake(0,0,90,90));
	SpriteFrame *controlLeftPressed=SpriteFrame::create("Thumb_dpad_left_pressed.png",CCRectMake(0,0,90,90));
	SpriteFrame *controlRight=SpriteFrame::create("Thumb_dpad_right.png",CCRectMake(0,0,90,90));
	SpriteFrame *controlRightPressed=SpriteFrame::create("Thumb_dpad_right_pressed.png",CCRectMake(0,0,90,90));
	SpriteFrame *controlJump=SpriteFrame::create("Thumb_dpad_jump.png",CCRectMake(0,0,135,90));
	SpriteFrame *controlJumpPressed=SpriteFrame::create("Thumb_dpad_jump_pressed.png",CCRectMake(0,0,135,90));
	sprintf(temp, "%d", heronormalkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(heronormal,temp);
	sprintf(temp, "%d", heroleftJumpkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(heroleftJump,temp);
	sprintf(temp, "%d", herorightJumpkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(herorightJump,temp);
	sprintf(temp, "%d", controlLeftkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlLeft,temp);
	sprintf(temp, "%d", controlLeftPressedkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlLeftPressed,temp);
	sprintf(temp, "%d", controlRightkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlRight,temp);
	sprintf(temp, "%d", controlRightPressedkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlRightPressed,temp);
	sprintf(temp, "%d", controlJumpkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlJump,temp);
	sprintf(temp, "%d", controlJumpPressedkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(controlJumpPressed,temp);
	Texture2D *tileTexture = TextureCache::getInstance()->addImage("Tile_source.png");
	SpriteFrame *whyBlock=SpriteFrame::createWithTexture(tileTexture, cocos2d::CCRectMake(0, 96, 48, 48));
	sprintf(temp, "%d", whyBlockKey);
	SpriteFrameCache::getInstance()->addSpriteFrame(whyBlock,temp);
	SpriteFrame *firmBlock=SpriteFrame::createWithTexture(tileTexture, cocos2d::CCRectMake(240, 0, 48, 48));
	sprintf(temp, "%d", firmBlockKey);
	SpriteFrameCache::getInstance()->addSpriteFrame(firmBlock,temp);
	SpriteFrame *gold=SpriteFrame::create("gold.png",CCRectMake(0,0,48,48));
	sprintf(temp, "%d", goldCoinkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(gold,temp);
	SpriteFrame *box=SpriteFrame::create("Navigator_tv.png",CCRectMake(0,0,527,418));
	sprintf(temp, "%d", failedboxkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(box,temp);

	SpriteFrame *cryFrame=SpriteFrame::create("Navigator_lose_image_1.png",CCRectMake(0,0,179,176));
	sprintf(temp, "%d", cryFramekey);
	SpriteFrameCache::getInstance()->addSpriteFrame(cryFrame,temp);

	SpriteFrame *onFrame=SpriteFrame::create("Switch_on.png",CCRectMake(0,0,130,58));
	sprintf(temp, "%d", onkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(onFrame,temp);
	
	SpriteFrame *offFrame=SpriteFrame::create("Switch_off.png",CCRectMake(0,0,130,58));
	sprintf(temp, "%d", offkey);
	SpriteFrameCache::getInstance()->addSpriteFrame(offFrame,temp);
	return true;
}

SpriteFrame * AnimationManager::getSpritFrame(int key)
{
	char temp[20];
	sprintf(temp, "%d", key);
	return SpriteFrameCache::getInstance()->spriteFrameByName(temp);
}
Animation* AnimationManager::createHeroMovingAnimationByDirection(HeroDirection direction)
{
	Texture2D *heroTexture = TextureCache::getInstance()->addImage("Hero_image.png");
	SpriteFrame *frame0, *frame1;
	//CCArray* animFrames ;
	//第二个参数表示显示区域的x, y, width, height，根据direction来确定显示的y坐标
	
	
	frame0 = SpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(eSize*0, eSize*direction, eSize, eSize));
	frame1 = SpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(eSize*1, eSize*direction, eSize, eSize));

	
	//animFrames = new CCArray(2);
	Vector<SpriteFrame*>animFrames;
	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	
	

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.09f);

	animFrames.clear();
	
	return animation;
}
//获取哭泣动画
Animation* AnimationManager::createCryAnimation()
{
	SpriteFrame *frame0, *frame1, *frame2,*frame3;
	//CCArray* animFrames =CCArray::createWithCapacity(4);
	Vector<SpriteFrame*> animFrames;

	frame0=SpriteFrame::create("Navigator_lose_image_1.png",CCRectMake(0,0,179,176));
	frame1=SpriteFrame::create("Navigator_lose_image_2.png",CCRectMake(0,0,179,176));
	frame2=SpriteFrame::create("Navigator_lose_image_3.png",CCRectMake(0,0,179,176));
	frame3=SpriteFrame::create("Navigator_lose_image.png",CCRectMake(0,0,179,176));
	
	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	animFrames.pushBack(frame3);
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animFrames.clear();
	
	return animation;
}
Animation* AnimationManager::createVictoryAnimation()
{

	SpriteFrame *frame0, *frame1;
	//CCArray* animFrames =CCArray::createWithCapacity(2);
	Vector<SpriteFrame*>animFrames;
	frame0=SpriteFrame::create("Navigator_win_image_2.png",CCRectMake(0,0,179,176));
	frame1=SpriteFrame::create("Navigator_win_image_1.png",CCRectMake(0,0,179,176));


	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animFrames.clear();

	return animation;
}
//获取指定动画模版
Animation* AnimationManager::getAnimation(int key)
{
	char temp[20];
	sprintf(temp, "%d", key);
	return AnimationCache::getInstance()->animationByName(temp);
}

//获取一个指定动画模版的实例
Animate* AnimationManager::createAnimate(int key)
{
	//获取指定动画模版
	Animation* anim = getAnimation(key);
	if(anim)
	{
		//根据动画模版生成一个动画实例
		return Animate::create(anim);
	}
	return NULL;
}

//获取一个指定动画模版的实例
Animate* AnimationManager::createAnimate(const char* key)
{
	//获取指定动画模版
	Animation* anim = AnimationCache::getInstance()->animationByName(key);
	if(anim)
	{
		//根据动画模版生成一个动画实例
		return Animate::create(anim);
	}
	return NULL;
}
Animation* AnimationManager::createBiqiSmile()
{

	SpriteFrame *frame0, *frame1,*frame2;
	Vector<SpriteFrame*> animFrames;
	//CCArray* animFrames =CCArray::createWithCapacity(3);
	frame0=SpriteFrame::create("Startup_herface1.png",CCRectMake(0,0,97,92));
	frame1=SpriteFrame::create("Startup_herface2.png",CCRectMake(0,0,97,92));
    frame2=SpriteFrame::create("Startup_herface3.png",CCRectMake(0,0,97,92));

	animFrames.pushBack(frame0);
	animFrames.pushBack(frame1);
	animFrames.pushBack(frame2);
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.6f);
	animFrames.clear();

	return animation;
}