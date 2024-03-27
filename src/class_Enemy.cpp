#include "../include/class_Enemy.h"
#include "../include/class_Manager.h"

Enemy::Enemy(sf::Vector2f coordinates, float speed, float health, float damage, int amount_sprite_head, int amount_sprite_legs, 
						 sf::Texture* head_texture, sf::Texture* legs_up_down_texture, sf::Texture* legs_left_texture, 
						 sf::Texture* legs_right_texture):
			 GameObject{coordinates, speed, health, damage, amount_sprite_head, amount_sprite_legs, 0.5f,
			 						head_texture, legs_up_down_texture, legs_left_texture, legs_right_texture},	
			 hero{manager->GetHero()} {}

void Enemy::Move(float dt) 
{
  coordinates.x += direction.x * speed * dt;
  coordinates.y += direction.y * speed * dt;
}

void Enemy::DirectionOnHero()
{
	direction = hero->GetPositionHead() - coordinates;
	direction = NormalizationVector(direction);
	if (not GameObject::CollisionWithObject(hero)) 
		return;
	direction.x *= -1;
	direction.y *= -1;
}

bool Enemy::CollisionWithEffect(Effect* effect) const
{
	if (effect->GetCreator() == TypeObject::ENEMY) return false;
	switch (effect->GetTypeEffect())
	{
		case TypeEffect::EXPLOSION:
		{
			EffectExplosion* effect_explosion = static_cast<EffectExplosion*>(effect);
			return radius_hitbox_head + effect_explosion->GetKillRadius() >=
			  LengthBetweenTwoPoints(GetPositionHead(), effect_explosion->GetCoordinates());
		} break;
		default: break;
	}
	return false;
}