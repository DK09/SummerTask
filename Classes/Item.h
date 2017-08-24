#ifndef __Item_H__
#define __Item_H__

#include "cocos2d.h"

typedef enum ItemType{
	item_def = 0,
	item_dian = 1,
	item_power = 2,
	item_power_big = 3,
	item_power_full = 4,
	item_power_dian = 5,
	item_bomb = 6,
	item_life = 7,
	item_graze = 8
}Item_Type;

class Item : public cocos2d::Sprite
{
public:	
	Item_Type type;
public:

	bool initWithFile(const std::string& path);

	static Item* createItem(Item_Type type);

	void ItemAnimi(Item * item);

	void DeleteItem(Ref * object);

    // implement the "static create()" method manually
    CREATE_FUNC(Item);
};

#endif // __Item_SCENE_H__
