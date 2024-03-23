#include "../include/global_functions.h"
#include "../include/class_GameObject.h"

using namespace sf;

float LengthVector(Vector2f vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f NormalizationVector(Vector2f vector) {
  float length = LengthVector((Vector2f)vector);
  return Vector2f(vector.x / length, vector.y / length);
}

sf::Vector2f CurrentCoordinatesOfTheObjectRelativeToAnotherObject(sf::Vector2f current_coordinates, sf::Vector2f coordinates_object)
{
	return Vector2f(current_coordinates.x - coordinates_object.x,current_coordinates.y - coordinates_object.y);
}

float LengthBetweenTwoPoints(Vector2f first_point, Vector2f second_point) {
  return std::sqrt((first_point.x - second_point.x) * (first_point.x - second_point.x) +
      						(first_point.y - second_point.y) * (first_point.y - second_point.y));
}

std::ostream& operator << (std::ostream &os, const TypeObject &type)
{
	if (type == TypeObject::PLAYER)
		return os << "PLAYER";
	else if (type == TypeObject::SHOT)	
		return os << "SHOT";
	else if (type == TypeObject::ENEMY)
		return os << "ENEMY";
	else if (type == TypeObject::EFFECT)
		return os << "EFFECT";
	else if (type == TypeObject::ITEM)
		return os << "ITEM";
	return os << "NONE";
}
