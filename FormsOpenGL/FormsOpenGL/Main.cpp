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

	glClearColor(0.1, 0.1, 0.1, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Enable transperancy
	glEnable(GL_BLEND);
	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);
	//Enable light
	GLfloat mat_specular[] = { 0, 0, 0, 0 };
	GLfloat mat_shininess[] = { 100 };
	GLfloat light_ambient[] = { 1.0, 0, 0, 0.0 };
	GLfloat light_position[] = { 0.7, 0.7, -1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	//only for specular light
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); //blik radius

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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