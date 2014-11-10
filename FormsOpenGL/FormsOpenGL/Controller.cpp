#include "Controller.h"

float Controller::cameraPositionX = 0.1f;
float Controller::cameraPositionY = 0.1f;
float Controller::cameraPositionZ = 0.1f;

float Controller::cameraRotateY = 0.005f;
float Controller::cameraRotateX = 0.005f;
float Controller::cameraRotateZ = 0;

int Controller::mouseXstart = 0;
int Controller::mouseYstart = 0;
int Controller::mouseXend = 0;
int Controller::mouseYend = 0;

bool Controller::mouseLeftButtonPressed = false;

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
	if (the_button == GLUT_LEFT_BUTTON && !button_state == GLUT_UP) {
		mouseLeftButtonPressed = true;
	}
	else
		mouseLeftButtonPressed = false;
}

void Controller::mouseMove(int x, int y) {
	if (mouseLeftButtonPressed) {
		mouseXstart = x;
		mouseYstart = y;
		mouseLeftButtonPressed = false;
		return;
	}
	DrawerVisitor::rotateCamera(cameraRotateY * ( mouseYstart - y), cameraRotateX * (x - mouseXstart), 0);
	glutPostRedisplay();
	mouseYstart = y;
	mouseXstart = x;
}

void Controller::keyboardSpecialAction(int key, int x, int y) {
	std::cout << "Key: " << key << "   X: " << x << "   Y: " << y << std::endl;
	switch (key)
	{
	case GLUT_KEY_UP:
		DrawerVisitor::moveY(0.2);
		break;
	case GLUT_KEY_DOWN:
		DrawerVisitor::moveY(-0.2);
		break;
	case GLUT_KEY_RIGHT:
		DrawerVisitor::moveX(0.2);
		break;
	case GLUT_KEY_LEFT:
		DrawerVisitor::moveX(-0.2);
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void Controller::mouseScroll(int button, int dir, int x, int y) {
	std::cout << "mouseScroll dir =  " << dir << std::endl;
	if (dir > 0) { //zoom in
		DrawerVisitor::scale(1.1);
	} else { //zoom out
		DrawerVisitor::scale(0.9);
	}
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