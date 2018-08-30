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
	// ����һ����Ա�����Լ�get##funName������û��set������get##funName����ֻ����������û�ж��塣��������:
	//��̬��������������GameMapʵ��
	static GameMap* gameMapWithTMXFile(const char *tmxFile);
	//TiledMap��cocos2d-x����ϵ�໥ת���ķ���
	Point tileCoordForPosition(Point position);
	Point positionForTileCoord(Point tileCoord);
	void hideBlockAnimate(Point target);
	void blockMoveFinished(Node *sender);
	void removeGold(Node *sender);
	//�����Ƴ�ש��
	void removeFloor(Point point);
protected:
	//TiledMap����ĳ�ʼ������
	void extraInit();
	//������ͼ����������
	void enableAnitiAliasForEachLayer();
	TMXLayer* platformLayer;
	TMXLayer* hideBlockLayer;
	TMXLayer* platformDynamicLayer;
	TMXLayer* biqiLayer;
};

