#include "OptionScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h" //ÒôÀÖ¿ØÖÆ

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace CocosDenshion;

Scene* OptionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto optionScene = CSLoader::createNode("OptionScene.csb");

	addChild(optionScene);

	InitBtn();

    return true;
}


void OptionScene::InitBtn() {
	auto btnBGM = Sprite::create("UIImage/btn_BGM.png");
	btnBGM->setPosition(Vec2(500, 540));
	btnBGM->setScaleX(1.2);
	btnBGM->setName("btnBGM");
	auto btnSE = Sprite::create("UIImage/btn_SE.png");
	btnSE->setPosition(Vec2(500, 465));
	btnSE->setName("btnSE");
	auto btnBack = Sprite::create("UIImage/btn_back.png");
	btnBack->setPosition(Vec2(500, 390));
	btnBack->setName("btnBack");
	addChild(btnBGM);
	addChild(btnSE);
	addChild(btnBack);


	auto checkBGM = Sprite::create("UIImage/checkbox.png");
	checkBGM->setPosition(750,530);
	checkBGM->setAnchorPoint(Vec2(0, 0));
	checkBGM->setName("checkBGM");

	if (UserDefault::getInstance()->getBoolForKey("isBGMPlay")) checkBGM->setTexture("UIImage/checkbox_select.png");

	addChild(checkBGM);

	auto checkSE = Sprite::create("UIImage/checkbox.png");
	checkSE->setPosition(750, 455);
	checkSE->setAnchorPoint(Vec2(0, 0));
	checkSE->setName("checkSE");

	if (UserDefault::getInstance()->getBoolForKey("isSEPlay")) checkSE->setTexture("UIImage/checkbox_select.png");

	addChild(checkSE);

}