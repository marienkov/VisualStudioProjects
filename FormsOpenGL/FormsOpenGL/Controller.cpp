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
	}
	else {
		DrawerVisitor::rotateCamera(cameraRotateY * ( mouseYstart - y), cameraRotateX * (mouseXstart-x), 0);
		glutPostRedisplay();
		mouseYstart = y;
		mouseXstart = x;
	}
}

void Controller::keyboardSpecialAction(int key, int x, int y) {
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
	if (dir > 0) {
		DrawerVisitor::scale(1.1);
	} else {
		DrawerVisitor::scale(0.9);
	}
}

void Controller::keyboardPressedAction(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void Controller::resizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}