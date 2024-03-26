#include "../include/class_Effect.h"

Effect::Effect(TypeEffect type_effect, TypeObject creator, sf::Texture* texture,
							 GameObject* affected, float effect_time):
							 affected{affected},
							 type_effect{type_effect}, 
							 creator{creator},
							 effect_time{effect_time},
							 timer{0},
							 sprite{nullptr}
{
	if (not sprite) sprite = new sf::Sprite;
	sprite->setTexture(*texture);
}

Effect::~Effect()
{
	delete sprite;
}

void Effect::Draw(sf::RenderWindow* window)
{
	window->draw(*sprite);
}

TypeEffect Effect::GetTypeEffect() const
{
	return type_effect;
}

TypeObject Effect::GetCreator() const
{
	return creator;
}

// Effect::Effect(sf::Vector2f coordinates, sf::Texture *main_texture, int amount_sprite, 
// 					float action_time, TypeEffect type_effect, float damage):
// 					GameObject(coordinates, 0, 0, damage, amount_sprite, 0, 0.15,
// 					main_texture, nullptr, nullptr, nullptr), 
// 					action_time(action_time),
// 					type_effect(type_effect),
// 					total_time(0) {}
