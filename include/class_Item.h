#ifndef ITM
#define ITM

#include "class_GameObject.h"
#include "class_Shot.h"
#include "class_Effect.h"

enum class TypeItem { SHOT, EFFECT, STAT };

class Item : public GameObject 
{
protected:
	TypeItem type_item;
	float stat_damage;
	float stat_health;
	float stat_range_fire;
	float stat_speed;
	TypeEffect type_effect;
	TypeShot type_shot;

	void Move(float dt) {}

public:
	Item(sf::Vector2f coordinates, sf::Texture* texture, TypeItem type_item, TypeShot type_shot, TypeEffect type_effect,
		  float damage, float health, float speed, float range_fire, int cost);
	void Update(float dt);
	void SendMessage(Message *message);
};
#endif
