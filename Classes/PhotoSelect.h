#ifndef PHOTOSELECT_H_
#define PHOTOSELECT_H_

#include "cocos2d.h"
#include "BZDMX.h"

using namespace cocos2d;

class PhotoSelect : public Layer
{
public:
	PhotoSelect(void);
	~PhotoSelect(void);
	static Scene* scene();
	virtual bool init();  
	CREATE_FUNC(PhotoSelect);
	void backItemCallback(Ref*);
	void TouchTrue(Ref*);
	void TouchFalse(Ref*);
};

#endif