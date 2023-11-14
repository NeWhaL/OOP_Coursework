#include "main.h"

class GameObject {
protected:
  sf::Vector2f coordinates;
  sf::Sprite *sprite;

public:
  GameObject();
  void SetPosition(sf::Vector2f coordinates);
  sf::Vector2f CurrentPosition() const;
  virtual ~GameObject();

  virtual void Update(float dt) = 0;
  void Draw();
};
