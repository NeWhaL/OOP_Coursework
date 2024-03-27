#include "../include/class_Manager.h"

Shot::Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
           float range_fire, float damage, TypeEffect effect, TypeObject who_creator):
			  GameObject(coordinates, speed, 1, damage, 1, 0, 0.5f,
        res_manager->getTShot(), nullptr, nullptr, nullptr),
				range_fire(range_fire),
				effect(effect)
{
	creator = who_creator;
  type_object = TypeObject::SHOT;
  this->direction = direction;
}

void Shot::Update(float dt) 
{
  Move(dt);
	Message::Move(this);
  MoveSprite();
  CollisionWithWall();
  if (range_fire > 0) return;
  DeathObject(this);
}

void Shot::CollisionWithWall() 
{
	if (not(coordinates.x - radius_hitbox_head < size_arena.up_left.x or
          coordinates.x + radius_hitbox_head > size_arena.down_right.x or
          coordinates.y - radius_hitbox_head < size_arena.up_left.y or
          coordinates.y + radius_hitbox_head > size_arena.down_right.y))
  return;
	DeathObject(this);
}

void Shot::Move(float dt) 
{
  sf::Vector2f delta_position = coordinates;
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
  delta_position -= coordinates;
  float length_delta_position = LengthVector(delta_position);
  range_fire -= length_delta_position;
}

bool Shot::CollisionWithObject(const GameObject * const object)
{
  if (not GameObject::CollisionWithObject(object))
		return false; 
	bool is_collision = false;
	switch(object->GetTypeObject())
	{
		case TypeObject::PLAYER:
			is_collision = (creator != TypeObject::PLAYER); break;
		case TypeObject::ENEMY:
			is_collision = (creator != TypeObject::ENEMY); break;
		default: break;
	}
	return is_collision;
}

void Shot::DeathObject(GameObject* killer)
{
  if (effect != TypeEffect::NONE)
    Message::StartEffect(effect, creator, this);
	GameObject::DeathObject(killer);
}