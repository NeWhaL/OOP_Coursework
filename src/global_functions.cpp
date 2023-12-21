#include "../include/global_functions.h"

using namespace sf;

float LengthVector(Vector2f vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f NormalizationVector(Vector2f vector) {
  float length = LengthVector((Vector2f)vector);
  return Vector2f(vector.x / length, vector.y / length);
}
sf::Vector2i
MouseCoordinatesRelativeOtherCoordinates(Vector2i coordinates_mouse,
                                         Vector2f coordinates_object) {
  return Vector2i(coordinates_mouse.x - coordinates_object.x,
                  coordinates_mouse.y - coordinates_object.y);
}

float LengthBetweenTwoPoints(Vector2f first_point, Vector2f second_point) {
  return sqrt(
      (first_point.x - second_point.x) * (first_point.x - second_point.x) +
      (first_point.y - second_point.y) * (first_point.y - second_point.y));
}
