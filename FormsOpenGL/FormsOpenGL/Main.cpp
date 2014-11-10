#include <iostream>
#include <memory>

#include "Parser.h"
#include "Visitor.h"
#include "DrawerVisitor.h"
#include "Button.h"
#include "Render.h"
#include "Controller.h"

using namespace std;

char* fileName = "Form.xml";

int initOpenGL(int argc1, char **argv1) {
	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(800, 500);
	glutInitWindowSize(600, 600);
	glutCreateWindow("FormsOpenGL");

	GLenum glew_status = glewInit();
	if (GLEW_OK != glew_status) {
		std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
		return 1;
	}

	if (!GLEW_VERSION_2_0) {
		std::cout << "No support for OpenGL 2.0 found\n";
		return 1;
	}

	glClearColor(0, 0, 0, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

int main(int argc, char **argv) {
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	initOpenGL(argc, argv);

	Render render;
	render.setViewList(viewList);
	glutDisplayFunc(Render::renderWrapper);

	Controller controller;
	controller.setViewList(viewList);
	glutReshapeFunc(Controller::resizeWindow);
	glutMouseFunc(Controller::mouseAction);
	glutMotionFunc(Controller::mouseMove);
	glutSpecialFunc(Controller::keyboardSpecialAction);
	glutMouseWheelFunc(Controller::mouseScroll);
	glutKeyboardFunc(Controller::keyboardPressedAction);

	glutMainLoop();
	system("pause");
	return 0;
}