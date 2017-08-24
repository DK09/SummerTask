#include "Item.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

bool Item::initWithFile(const std::string &path) {

	if (Sprite::initWithFile(path)) {

		this->type = item_def;

		return true;
	}

	return false;
}

Item* Item::createItem(Item_Type type) {

	Item* object = NULL;

	object = new Item();
	std::string path = StringUtils::format("ItemImage/point%d.png", type);
	object->initWithFile(path);
	object->autorelease();

	return object;
}

void Item::ItemAnimi(Item * item) {
	if (item->type == item_graze) {
		auto pos = Vec2(rand_0_1() * 50 - 25, rand_0_1() * 25) + item->getPosition();
		auto moveTo1 = MoveTo::create(0.2, pos);
		auto moveTo2 = FadeOut::create(0.2);
		auto seq = Sequence::create(moveTo1, moveTo2, CallFuncN::create(CC_CALLBACK_1(Item::DeleteItem, this)), nullptr); 
		item->runAction(seq);
	}
	else {
		auto pos = Vec2(rand_0_1() * 200 - 100, rand_0_1() * 100) + item->getPosition();
		auto moveTo1 = MoveTo::create(0.2, pos);
		auto moveTo2 = MoveTo::create(4, pos - Vec2(0, 1200));
		auto seq = Sequence::create(moveTo1, moveTo2, CallFuncN::create(CC_CALLBACK_1(Item::DeleteItem, this)), nullptr);
		item->runAction(seq);
	}
}

void Item::DeleteItem(Ref * object) {
	auto item = (Node *)object;
	item->removeFromParentAndCleanup(item);
}