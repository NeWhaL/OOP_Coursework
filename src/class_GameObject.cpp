#include "../include/class_GameObject.h"
#include "../include/class_Manager.h"
#include "../include/class_Font.h"

Manager* GameObject::manager = Manager::GetInstance();
ResourceManager* GameObject::res_manager = ResourceManager::GetInstance();

GameObject::GameObject(sf::Vector2f coordinates, float speed, float health, float damage,
											 int amount_sprite_head, int amount_sprite_legs, float scale_sprite,
             sf::Texture* head_texture,
             sf::Texture* legs_up_down_texture,
             sf::Texture* legs_left_texture,
             sf::Texture* legs_right_texture):
	coordinates{coordinates},
	direction{0.f, 0.f},
	speed{speed},
	health{health},
	head_sprite{nullptr},
	legs_up_down{nullptr},
	legs_left{nullptr},
	legs_right{nullptr},
	amount_money{0},
 	amount_sprite_head{amount_sprite_head},
	amount_sprite_legs_up_down{amount_sprite_legs},
	damage{damage},
	is_object_alive{true},
	scale_sprite{scale_sprite},
	font_characteristics{new FontForCharacteristics("fonts/CodenameCoderFree4F-Bold.ttf", 50)}
{

	SetSpriteFromTexture(head_texture, head_sprite, amount_sprite_head);
	SetSpriteFromTexture(legs_up_down_texture, legs_up_down, amount_sprite_legs);
	SetSpriteFromTexture(legs_left_texture, legs_left, amount_sprite_legs);
	SetSpriteFromTexture(legs_right_texture, legs_right, amount_sprite_legs);

	radius_hitbox_head = head_sprite->getGlobalBounds().height / 2;
	if(not legs_up_down) return;
	radius_hitbox_legs = legs_up_down->getGlobalBounds().height / 2;
}

void GameObject::SetSpriteFromTexture(const sf::Texture* texture, sf::Sprite*& sprite, int amount_sprite)
{
	if (not texture) return;
	if (not sprite) sprite = new sf::Sprite;
	sprite->setTexture(*texture);
	sprite->setScale(scale_sprite, scale_sprite);
	sf::FloatRect bounds_sprite = sprite->getLocalBounds();
	sprite->setTextureRect(sf::IntRect(0, 0, bounds_sprite.width / amount_sprite,
	                bounds_sprite.height));
	sprite->setOrigin(bounds_sprite.width / amount_sprite / 2,
                           bounds_sprite.height / 2);
}

GameObject::~GameObject() 
{ 
	delete head_sprite; 
	delete legs_up_down;
	delete legs_left;
	delete legs_right;
}

void GameObject::SetPosition(sf::Vector2f coordinates) {	this->coordinates = coordinates; }

float GameObject::GetRadiusHitbox() const { return radius_hitbox_head; }

sf::Vector2f GameObject::GetPosition() const { return coordinates; }

sf::Vector2f GameObject::GetPositionHead() const { return head_sprite->getPosition(); }

int& GameObject::GetMoney() { return amount_money; }

float GameObject::GetDamage() const { return damage; }

sf::Vector2f GameObject::GetDirection() const
{ 
	return direction; 
}

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

bool GameObject::CollisionWithObject(const GameObject * const object) 
{
	return radius_hitbox_head + object->radius_hitbox_head >=
			 LengthBetweenTwoPoints(GetPositionHead(), object->GetPositionHead());
}

void GameObject::DeathObject(GameObject* killer)
{
	if (not is_object_alive) return;
	Message::Death(this, killer, amount_money);
	is_object_alive = false;
}

TypeObject GameObject::GetTypeObject() const { return type_object; }

TypeObject GameObject::GetCreatorObject() const { return creator; }

void GameObject::Draw(sf::RenderWindow* window) const 
{
	//пока что рисует стандартное расположение ног и головы
	font_characteristics->Update(this);
	if(legs_up_down)
		window->draw(*legs_up_down);
	window->draw(*head_sprite); 
	font_characteristics->Draw(window, this);
}

void GameObject::MoveSprite() 
{ 
	if(legs_up_down)
	{
		legs_up_down->setPosition(coordinates.x, coordinates.y);  
		head_sprite->setPosition(coordinates.x, coordinates.y - legs_up_down->getLocalBounds().height +
							 legs_up_down->getGlobalBounds().height);
	}
	else
		head_sprite->setPosition(coordinates.x, coordinates.y);
}