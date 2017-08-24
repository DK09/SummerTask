#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CollisionManager.h"
#include "MusicControl.h"

#include "Bullet.h"
#include "Item.h"
#include "MyPlane.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

void CollisionManager::ItemCollosion(Node * parent, Node * hero) {
	Vector<Node *> child_v = parent->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(* child_v.at(i)).name(), typeid(Item).name()) == 0) {
			if (hero->getBoundingBox().intersectsRect(child_v.at(i)->getBoundingBox())) {
				//getItem();
			}
		}
	}
}

void CollisionManager::HeroCollosion(Node * parent, Node * cPoint) {
	Vector<Node *> child_v = parent->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(*child_v.at(i)).name(), typeid(MyPlane).name()) == 0) {
			if (cPoint->getBoundingBox().intersectsRect(child_v.at(i)->getBoundingBox())) {
				//Die();
			}
			for (int j = 0; j <= child_v.size() - 1; j++) {
				if (strcmp(typeid(*child_v.at(i)).name(), typeid(Bullet).name()) == 0) {
					MyPlane * enemy = (MyPlane *)child_v.at(i);
					Bullet * bullet = (Bullet *)child_v.at(j);
					//EnemyAttack(enemy, bullet);
				}
			}
		}
	}
}

void CollisionManager::EnemyCollosion(Node * parent, Node * cPoint) {
	Vector<Node *> child_v = parent->getChildren();
	for (int i = 0; i <= child_v.size() - 1; i++) {
		if (strcmp(typeid(*child_v.at(i)).name(), "") == 0) {
			if (cPoint->getBoundingBox().intersectsRect(child_v.at(i)->getBoundingBox())) {
				//Die()
			}
		}
	}
}