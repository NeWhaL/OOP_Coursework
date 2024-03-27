#include "../include/class_ShotThrought.h"

ShotThrought::ShotThrought(sf::Vector2f coordinates, sf::Vector2f direction, 
              float speed, float range_fire, float damage,
              TypeEffect effect, TypeObject who_creator):
              Shot(coordinates, direction, speed, range_fire, damage, effect, who_creator),
              do_damage{true},
              timer{0},
              amount_of_time_to_do_damage{0.2} {}

void ShotThrought::Update(float dt)
{
  Move(dt);
  MoveSprite();
  timer += dt;
  if (timer >= amount_of_time_to_do_damage)
  {
    do_damage = true;
    timer = 0;
  }
  if (do_damage) Message::Move(this);
  if (range_fire > 0) return;
  DeathObject(this);
}

void ShotThrought::SendMessage(Message* message)
{
  if (message->type_message != TypeMessage::MOVE or message->who_sent == this) 
		return;
	if (not CollisionWithObject(message->who_sent)) return;
  do_damage = false;
}