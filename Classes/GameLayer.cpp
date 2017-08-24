#include "GameScene.h"
#include "GameLayer.h"
#include "PlaneLayer.h"
#include "HeroControl.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

USING_NS_CC;

#define width 425
#define height 425

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto gameLayer = CSLoader::createNodeWithVisibleSize("GameLayer.csb");
	addChild(gameLayer);

	InitAllParament();

    return true;
}


void GameLayer::InitAllParament() {
	auto heroControl = HeroControl::create();
	heroControl->setAnchorPoint(Vec2(0.5, 0.5));
	heroControl->setPosition(Vec2::ZERO);
	addChild(heroControl);

	auto planeLayer = PlaneLayer::create();
	planeLayer->setAnchorPoint(Vec2(0.5, 0.5));
	planeLayer->setPosition(Vec2::ZERO);
	addChild(planeLayer);
}