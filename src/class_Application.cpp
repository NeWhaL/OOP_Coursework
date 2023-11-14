#include "../include/class_Application.h"

namespace app {
Application::Application() : Window(nullptr) {}
Application::~Application() {}

void Application::Init() {
  Window = new sf::RenderWindow(sf::VideoMode(640, 640), "GAME");
}

void Application::Run() {
  while (Window->isOpen()) {
    sf::Event ev;
    while (Window->pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        Window->close();
      }
    }
  }
}

void Application::End() { delete Window; }
} // namespace app
