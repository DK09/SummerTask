#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameScene : public cocos2d::Layer
{
	static GameScene * _GameScene;

	cocos2d::Vector<cocos2d::Sprite *> life_v;
	cocos2d::Vector<cocos2d::Sprite *> bomb_v;

	cocos2d::ui::Text* powerText;

	int  bomb, bombs;

public:
	int life, power, noMissTime;
	float missPrecent, attack;
	long score;
  
public:  
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	static GameScene * getInstance();
	
	void InitAllParament();

	void LifeChange(int change);

	void BombChange(int change);

	void ReturnTitle();

	void PowerChange(int change);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
