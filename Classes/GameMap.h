#pragma once
#include "BZDMX.h"
class GameMap : public cocos2d::CCTMXTiledMap
{
public:
	GameMap(void);
	~GameMap(void);
	/*CC_PROPERTY_READONLY(TMXLayer*, platformLayer, PlatformLayer);
	//TMXLayer* getPlatformLayer();
	CC_PROPERTY_READONLY(TMXLayer*, hideBlockLayer, HideBlockLayer);
	CC_PROPERTY_READONLY(TMXLayer*, platformDynamicLayer,PlatformDynamicLayer);
	CC_PROPERTY_READONLY(TMXLayer*, biqiLayer,BiqiLayer);*/

	TMXLayer* getPlatformLayer();
	TMXLayer* getPlatformDynamicLayer();
	TMXLayer* getHideBlockLayer();
	TMXLayer* getBiqiLayer();
	// 声明一个成员变量以及get##funName函数，没有set函数。get##funName函数只有声明，而没有定义。代码如下:
	//静态方法，用于生成GameMap实例
	static GameMap* gameMapWithTMXFile(const char *tmxFile);
	//TiledMap和cocos2d-x坐标系相互转换的方法
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	void hideBlockAnimate(Point target);
	void blockMoveFinished(Node *sender);
	void removeGold(Node *sender);
	//动画移除砖块
	void removeFloor(Point point);
protected:
	//TiledMap额外的初始化方法
	void extraInit();
	//开启各图层的纹理抗锯齿
	void enableAnitiAliasForEachLayer();
	TMXLayer* platformLayer;
	TMXLayer* hideBlockLayer;
	TMXLayer* platformDynamicLayer;
	TMXLayer* biqiLayer;
};

