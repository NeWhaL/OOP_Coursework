#include "../include/struct_Message.h"
#include "../include/class_Manager.h"
#include "../include/class_Shot.h"
#include "../include/class_Effect.h"

void Message::MessageMove(GameObject* who_sent, Manager* manager)
{
	Message* message = new Message;
	message->type_message = TypeMessage::MOVE;
	message->who_sent = who_sent;
	manager->SendMessage(message);
}

void Message::MessageCreateShot(Shot* shot, GameObject* creator, Manager* manager)
{
  Message *message = new Message;
  message->type_message = TypeMessage::CREATE;
  message->create.new_object = shot;
  message->create.creator = creator;
  manager->SendMessage(message);
}

void Message::MessageCreateEffect(Effect* effect, GameObject* who_sent, GameObject* creator, Manager* manager)
{
  Message* message = new Message;
	message->who_sent = who_sent;
	message->type_message = TypeMessage::CREATE;
	message->create.creator = creator;
	message->create.new_object = effect;
	manager->SendMessage(message);
}

void Message::ActionEffect(GameObject* who_sent, TypeObject creator, TypeEffect type_effect, float damage, Manager* manager)
{
  Message* message = new Message;
	message->type_message = TypeMessage::EFFECT;
	message->who_sent = who_sent;
	message->effect.creator = creator;
	message->effect.type = type_effect;
	message->effect.damage = damage;
	manager->SendMessage(message);
}

void Message::Death(GameObject* who_die, GameObject* killer, int amount_money, Manager* manager)
{
	Message* message = new Message;
	message->type_message = TypeMessage::DEATH;
	message->who_sent = who_die;
	message->death.killer = killer;
	message->death.who_die = who_die;
	message->death.money = amount_money;
	manager->SendMessage(message);
}

void Message::BuyItem(GameObject* who_sent, TypeShot type_shot, TypeEffect type_effect, 
							float health, float damage, float speed, float range_fire, Manager* manager)
{
	Message* message_item = new Message;
	message_item->who_sent = who_sent;
	message_item->type_message = TypeMessage::ITEM;
	message_item->item.type_shot = type_shot;
	message_item->item.type_effect = type_effect;
	message_item->item.health = health;
	message_item->item.damage = damage;
	message_item->item.speed = speed;
	message_item->item.range_fire = range_fire;
	manager->SendMessage(message_item);
}