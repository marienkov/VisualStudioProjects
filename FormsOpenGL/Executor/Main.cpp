#include <iostream>
#include <memory>

#include <Engine.h>

using namespace std;

char* fileName = "Form.xml";

int main(int argc, char **argv) {
	Engine engine;
	engine.loadView(fileName);
	engine.initOpenGL(argc, argv);
	engine.initLight();
	engine.initController();
	engine.startRendering();

	system("pause");
	return 0;
}