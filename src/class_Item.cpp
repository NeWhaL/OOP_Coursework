#include "../include/class_Item.h"

Item::Item(sf::Vector2f coordinates, sf::Texture* texture, TypeItem type_item, TypeShot type_shot, TypeEffect type_effect, 
			  float damage, float health, float speed, float range_fire, int cost):
			  GameObject(coordinates, 0, 0, 0, 1, 0, 0.15f,
									 texture, nullptr, nullptr, nullptr), 
				type_item(type_item),
				type_effect(type_effect),
			  type_shot(type_shot), 
				stat_damage(damage),
				stat_health(health),
				stat_speed(speed),
				stat_range_fire(range_fire) 
{
	type_object = TypeObject::ITEM;
	amount_money = 5;
}

void Item::Update(float dt)
{
	MoveSprite();
}

void Item::SendMessage(Message* message)
{
	if (message->who_sent->GetTypeObject() != TypeObject::PLAYER or
		  not GameObject::CollisionWithObject(message->who_sent) or
			amount_money > message->who_sent->GetMoney())
		return;
	Message::BuyItem(this, type_shot, type_effect, stat_health, stat_damage,
					 stat_speed, stat_range_fire);
	GameObject::DeathObject(message->who_sent);	
}
