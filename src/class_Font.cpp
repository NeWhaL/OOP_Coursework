#include "../include/class_Font.h"
#include <SFML/Graphics/RenderWindow.hpp>

FontForCharacteristics::FontForCharacteristics(std::string font_name, int font_size): 
                        font_for_health{new sf::Font}, result_text{new sf::Text}, font_size(font_size)
{
  font_for_health->loadFromFile(font_name);
  result_text->setFont(*font_for_health);
  result_text->setCharacterSize(font_size);
  result_text->setFillColor(sf::Color::Red);
}

FontForCharacteristics::~FontForCharacteristics()
{
  delete font_for_health;
  delete result_text;
}

sf::Text& FontForCharacteristics::getText()
{
  return *result_text;
}

void FontForCharacteristics::Update(const GameObject* object)
{
  result_text->setString(std::to_string(static_cast<int>(object->health)));
  result_text->setPosition(object->coordinates.x - 20, object->coordinates.y - 100);
}

void FontForCharacteristics::Draw(sf::RenderWindow* window, const GameObject* object)
{
  TypeObject current = object->type_object;
  if(current == TypeObject::SHOT or current == TypeObject::EFFECT or current == TypeObject::ITEM)
    return;
  window->draw(*result_text);
}