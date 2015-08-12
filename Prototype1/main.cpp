#include <iostream>
#include "locale.h"

#include "scenes_1.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	//Scene::RunScene1();
	Scene::RunScene2();
	
	return 0;
}