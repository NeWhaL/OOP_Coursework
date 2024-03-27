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