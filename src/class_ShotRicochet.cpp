#include "../include/class_ShotRicochet.h"
#include "../include/class_Manager.h"

ShotRicochet::ShotRicochet(sf::Vector2f coordinates, sf::Vector2f direction,
              float speed, float range_fire, float damage, TypeEffect effect,
              TypeObject who_creator):
              Shot(coordinates, direction, speed, range_fire, damage, effect, who_creator) {}

bool ShotRicochet::CollisionWithObject(const GameObject* const object)
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
		case TypeObject::SHOT: 
			is_collision = true; break;
		default: break;
	}
	if(is_collision)
	{
		float distance_x = coordinates.x - object->GetPositionHead().x;
		float distance_y	= coordinates.y - object->GetPositionHead().y;
		sf::Vector2f vector_for_norm = {distance_x, distance_y};
		vector_for_norm = NormalizationVector(vector_for_norm);
		direction = {vector_for_norm.x + direction.x, vector_for_norm.y + vector_for_norm.y};
		direction = NormalizationVector(direction);
		//сомнительно (чтобы выстрел не убивал противника с одного удара)
		coordinates.x += direction.x * 10;
		coordinates.y += direction.y * 10;
	}
	return is_collision;
}

void ShotRicochet::CollisionWithWall()
{
  Size_arena tmp_size = manager->GetSizeArena();
	float d_x = 0.f;
	float d_y = 0.f;
	if (coordinates.x - radius_hitbox_head < tmp_size.up_left.x)
  {
	  d_x = tmp_size.up_left.x - (coordinates.x - radius_hitbox_head);
		direction.x *= -1;
  }
	else if (coordinates.x + radius_hitbox_head > tmp_size.down_right.x)
  {
	  d_x = tmp_size.down_right.x - (coordinates.x + radius_hitbox_head);
		direction.x *= -1;
  }
	if (coordinates.y - radius_hitbox_head < tmp_size.up_left.y)
  {
	  d_y = tmp_size.up_left.y - (coordinates.y - radius_hitbox_head);
		direction.y *= -1;
  }
	else if (coordinates.y + radius_hitbox_head > tmp_size.down_right.y)
  {
	  d_y = tmp_size.down_right.y - (coordinates.y + radius_hitbox_head);
		direction.y *= -1;
  }
	coordinates.x += d_x;
	coordinates.y += d_y;
}

void ShotRicochet::SendMessage(Message* message)
{
	if (message->type_message != TypeMessage::MOVE or message->who_sent == this) 
		return;
	CollisionWithObject(message->who_sent);
}