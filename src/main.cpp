#include "../include/class_Manager.h"

int main(int argc, char *argv[]) {
  Manager *manager = Manager::GetInstance();
  manager->Run();
  manager->End();
  return 0;
}
