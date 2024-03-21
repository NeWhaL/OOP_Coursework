#ifndef FONT
#define FONT
#include "main.h"
#include "class_GameObject.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class FontForCharacteristics
{
  // friend GameObject;
private: 
  sf::Font* font_for_health;
  sf::Text* result_text;
  sf::Vector2f coordinates;
  int font_size;

public:
  FontForCharacteristics(std::string font_name, int font_size);
  ~FontForCharacteristics();
  void Update(const GameObject* object);
  void Draw(sf::RenderWindow *window, const GameObject* object);
  sf::Text& getText();
};

#endif