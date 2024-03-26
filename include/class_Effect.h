#ifndef EFC
#define EFC
#include "main.h"
#include "class_ManagerResource.h"

class GameObject;

class Effect
{
protected:
	TypeEffect type_effect;
	TypeObject creator;
	sf::Sprite* sprite;
	GameObject* affected;
	float effect_time;
	float timer;

public:
	Effect(TypeEffect type_effect, TypeObject creator, sf::Texture* texture,
				 GameObject* affected, float effect_time);
	TypeEffect GetTypeEffect() const;
	TypeObject GetCreator() const;
	virtual void Action(float dt) = 0;
	void Draw(sf::RenderWindow* window);
	virtual ~Effect();
};

#endif
// class Effect : public GameObject
// {
// protected:
// 	float action_time;
// 	float total_time;
// 	TypeEffect type_effect;

// 	virtual void Action(float dt) = 0;	
// 	void Move(float dt) {}

// public:
// 	Effect(sf::Vector2f coordinates, sf::Texture *main_texture, int amount_sprite, 
// 			 float action_time, TypeEffect type_effect, float damage);
// 	virtual ~Effect() {};
// };