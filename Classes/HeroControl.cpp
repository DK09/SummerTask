#include "HeroControl.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MusicControl.h"
#include "Bullet.h"
#include "MyPlane.h"

#include "GameScene.h"

USING_NS_CC;

#define s_width 425
#define s_height 425

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* HeroControl::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HeroControl::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HeroControl::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	_HeroControl = this;

	auto heroControl = CSLoader::createNodeWithVisibleSize("GameLayer.csb");
	addChild(heroControl);

	InitAllParament();


	//create a keyboard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event * event){
		MoveDirector(key, 1);
		if (key == EventKeyboard::KeyCode::KEY_Q) { GameScene::getInstance()->PowerChange(100); }
		if (key == EventKeyboard::KeyCode::KEY_E) { GameScene::getInstance()->PowerChange(-100); }
		if (key == EventKeyboard::KeyCode::KEY_R) HeroMiss();
		if (key == EventKeyboard::KeyCode::KEY_W) GameScene::getInstance()->LifeChange(1);
		if (key == EventKeyboard::KeyCode::KEY_X) GameScene::getInstance()->BombChange(-1);
		if (key == EventKeyboard::KeyCode::KEY_V) GameScene::getInstance()->BombChange(1);
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode key, Event * event){
		MoveDirector(key, -1);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(HeroControl::MoveUpdate));
	this->schedule(schedule_selector(HeroControl::BulletUpdate), 0.1f);


    return true;
}

HeroControl * HeroControl::_HeroControl = NULL;

HeroControl * HeroControl::getInstance() {
	if (_HeroControl == NULL) {
		_HeroControl = new HeroControl();
	}
	return _HeroControl;
}

void HeroControl::InitAllParament() {
	std::string name = StringUtils::format("PlaneImage/heroplane_%d.png", UserDefault::getInstance()->getIntegerForKey("planeIndex"));
	hero = MyPlane::createPlane(name);
	hero->type = plane_def;
	switch (UserDefault::getInstance()->getIntegerForKey("planeIndex")) {
	case 0:
		lowSpeed = 4; speed = maxSpeed = 12;
		break;
	case 1:
		lowSpeed = 2; speed = maxSpeed = 8;
		break;
	case 2:
		lowSpeed = 3; speed = maxSpeed = 8;
		break;
	case 3:
		lowSpeed = 3; speed = maxSpeed = 6;
		break;
	defaul:
		break;
		
	}
	director = Vec2(0, 0);
	isShoot = false;
	canMove = true;

	// position the sprite on the center of the screen
	hero->setPosition(Vec2(0, -s_height / 1.2));
	hero->setAnchorPoint(Vec2(0.5, 0.5));
	hero->setScale(0.15);
	planeWidth = hero->getContentSize().width / 3 * hero->getScale();
	planeHeight = hero->getContentSize().height / 3 * hero->getScale();

	// add the sprite as a child to this layer
	addChild(hero, 0);
	
	//add the collision point
	cPoint = MyPlane::createPlane("PlaneImage/collisionpoint.png");
	cPoint->type = plane_main;
	cPoint->setAnchorPoint(Vec2(0.5, 0.5));
	cPoint->setScale(1);
	cPoint->setPosition(hero->getContentSize() / 2);
	cPoint->setVisible(false);
	addChild(cPoint);

	Invincible(4);
}


//decide the director
//pr:press or release,press:1,release:-1
void HeroControl::MoveDirector(EventKeyboard::KeyCode key, int pr) {
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) director += pr * Vec2(0, speed);
	if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) director -= pr * Vec2(0, speed);
	if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW) director -= pr * Vec2(speed, 0);
	if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) director += pr * Vec2(speed, 0);
	if (key == EventKeyboard::KeyCode::KEY_LEFT_SHIFT) {
		if (pr == 1) {
			director = director * lowSpeed / maxSpeed;
			cPoint->setVisible(true);
			speed = lowSpeed;
		}
		else {
			director = director * maxSpeed / lowSpeed;
			cPoint->setVisible(false);
			speed = maxSpeed;
		}
	}
	if (key == EventKeyboard::KeyCode::KEY_Z) isShoot = pr + 1;
	if (key == EventKeyboard::KeyCode::KEY_ESCAPE) GameScene::getInstance()->ReturnTitle();
}

void HeroControl::HeroMove(Vec2 director) {
	Vec2 toPosition = hero->getPosition() + director;
	toPosition.x = toPosition.x < s_width - planeWidth ? toPosition.x : s_width - planeWidth;
	toPosition.x = toPosition.x > planeWidth - s_width ? toPosition.x : planeWidth - s_width;
	toPosition.y = toPosition.y < s_height - planeHeight ? toPosition.y : s_height - planeHeight;
	toPosition.y = toPosition.y > planeHeight - s_height ? toPosition.y : planeHeight - s_height;
	hero->setPosition(toPosition);
	cPoint->setPosition(toPosition);
	if (director.x > 0) hero->setRotationY(5);
	else if (director.x < 0) hero->setRotationY(-5);
	else hero->setRotationY(0);

}

void HeroControl::MoveUpdate(float detal) {
	if(canMove) HeroMove(director);
}

void HeroControl::BulletUpdate(float detal) {
	if (isShoot) Shoot();
}

void HeroControl::Shoot() {
	int p = GameScene::getInstance()->power / 100;
	switch (p) {
	case 0:
		BulletShoot(Vec2(0, 0), 0);
		break;
	case 1:
		BulletShoot(Vec2(-5, 0), 0);
		BulletShoot(Vec2(5, 0), 0);
		break;
	case 2:
		if (speed == maxSpeed) {
			BulletShoot(Vec2(0, 0), 0);
			BulletShoot(Vec2(-5, 0), -100);
			BulletShoot(Vec2(5, 0), 100);
		}
		else {
			BulletShoot(Vec2(0, 0), 0);
			BulletShoot(Vec2(-10, -5), 0);
			BulletShoot(Vec2(10, -5), 0);
		}
		break;
	case 3:
		if (speed == maxSpeed) {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-5, 0), -100);
			BulletShoot(Vec2(5, 0), 100);
		}
		else {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-15, -5), 0);
			BulletShoot(Vec2(15, -5), 0);
		}
		break;
	case 4:
		if (speed == maxSpeed) {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-5, 0), -100);
			BulletShoot(Vec2(5, 0), 100);
			BulletShoot(Vec2(-5, 0), -200);
			BulletShoot(Vec2(5, 0), 200);
		}
		else {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-15, -5), 0);
			BulletShoot(Vec2(15, -5), 0);
			BulletShoot(Vec2(-25, -7), 0);
			BulletShoot(Vec2(25, -7), 0);
		}
		break;
	default:
		if (speed == maxSpeed) {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-5, 0), -100);
			BulletShoot(Vec2(5, 0), 100);
			BulletShoot(Vec2(-5, 0), -200);
			BulletShoot(Vec2(5, 0), 200);
		}
		else {
			BulletShoot(Vec2(-5, 0), 0);
			BulletShoot(Vec2(5, 0), 0);
			BulletShoot(Vec2(-15, -5), 0);
			BulletShoot(Vec2(15, -5), 0);
			BulletShoot(Vec2(-25, -7), 0);
			BulletShoot(Vec2(25, -7), 0);
		}
		break;
	}
}

void HeroControl::BulletShoot(Vec2 pos, float x) {
	std::string bltName = StringUtils::format("PlaneImage/herobullet_%d.png", UserDefault::getInstance()->getIntegerForKey("planeIndex"));
	auto bullet = Bullet::createBullet(bltName);
	bullet->type = bullet_main;
	bullet->damage = 1 + GameScene::getInstance()->power / 200.0;
	addChild(bullet, 2);
	bullet->setScale(1);
	bullet->setPosition(hero->getPosition() + Vec2(0, planeHeight) + pos);
	auto moveTo = MoveTo::create(0.5, bullet->getPosition() + Vec2(x, 850));
	auto seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(HeroControl::DeleteBullet, this)), nullptr);
	bullet->runAction(seq);
}


void HeroControl::DeleteBullet(Ref * object) {
	Node * node = (Node *)object;
	this->removeChild(node);
}

void HeroControl::Invincible(float time) {
	hero->setOpacity(127);
	cPoint->type = plane_def;
	scheduleOnce(schedule_selector(HeroControl::UnInvincible), time);
}

void HeroControl::UnInvincible(float dt) {
	cPoint->type = plane_main;
	hero->setOpacity(255);
}

void HeroControl::HeroMiss() {
	hero->setPosition(Vec2(0, -s_height / 1.2));
	HeroControl::Invincible(5);
	GameScene::getInstance()->LifeChange(-1);
}