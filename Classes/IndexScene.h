#ifndef __IndexScene_H__
#define __IndexScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class IndexScene : public cocos2d::Layer
{
	
	Node * indxScene;
	Node * optionScene;

	cocos2d::Sprite * btnStart, * btnOption, *btnExit;
	cocos2d::Sprite * checkBGM, * checkSE;

	bool isOption, isBGMPlay, isSEPlay;

	//the active btn index
	int activeBtn;

	//a vector to store the btn list
	cocos2d::Vector<cocos2d::Sprite *> sp_v;

public:
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//initialize the btns
	void InitBtn();

	void InitSprites();

	//initialize BGM and SE
	void InitMusic();

	//use up&down arrow to change the active btn
	void ChangeBtn(int direct);

	//the sequence when btn pressed
	void PressBtn();

	//change scene decide on which btn is active
	void ChangeScene();

	//while SE on paly effect
	void PlaySE(char * path);

	//use Z&ESC back to main menu 
	void Back();

    // implement the "static create()" method manually
    CREATE_FUNC(IndexScene);
};

#endif // __IndexScene_SCENE_H__
