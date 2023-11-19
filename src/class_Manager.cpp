#include "../include/class_Manager.h"

Manager *Manager::manager = nullptr;

Manager::Manager() : window(nullptr) {}

Manager::~Manager() {}

Manager *Manager::getInstance() {
  if (manager == nullptr)
    manager = new Manager;
  return manager;
}

void Manager::Init() {
  window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "GAME",
                                sf::Style::Fullscreen);
}

void Manager::Run() {
  hero = new Hero;
  while (window->isOpen()) {
    sf::Event ev;
    while (window->pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        window->close();
      }
    }

    // window->clear(sf::Color(122, 0, 0));
    DrawAllObject();
    window->display();
  }
}

void Manager::End() { delete window; }

void Manager::DrawAllObject() const { hero->Draw(window); }
