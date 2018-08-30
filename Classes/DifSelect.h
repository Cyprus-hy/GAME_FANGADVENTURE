#ifndef DIFSELECT_H_
#define DIFSELECT_H_

#include "cocos2d.h"
#include "BZDMX.h"

using namespace cocos2d;

class DifSelect : public Layer
{
public:
	DifSelect(void);
	~DifSelect(void);
	static Scene* scene();
	virtual bool init();  
	CREATE_FUNC(DifSelect);
	void backItemCallback(Ref*);
	void TouchTrue(Ref*);
	void TouchFalse(Ref*);
};

#endif