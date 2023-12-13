#ifndef MNG
#define MNG

#include "class_GameObject.h"
#include "class_Hero.h"

class Manager {
private:
  static Manager *manager;
  sf::RenderWindow *window;
  std::list<GameObject *> game_objects;
  std::list<Message *> messages;

  Manager();
  ~Manager();
  Manager(const Manager &){};
  void DrawAllObject() const;
  void Update(float dt);
  void EventProcessing(sf::Event &ev);
  static void Destroy();

public:
  static Manager *GetInstance();
  sf::RenderWindow *GetWindow() const;
  void SendMessage(Message *msg);
  void Run();
  void End();
};
#endif
