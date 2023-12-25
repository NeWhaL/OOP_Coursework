#ifndef EFC
#define EFC

#include "class_GameObject.h"

enum class TypeEffect { NONE, TORNADO, BLEEDING, EXPLOSION };

class Effect : public GameObject
{
protected:
	float action_time;
	float total_time;
	TypeEffect type_effect;

	virtual void Action(float dt) = 0;	
	void Move(float dt) {}

public:
	Effect(sf::Vector2f coordinates, sf::Texture *main_texture, int amount_sprite, 
			 float action_time, TypeEffect type_effect, float damage);
	virtual ~Effect() {};
};

#endif
