#include "../include/main.h"
#include "../include/class_application.h"

int main(int argc, char *argv[]) {
  app::Application application;
  application.Init();
  application.Run();
  application.End();
  return 0;
}
