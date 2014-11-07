#include <iostream>
#include <memory>

#include "Parser.h"
#include "Visitor.h"
#include "DrawerVisitor.h"
#include "Button.h"
#include "Render.h"
#include "Controller.h"
#include "Matrix.h" //todo: delete after test

using namespace std;

char* fileName = "Form.xml";

int initOpenGL(int argc1, char **argv1) {
	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(800, 500);
	glutInitWindowSize(600, 600);
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

	glClearColor(0, 0, 0, 1);
}

class B{
public:
		B() { std::cout << "B()" << std::endl; };
	~B() {
		std::cout << "~B()" << std::endl;
	}
};

class A{
public:
	std::shared_ptr < B > sss;
	A() : sss(new B){ 
		std::cout << "A()" << std::endl; };
	~A() {
		std::cout << "~A()" << std::endl;
	}
};

int main(int argc, char **argv) {
	//todo: Delete after test
	Matrix<float> matrixTest(4,4);
	matrixTest.loadIdentityMatrix();
	std::shared_ptr<A> bbb(new A());
	bbb.reset();
	Matrix<int> m1 = Matrix<int>(new int[9]{1, 2, 3, 2, 2, 2, 3, 2, 1}, 3, 3);
	Matrix<int> m2 = Matrix<int>(new int[9]{3, 2, 1, 3, 3, 3, 1, 2, 1}, 3, 3);
	Matrix<int>* m3 = m1 * (m2);
	//

	//Parse xml for Views (Model)
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	//Init OpenGL
	initOpenGL(argc, argv);

	//Init render
	Render render;
	render.setViewList(viewList);
	glutDisplayFunc(Render::renderWrapper);

	//Init controller
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