#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "PlaneLayer.h"
#include "HeroControl.h"
#include "Bullet.h"
#include "MyPlane.h"

USING_NS_CC;

#define width 425
#define height 425

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

Scene* PlaneLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlaneLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlaneLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto planeLayer = CSLoader::createNodeWithVisibleSize("GameLayer.csb");
	addChild(planeLayer);

	_PlaneLayer = this;

	cPoint = HeroControl::getInstance()->cPoint;

	this->schedule(schedule_selector(PlaneLayer::EnemyCollision));
	this->schedule(schedule_selector(PlaneLayer::HeroCollision));

	auto enemy = MyPlane::createPlane("EnemyPLane/1.png");
	enemy->setPosition(Vec2::ZERO);
	addChild(enemy);
	enemy->type = plane_enemy;
	enemy->hp = 10;

    return true;
}

PlaneLayer * PlaneLayer::_PlaneLayer = NULL;

PlaneLayer * PlaneLayer::getInstance() {
	if (_PlaneLayer == NULL) {
		_PlaneLayer = new PlaneLayer();
	}
	return _PlaneLayer;
}

void PlaneLayer::EnemyCollision(float dt) {
	if (cPoint->type == plane_def) return;
	Vector<Node *> child_v = this->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(*child_v.at(i)).name(), typeid(MyPlane).name()) == 0) {
			if (child_v.at(i)->getBoundingBox().intersectsRect(cPoint->getBoundingBox())) {
				HeroMiss();
			}
			for (int j = 0; j <= child_v.size() - 1; j++) {
				if (strcmp(typeid(*child_v.at(j)).name(), typeid(Bullet).name()) == 0) {
					if (child_v.at(i)->getBoundingBox().intersectsRect(child_v.at(j)->getBoundingBox())) {
						MyPlane * enemy = (MyPlane *)child_v.at(i);
						Bullet * bullet = (Bullet *)child_v.at(j);
						if (bullet->type == bullet_main) {
							EnemyInjure(enemy, bullet->damage * GameScene::getInstance()->attack);
							ClearBullet(bullet);
						}
						else if (bullet->type == bullet_main_laser) {
							EnemyInjure(enemy, bullet->damage * GameScene::getInstance()->attack);
						}
					}
				}
			}
		}
	}
}

void PlaneLayer::HeroCollision(float dt) {
	Vector<Node *> child_v = this->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (cPoint->getBoundingBox().intersectsRect(child_v.at(i)->getBoundingBox())) {
			if (strcmp(typeid(*child_v.at(i)).name(), typeid(Bullet).name()) == 0) {
				Bullet * bullet = (Bullet *)child_v.at(i);
				if (bullet->type == bullet_enemy) {
					UnderAttack();
				}
				else if (bullet->type == bullet_enemy_laser && bullet->getOpacity() == 255) {
					UnderAttack();
				}
			}
		}
	}
}

void PlaneLayer::UnderAttack() {
	if (GameScene::getInstance()->noMissTime > 0) {
		GameScene::getInstance()->noMissTime--;
		ClearBullet();
		HeroControl::getInstance()->Invincible(0.5);
	}
	else if (rand_0_1() > 0){
		HeroControl::getInstance()->Invincible(0.5);
	}
	else {
		HeroMiss();
	}
}

void PlaneLayer::HeroMiss() {
	HeroControl::getInstance()->HeroMiss();
}

void PlaneLayer::EnemyInjure(MyPlane * enemy, float damage) {
	enemy->hp -= damage;
	if (enemy->hp <= 0) enemy->removeFromParentAndCleanup(enemy);
}

void PlaneLayer::ClearBullet() {
	//清除敌方子弹
	Vector<Node *> child_v = this->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(*child_v.at(i)).name(), typeid(Bullet).name()) == 0) {
			Bullet * bullet = (Bullet *)child_v.at(i);
			if (bullet->type == bullet_enemy) {
				auto scaleTo = ScaleTo::create(0, 0.3);
				bullet->type = bullet_def;
				auto seq = Sequence::create(scaleTo, CallFuncN::create(CC_CALLBACK_1(PlaneLayer::DeleteBullet, this)), nullptr);
				bullet->runAction(seq);
			}
		}
	}
}

void PlaneLayer::ClearBullet(float time) {
	Vector<Node *> child_v = this->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(*child_v.at(i)).name(), typeid(Bullet).name()) == 0) {
			Bullet * bullet = (Bullet *)child_v.at(i);
			if (bullet->type == bullet_enemy) {
				auto scaleTo = ScaleTo::create(0.3, 0);
				bullet->type = bullet_def;
				auto seq = Sequence::create(scaleTo, CallFuncN::create(CC_CALLBACK_1(PlaneLayer::DeleteBullet, this)), nullptr);
				bullet->runAction(seq);
			}
			//清除敌机激光
			else if (bullet->type == bullet_enemy_laser) {
				bullet->setOpacity(125);
				auto fadeTo = FadeTo::create(time, 125);
				auto fadeIn = FadeTo::create(0.1, 255);
				auto seq = Sequence::create(fadeTo, fadeIn, nullptr);
				bullet->runAction(seq);
			}
		}
	}
}

void PlaneLayer::ClearBullet(Bullet * bullet) {
	if (bullet->type == bullet_main_laser || bullet->type == bullet_enemy_laser) return;
	bullet->stopAllActions();
	bullet->removeFromParentAndCleanup(bullet);
}

void PlaneLayer::DeleteBullet(Ref * object) {
	Bullet * bullet = (Bullet *)object;
	bullet->stopAllActions();
	bullet->removeFromParentAndCleanup(bullet);
}