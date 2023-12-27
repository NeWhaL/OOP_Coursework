#ifndef ITM
#define ITM

#include "class_GameObject.h"
#include "class_Shot.h"
#include "class_Effect.h"

enum class TypeItem { SHOT, EFFECT, STAT };

class Item : public GameObject 
{
protected:
	int cost;
	TypeItem type_item;
	float damage;
	float health;
	float range_fire;
	float speed;
	TypeEffect type_effect;
	TypeShot type_shot;

	bool CollisionWithObject(GameObject *object);
	void Move(float dt) {}
	void Buy();

public:
	Item(sf::Vector2f coordinates, sf::Texture* texture, TypeItem type_item, TypeShot type_shot, TypeEffect type_effect,
		  float damage, float health, float speed, float range_fire, int cost);
	void Update(float dt);
	void SendMessage(Message *message);
};
#endif
