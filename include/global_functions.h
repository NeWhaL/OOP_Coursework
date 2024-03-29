#ifndef GLOBALFUNC
#define GLOBALFUNC

#include "main.h"

enum class TypeObject;

sf::Vector2f NormalizationVector(sf::Vector2f vector);
float LengthVector(sf::Vector2f vector);
sf::Vector2f CurrentCoordinatesOfTheObjectRelativeToAnotherObject(sf::Vector2f current_coordinates, sf::Vector2f coordinates_object);
float LengthBetweenTwoPoints(sf::Vector2f first_point, sf::Vector2f second_point);

std::ostream& operator << (std::ostream &os, const TypeObject &type);
#endif