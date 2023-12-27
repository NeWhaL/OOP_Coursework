#include "../include/class_GameObject.h"
#include "../include/class_Manager.h"

GameObject::GameObject(sf::Vector2f coordinates, float speed, float health,
                       sf::Texture *main_texture, int amount_sprite, float damage)
    : coordinates(coordinates), speed(speed), health(health),
      main_sprite(new sf::Sprite), amount_sprite(amount_sprite), damage(damage), is_object_alive(true)
{
	manager = Manager::GetInstance();
	main_sprite->setTexture(*main_texture);
	main_sprite->setScale(0.5 , 0.5);
	sf::FloatRect bounds_sprite = main_sprite->getLocalBounds();
	main_sprite->setTextureRect(sf::IntRect(
		0, 0, bounds_sprite.width / amount_sprite, bounds_sprite.height));
	main_sprite->setOrigin(bounds_sprite.width / amount_sprite / 2,
								 bounds_sprite.height / 2);
	radius_hitbox_head = main_sprite->getGlobalBounds().height / 2;
}

GameObject::~GameObject() { delete main_sprite; }

void GameObject::SetPosition(sf::Vector2f coordinates) {	this->coordinates = coordinates; }

float GameObject::GetRadiusHitbox() const { return radius_hitbox_head; }

sf::Vector2f GameObject::GetPosition() const { return coordinates; }

sf::Vector2f GameObject::GetPositionHead() const { return main_sprite->getPosition(); }

float GameObject::GetDamage() const { return damage; }

void GameObject::CollisionWithWall() 
{
	Size_arena tmp_size = manager->GetSizeArena();
	float d_x = 0.f;
	float d_y = 0.f;
	if (coordinates.x - radius_hitbox_head < tmp_size.up_left.x)
	 d_x = tmp_size.up_left.x - (coordinates.x - radius_hitbox_head);
	else if (coordinates.x + radius_hitbox_head > tmp_size.down_right.x)
	 d_x = tmp_size.down_right.x - (coordinates.x + radius_hitbox_head);
	if (coordinates.y - radius_hitbox_head < tmp_size.up_left.y)
	 d_y = tmp_size.up_left.y - (coordinates.y - radius_hitbox_head);
	else if (coordinates.y + radius_hitbox_head > tmp_size.down_right.y)
	 d_y = tmp_size.down_right.y - (coordinates.y + radius_hitbox_head);
	coordinates.x += d_x;
	coordinates.y += d_y;
}

bool GameObject::CollisionWithObject(GameObject *object) 
{
	return radius_hitbox_head + object->radius_hitbox_head >=
			 LengthBetweenTwoPoints(coordinates, object->GetPositionHead());
}

void GameObject::DeathObject(GameObject* killer)
{
	if (not is_object_alive)
		return;
	Message* message = new Message;
	message->type_message = TypeMessage::DEATH;
	message->who_sent = this;
	message->death.killer = killer;
	message->death.who_die = this;
	manager->SendMessage(message);
	is_object_alive = false;
}

TypeObject GameObject::GetTypeObject() const { return type_object; }

TypeObject GameObject::GetCreatorObject() const { return creator; }

void GameObject::Draw(sf::RenderWindow* window) const { window->draw(*main_sprite); }

void GameObject::MoveSprite() { main_sprite->setPosition(coordinates.x, coordinates.y); }
