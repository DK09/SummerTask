#include "GameScene.h"
#include "GameLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

#include "IndexScene.h"

USING_NS_CC;

#define maxCount 8 //the number of life/bomb up limit

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene * GameScene::_GameScene = NULL;

GameScene * GameScene::getInstance() {
	if (_GameScene == NULL) {
		_GameScene = new GameScene();
	}
	return _GameScene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	_GameScene = this;

    auto GameScene = CSLoader::createNode("GameScene.csb");

	addChild(GameScene);

	InitAllParament();

	MusicControl::getInstance()->preloadSE("SoundEffect/extend.wav");
	MusicControl::getInstance()->preloadSE("SoundEffect/miss.wav");

    return true;
}


void GameScene::InitAllParament() {
	//create game layer
	auto gameLayer = GameLayer::create();
	addChild(gameLayer);
	gameLayer->setAnchorPoint(Vec2(0.5, 0.5));
	gameLayer->setPosition(Vec2(450, 450));

	//create game background
	auto bg = Sprite::create("OtherImage/game_bg1.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);

	//set bomb and life
	life = 3;
	bombs = bomb = 3;
	if (UserDefault::getInstance()->getIntegerForKey("coreEquip") == 3) bombs = bomb = 4;
	for (int i = 0; i <= maxCount - 1; i++) {
		auto lifeSprite = Sprite::create();
		if (i < life) lifeSprite->setTexture("OtherImage/count.png");
		lifeSprite->setPosition(Vec2(1050 + i * 30, 625));
		lifeSprite->setScale(2);
		addChild(lifeSprite);
		life_v.pushBack(lifeSprite);

		auto bombSprite = Sprite::create();
		if (i < bomb) bombSprite->setTexture("OtherImage/count.png");
		bombSprite->setPosition(Vec2(1050 + i * 30, 560));
		bombSprite->setScale(2);
		addChild(bombSprite);
		bomb_v.pushBack(bombSprite);
	}

	//设置power栏及初始power值
	powerText = Text::create("0.00", "Arial", 30);
	power = 0;
	powerText->setAnchorPoint(Vec2(0, 0));
	powerText->setPosition(Vec2(1050, 470));
	if (UserDefault::getInstance()->getIntegerForKey("planeIndex") == 3){
		powerText->setText("1.00");
		power = 100;
	}
	addChild(powerText);

	//设置中弹概率
	missPrecent = 1;
	noMissTime = 0;
	if (UserDefault::getInstance()->getIntegerForKey("planeIndex") == 0){
		missPrecent = missPrecent * 0;
	}
	if (UserDefault::getInstance()->getIntegerForKey("coreEquip") == 2){
		missPrecent = missPrecent * 0.8;
	}

	//设置伤害系数
	attack = 1;
	if (UserDefault::getInstance()->getIntegerForKey("planeIndex") == 3){
		missPrecent = missPrecent * 1.5;
	}
	if (UserDefault::getInstance()->getIntegerForKey("coreEquip") == 1){
		missPrecent = missPrecent * 1.3;
	}
}

void GameScene::LifeChange(int change) {
	if (life + change > 8) return;
	if (life + change < 0) {
		ReturnTitle();
		return;
	}
	if (change < 0) {
		MusicControl::getInstance()->playSE("SoundEffect/miss.wav");
		life_v.at(life - 1)->setTexture("");
		//miss后bomb数还原
		for (int i = 0; i <= maxCount - 1; i++) {
			bomb = bombs;
			if (i < bomb) bomb_v.at(i)->setTexture("OtherImage/count.png");
			else bomb_v.at(i)->setTexture("");
		}
		//miss后power归零，特殊机体变为1.00
		PowerChange(-power);
		if (UserDefault::getInstance()->getIntegerForKey("planeIndex") == 3){
			PowerChange(100);
		}
	}
	else {
		//获得残机后extend音效及图片效果
		MusicControl::getInstance()->playSE("SoundEffect/extend.wav");
		life_v.at(life)->setTexture("OtherImage/count.png");
	}
	life += change;
}

void GameScene::BombChange(int change) {
	//获得或使用bomb
	if (bomb + change > 8 || bomb + change < 0) return;
	if (change < 0) {
		bomb_v.at(bomb - 1)->setTexture("");
	}
	else {
		bomb_v.at(bomb)->setTexture("OtherImage/count.png");
		MusicControl::getInstance()->playSE("SoundEffect/bombget.wav");
	}
	bomb += change;
}

void GameScene::ReturnTitle() {
	this->removeFromParentAndCleanup(this);
	Director::getInstance()->replaceScene(IndexScene::createScene());
}

void GameScene::PowerChange(int change) {
	//power值的改变
	power += change;
	if (power >= 400) {
		power = 400;
		//FullPowerMode();
	}
	std::string text = StringUtils::format("%d.%d%d", power/100, power%100/10, power%10);
	powerText->setText(text);
}

