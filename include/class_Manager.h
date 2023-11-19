#include "class_Hero.h"
#include "main.h"

class Manager {
private:
  static Manager *manager;
  sf::RenderWindow *window;
  Hero *hero;
  std::list<GameObject *> game_objects;
  sf::Clock time;

  Manager();
  ~Manager();
  Manager(const Manager &){};
  void DrawAllObject() const;
  void Update();

public:
  static Manager *getInstance();
  void Init();
  void Run();
  void End();
};
