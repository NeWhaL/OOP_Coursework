#include "../include/class_Effect.h"

Effect::Effect(sf::Vector2f coordinates, sf::Texture *main_texture, int amount_sprite, 
					float action_time, TypeEffect type_effect, float damage):
					GameObject(coordinates, 0, 0, main_texture, amount_sprite, damage), 
					action_time(action_time), type_effect(type_effect), total_time(0) {}
