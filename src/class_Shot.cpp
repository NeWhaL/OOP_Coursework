#include "../include/class_Manager.h"

Shot::Shot(sf::Vector2f coordinates, sf::Vector2f direction, float speed,
           float range_fire, float damage, TypeEffect effect, TypeObject who_creator):
			  GameObject(coordinates, speed, 1, ResourceManager::GetInstance()->getTShot(), 1, damage),
			  direction(direction), 
				range_fire(range_fire),
				effect(effect)
{
	creator = who_creator;
  type_object = TypeObject::SHOT;
  amount_sprite = 1;
}

void Shot::Update(float dt) 
{
   Move(dt);
   MoveSprite();
   CollisionWithWall();
}

void Shot::CollisionWithWall() 
{
	Size_arena tmp_size = manager->GetSizeArena();
	if (not(coordinates.x - radius_hitbox_head < tmp_size.up_left.x or
          coordinates.x + radius_hitbox_head > tmp_size.down_right.x or
          coordinates.y - radius_hitbox_head < tmp_size.up_left.y or
          coordinates.y + radius_hitbox_head > tmp_size.down_right.y))
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
	Message::MessageMove(this, manager);
  if (range_fire > 0) return;
  DeathObject(this);
}

void Shot::DeathObject(GameObject* killer)
{
	switch(effect)
	{
		case TypeEffect::EXPLOSION:
			Message::MessageCreateEffect({new EffectBomb(coordinates, TypeObject::PLAYER)}, this, this, manager);
		  break;
		default: break;
	}
	GameObject::DeathObject(killer);
}

Shot::~Shot() {}
