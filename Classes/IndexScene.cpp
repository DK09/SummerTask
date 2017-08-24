#include "IndexScene.h"
#include "OptionScene.h"
#include "SelectScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"

USING_NS_CC;

#define BGM "BGM/BGM0.mp3"
#define ButtonSE "SoundEffect/changeButton.mp3"

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* IndexScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IndexScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IndexScene::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    indxScene = CSLoader::createNode("IndexScene.csb");

	addChild(indxScene);

	InitBtn();

	InitSprites();

	InitMusic();

	//create a keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event * event){
		if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) ChangeBtn(2);
		if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) ChangeBtn(1);
		if (key == EventKeyboard::KeyCode::KEY_Z || key == EventKeyboard::KeyCode::KEY_ENTER) PressBtn();
		if (key == EventKeyboard::KeyCode::KEY_X || key == EventKeyboard::KeyCode::KEY_ESCAPE) Back();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void IndexScene::InitBtn() {
	btnStart = Sprite::create("UIImage/btn_start.png");
	btnStart->setPosition(Vec2(1120, 380));
	btnOption = Sprite::create("UIImage/btn_option.png");
	btnOption->setPosition(Vec2(1170, 235));
	btnExit = Sprite::create("UIImage/btn_exit.png");
	btnExit->setPosition(Vec2(1090, 90));
	addChild(btnStart);
	addChild(btnOption);
	addChild(btnExit);
	sp_v.pushBack(btnStart);
	sp_v.pushBack(btnOption);
	sp_v.pushBack(btnExit);

	activeBtn = 0;

	isOption = false;
}

void IndexScene::InitSprites() {
	auto logo = Sprite::create("UIImage/logo.png");
	logo->setPosition(Vec2(450, 1200));
	addChild(logo);
	auto moveTo = MoveTo::create(0.4, Vec2(450, 650));
	logo->runAction(moveTo);
}

void IndexScene::InitMusic() {
	MusicControl::getInstance()->playBGM(BGM);
	MusicControl::getInstance()->preloadSE(ButtonSE);
}



void IndexScene::ChangeBtn(int direct) {
	if (isOption) {
        auto moveUp = ScaleTo::create(0.2, 1);
		sp_v.at(activeBtn)->runAction(moveUp);

		activeBtn = (activeBtn + direct) % 3 + 3;
		
		auto moveDown = ScaleTo::create(0.2, 1.2);
		sp_v.at(activeBtn)->runAction(moveDown);
	}
	else {
		auto moveIn = MoveTo::create(0.2, sp_v.at(activeBtn)->getPosition() + Vec2(130, 0));
		sp_v.at(activeBtn)->runAction(moveIn);

		activeBtn = (activeBtn + direct) % 3;

		auto moveOut = MoveTo::create(0.2, sp_v.at(activeBtn)->getPosition() - Vec2(130, 0));
		sp_v.at(activeBtn)->runAction(moveOut);
	}
	MusicControl::getInstance()->playSE(ButtonSE);
}

void IndexScene::PressBtn() {
	
	MusicControl::getInstance()->playSE(ButtonSE);

	auto moveUp = MoveTo::create(0.05, sp_v.at(activeBtn)->getPosition() + Vec2(0, 10));
	auto moveDown = MoveTo::create(0.05, sp_v.at(activeBtn)->getPosition());
	auto seq = Sequence::create(moveUp, moveDown, CallFuncN::create(CC_CALLBACK_0(IndexScene::ChangeScene, this)), nullptr);
	sp_v.at(activeBtn)->runAction(seq);

}

void IndexScene::ChangeScene() {
	switch (activeBtn) {
	case 0:
		Director::getInstance()->replaceScene(SelectScene::createScene());
		break;
	case 1:
		optionScene = OptionScene::create();
		addChild(optionScene);

		sp_v.pushBack(static_cast<Sprite *>(optionScene->getChildByName("btnBGM")));
		sp_v.pushBack(static_cast<Sprite *>(optionScene->getChildByName("btnSE")));
		sp_v.pushBack(static_cast<Sprite *>(optionScene->getChildByName("btnBack")));

		checkBGM = static_cast<Sprite *>(optionScene->getChildByName("checkBGM"));
		checkSE = static_cast<Sprite *>(optionScene->getChildByName("checkSE"));

		isOption = true;
		activeBtn = 3;
		break;
	case 2:
		sp_v.clear();
		Director::getInstance()->end();
		break;
	case 3:
		if (MusicControl::getInstance()->isBGMPlay()) 
			checkBGM->setTexture("UIImage/checkbox.png");
		else 
			checkBGM->setTexture("UIImage/checkbox_select.png");
		MusicControl::getInstance()->turnBGMPlay();
		break;
	case 4:
		if (MusicControl::getInstance()->isSEPlay()) 
			checkSE->setTexture("UIImage/checkbox.png");	
		else 
			checkSE->setTexture("UIImage/checkbox_select.png");
		MusicControl::getInstance()->turnSEPlay();
		break;
	case 5:
		sp_v.popBack();
		sp_v.popBack();
		sp_v.popBack();
		optionScene->removeFromParentAndCleanup(optionScene);

		isOption = false;
		activeBtn = 1;
		
		break;
	default:
		break;
	}
}

void IndexScene::Back() {
	if (activeBtn > 2) {
		activeBtn = 5;
		MusicControl::getInstance()->playSE(ButtonSE);
		ChangeScene();
	}
	else {
		ChangeBtn(2 - activeBtn);
	}
}