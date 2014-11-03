#include "Controller.h"

float Controller::cameraPositionX = 0.1f;
float Controller::cameraPositionY = 0.1f;
float Controller::cameraPositionZ = 0.1f;

float Controller::cameraRotateY = 2;
float Controller::cameraRotateX = 2;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>> list) {
	viewList = list;
}

void Controller::mouseAction(int the_button, int button_state, int x, int y) {
	std::cout << "X: " << x << "   Y: " << y << std::endl;
}

void Controller::keyboardSpecialAction(int key, int x, int y) {
	std::cout << "Key: " << key << "   X: " << x << "   Y: " << y << std::endl;
	switch (key)
	{
	case GLUT_KEY_UP:
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0, cameraPositionY, 0);
		break;
	case GLUT_KEY_DOWN:
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0, -cameraPositionY, 0);
		break;
	case GLUT_KEY_RIGHT:
		glMatrixMode(GL_MODELVIEW);
		glRotatef(cameraRotateY, 0.0, 1.0, 0.0);
		break;
	case GLUT_KEY_LEFT:
		glMatrixMode(GL_MODELVIEW);
		glRotatef(-cameraRotateY, 0.0, 1.0, 0.0);
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void Controller::keyboardPressedAction(unsigned char key, int x, int y) {
	switch (key) {
	case 27:       // When escape is pressed...
		exit(0);    // Exit The Program
		break;
	default:
		break;
	}
}

void Controller::resizeWindow(int width, int height)
{
	std::cout << "glViewport(0, 0, width, height);" << std::endl;
	glViewport(0, 0, width, height);
}