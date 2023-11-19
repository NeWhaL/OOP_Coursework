#include "../include/main.h"
#include "../include/class_Manager.h"

int main(int argc, char *argv[]) {
  Manager::getInstance()->Init();
  Manager::getInstance()->Run();
  Manager::getInstance()->End();
  return 0;
}
