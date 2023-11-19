#include "main.h"

class GameObject {
protected:
  sf::Vector2f coordinates;

public:
  GameObject();
  void SetPosition(sf::Vector2f coordinates);
  sf::Vector2f GetPosition() const;
  sf::Vector2f CurrentPosition() const;
  virtual ~GameObject();
  virtual void Draw(sf::RenderWindow *window) const = 0;
  void SetTexture();
  virtual void Update(float dt) = 0;
};
