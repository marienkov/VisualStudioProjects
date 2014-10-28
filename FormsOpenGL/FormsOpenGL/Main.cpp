#include <iostream>
#include <memory>

#include "Parser.h"
#include "Visitor.h"
#include "DrawerVisitor.h"
#include "Button.h"
#include "GlutRender.h"

using namespace std;

char* fileName = "Form.xml";

void glutInitialization(int argc, char **argv);
void render(void);

int main(int argc, char **argv) {
	//Parse xml for Views
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	GlutRender glutRender(argc, argv);
	glutRender.initGlutWindow(400, 300, 400, 400, "FormsOpenGL");
	glutRender.setViewList(viewList);
	glutRender.startDrawing();

	system("pause");
	return 0;
}

