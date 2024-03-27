#ifndef EVENTMANAGER
#define EVENTMANAGER
#include "main.h"
#include "class_EffectExplosion.h"

class GameObject;

class EventManager
{
  std::list<Effect*> effects;

  void CreateEffect(Message* message);
	void DestroyEffect(Effect* effect);

public:
  EventManager() = default;
  ~EventManager();
  void Update(float dt);
  void Draw(sf::RenderWindow* window);
  void SendMessage(Message* message);
};

#endif