#ifndef LOADING_H_
#define LOADING_H_

#include "cocos2d.h"
#include "BZDMX.h"

using namespace cocos2d;

class Loading : public Layer
{
public:
	Loading(void);
	~Loading(void);
	static Scene* scene();
	virtual bool init();  
	CREATE_FUNC(Loading);	
	void backItemCallback(Ref*);
};



#endif