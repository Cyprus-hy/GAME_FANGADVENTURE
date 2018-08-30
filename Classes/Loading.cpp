#include "Loading.h"

Loading::Loading()
{

}

Loading::~Loading()
{

}

Scene* Loading::scene()
{
	Scene * scene = NULL;
	do 
	{
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		Loading *layer = Loading::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
	return scene;
}

bool Loading::init()
{
	Size size = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading.plist");

	//------返回按钮------
	MenuItemImage *backItem = MenuItemImage::create(
	"back_but1.png",
	"back_but2.png",
	this,
	menu_selector(Loading::backItemCallback));
	if(! backItem )
		return false;

	// Place the menu item bottom-right conner.
	backItem ->setPosition(70,size.height-30);
	Menu* backItemMenu = Menu::create(backItem , NULL);
	backItemMenu->setPosition(Point::ZERO);
	addChild(backItemMenu,1);

	//------背景图片------
	Sprite* bgSprite=Sprite::create("loadingBackground.png");
	bgSprite->setPosition(size.width / 2, size.height/2);
	this->addChild(bgSprite,0);

	//------加入骑车加载动画------
	auto load=Sprite::createWithSpriteFrameName("loading1.png");
	load->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	load->setPosition(size.width/2,size.height/3);
	this->addChild(load);

	//------骑车加载动画执行后跳转场景------
	auto animation = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		auto png = StringUtils::format("loading%d.png", i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(9);
	auto animate = Animate::create(animation);
	auto callFunc = CallFunc::create([](){
		//------跳转到游戏场景------
		Director::getInstance()->popScene();
		Director::getInstance()->popScene();
		Director::getInstance()->popScene();
		Director::getInstance()->popScene();
		Director::getInstance()->pushScene(GameMenu::scene());
		Director::getInstance()->pushScene(StageSelect::scene());
	});
	load->runAction(Sequence::create(animate,callFunc,NULL));

	return true;
}

void Loading::backItemCallback(Ref*)
{
	Director::getInstance()->popScene();
}