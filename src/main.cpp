#include "../include/class_Manager.h"

int main(int argc, char *argv[]) 
{
	srand(time(nullptr));
   Manager *manager = Manager::GetInstance();
   manager->Run();
   manager->End();
   return 0;
}
