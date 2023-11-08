#include "main.h"

namespace app {
class Application;
}

class app::Application {
private:
  sf::RenderWindow *Window;

public:
  Application();
  ~Application();
  void Init();
  void Run();
  void End();
};
