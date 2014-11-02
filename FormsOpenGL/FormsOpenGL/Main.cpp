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
	glutInitWindowPosition(400, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("FormsOpenGL");

	//! Before shader initialization
	GLenum glew_status = glewInit();
	if (GLEW_OK != glew_status) {
		//! GLEW is not initialized
		std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
		return 1;
	}

	//! Check OpenGL 2.0
	if (!GLEW_VERSION_2_0) {
		std::cout << "No support for OpenGL 2.0 found\n";
		return 1;
	}

	glClearColor(1, 0, 0, 0);
}

int main(int argc, char **argv) {
	//Parse xml for Views (Model)
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	//Init OpenGL
	initOpenGL(argc, argv);

	//Init controller
	Controller controller;
	controller.setViewList(viewList);
	glutReshapeFunc(Controller::resizeWindow);
	glutMouseFunc(Controller::mouseAction);
	glutSpecialFunc(Controller::keyboardSpecialAction);
	glutKeyboardFunc(Controller::keyboardPressedAction);

	//Init render
	Render render;
	render.setViewList(viewList);
	glutDisplayFunc(Render::renderWrapper);

	glutMainLoop();
	system("pause");
	return 0;
}