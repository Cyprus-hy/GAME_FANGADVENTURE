#include "cocos2d.h"
#include <CCGLView.h>
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BZDMX.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
	sAnimationMgr->release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();//�ҵ���ʦ���ҵ��ɻ�ͼ�Ľӿ�
	if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);//glview���ô��ڴ�С
    }

	glview->setDesignResolutionSize(720, 480, ResolutionPolicy::FIXED_WIDTH);
	//GLView::sharedOpenGLView()->setDesignResolutionSize(800,480,kResolutionExactFit);
	FileUtils::getInstance()->addSearchPath("UI");//����Դ���ui�ļ���
	//FileUtils::getInstance()->addSearchPath("fonts");
	FileUtils::getInstance()->addSearchPath("font");
	FileUtils::getInstance()->addSearchPath("music");
    // turn on display FPS
    director->setDisplayStats(false);
	sAnimationMgr->initAnimationMap();
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    Scene *pScene = HelloWorld::scene();

	// run
	director->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
