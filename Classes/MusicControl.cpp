#include "MusicControl.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;

using namespace CocosDenshion;

MusicControl * MusicControl::getInstance() {
	static MusicControl _MusicControl;
	return &_MusicControl;
}

void MusicControl::playSE(char * path) {
	if (MusicControl::isSEPlay()) SimpleAudioEngine::getInstance()->playEffect(path);
}

void MusicControl::playBGM(char * path) {
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	    SimpleAudioEngine::getInstance()->playBackgroundMusic(path, true);
	if (!MusicControl::isBGMPlay()) MusicControl::stopBGM();
}

void MusicControl::stopBGM() {
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void MusicControl::resumeBGM() {
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

bool MusicControl::isSEPlay() {
	return UserDefault::getInstance()->getBoolForKey("isSEPlay", true);
}

bool MusicControl::isBGMPlay() {
	return UserDefault::getInstance()->getBoolForKey("isBGMPlay", true);
}

void MusicControl::turnSEPlay() {
	UserDefault::getInstance()->setBoolForKey("isSEPlay", !MusicControl::isSEPlay());
}

void MusicControl::turnBGMPlay() {
	UserDefault::getInstance()->setBoolForKey("isBGMPlay", !MusicControl::isBGMPlay());
	if (MusicControl::isBGMPlay()) MusicControl::resumeBGM();
	else MusicControl::stopBGM();
}

void MusicControl::preloadSE(char * path) {
	SimpleAudioEngine::getInstance()->preloadEffect(path);
}