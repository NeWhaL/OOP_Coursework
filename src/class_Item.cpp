#include "../include/class_Item.h"
#include "../include/class_Manager.h"

Item::Item(sf::Vector2f coordinates, sf::Texture* texture, TypeItem type_item, TypeShot type_shot, TypeEffect type_effect, 
			  float damage, float health, float speed, float range_fire, int cost):
			  GameObject(coordinates, 0, 0, texture, 1, 0), type_item(type_item), type_effect(type_effect),
			  type_shot(type_shot), stat_damage(damage), stat_health(health), stat_speed(speed), stat_range_fire(range_fire) 
{
	amount_money = 5;
	main_sprite->setScale(0.15, 0.15);
	radius_hitbox_head = main_sprite->getGlobalBounds().height / 2;
}

void Item::Update(float dt)
{
	MoveSprite();
}

void Item::SendMessage(Message* message)
{
	if (message->who_sent->GetTypeObject() != TypeObject::PLAYER)
		return;
	if (not GameObject::CollisionWithObject(message->who_sent))
		return;
	if (amount_money > message->who_sent->GetMoney())
		return;
	Message* message_item = new Message;
	message_item->who_sent = this;
	message_item->type_message = TypeMessage::ITEM;
	message_item->item.type_shot = type_shot;
	message_item->item.type_effect = type_effect;
	message_item->item.health = stat_health;
	message_item->item.damage = stat_damage;
	message_item->item.speed = stat_speed;
	message_item->item.range_fire = stat_range_fire;
	manager->SendMessage(message_item);
	GameObject::DeathObject(message->who_sent);	
}
