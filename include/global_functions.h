#ifndef GLOBALFUNC
#define GLOBALFUNC

#include "main.h"

sf::Vector2f NormalizationVector(sf::Vector2f vector);
float LengthVector(sf::Vector2f vector);
sf::Vector2i
MouseCoordinatesRelativeOtherCoordinates(sf::Vector2i coordinates_mouse,
                                         sf::Vector2f coordinates_object);
float LengthBetweenTwoPoints(sf::Vector2f first_point,
                             sf::Vector2f second_point);

#endif
