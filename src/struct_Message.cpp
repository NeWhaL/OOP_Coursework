#include "../include/struct_Message.h"
#include "../include/class_Manager.h"
#include "../include/class_Shot.h"
#include "../include/class_Effect.h"

Manager* Message::manager = Manager::GetInstance();

void Message::Move(GameObject* who_sent)
{
	Message* message = new Message;
	message->type_message = TypeMessage::MOVE;
	message->who_sent = who_sent;
	manager->SendMessage(message);
}

void Message::CreateShot(Shot* shot, GameObject* creator)
{
  Message *message = new Message;
  message->type_message = TypeMessage::CREATE;
  message->create.new_object = shot;
  message->create.creator = creator;
  manager->SendMessage(message);
}

void Message::Death(GameObject* who_die, GameObject* killer, int amount_money)
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
							float health, float damage, float speed, float range_fire)
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

void Message::StartEffect(TypeEffect type_effect, TypeObject creator, GameObject* who_sent)
{
	Message* message = new Message;
	message->type_message = TypeMessage::CREATE_EFFECT;
	message->who_sent = who_sent;
	message->create_effect.type_effect = type_effect;
	message->create_effect.creator = creator;
	manager->SendMessage(message);
}

void Message::EndEffect(Effect* effect)
{
	Message* message = new Message;
	message->who_sent = nullptr;
	message->type_message = TypeMessage::END_EFFECT;
	message->end_effect.effect = effect;
	manager->SendMessage(message);
}

void Message::ActionEffect(Effect* effect)
{
	Message* message = new Message;
	message->who_sent = nullptr;
	message->type_message = TypeMessage::EFFECT;
	message->effect.effect = effect;
	manager->SendMessage(message);
}

void Message::EndGame(TypeEndGame reason)
{
	Message* message = new Message();
	message->type_message = TypeMessage::END_GAME;
	message->who_sent = nullptr;
	message->end_game.reason = reason;
	manager->SendMessage(message);
}