#ifndef __MusicControl_H__
#define __MusicControl_H__

#include "cocos2d.h"

class MusicControl {

public:
	
	static MusicControl * getInstance();

	virtual void playSE(char * path);

	virtual void playBGM(char * path);

	virtual void stopBGM();

	virtual void resumeBGM();

	virtual bool isBGMPlay();

	virtual bool isSEPlay();

	virtual void turnBGMPlay();

	virtual void turnSEPlay();

	virtual void preloadSE(char * path);
};

#endif // __MusicControl_SCENE_H__
