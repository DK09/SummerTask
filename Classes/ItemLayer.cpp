#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"
#include "GameScene.h"
#include "ItemLayer.h"
#include "HeroControl.h"
#include "GameLayer.h"

USING_NS_CC;

#define width 425
#define height 425

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* ItemLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ItemLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ItemLayer::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto ItemLayer = CSLoader::createNodeWithVisibleSize("ItemLayer.csb");
	addChild(ItemLayer);


    return true;
}