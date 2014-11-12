#include "Controller.h"

float Controller::viewPositionX = 0.05f;
float Controller::viewPositionY = 0.05f;
float Controller::viewPositionZ = 0.05f;

float Controller::viewRotateX = 0.005f;
float Controller::viewRotateY = 0.005f;
float Controller::viewRotateZ = 0;

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
		DrawerVisitor::rotateModel(viewRotateY * (mouseYstart - y), viewRotateX * (mouseXstart - x), 0);
		glutPostRedisplay();
		mouseYstart = y;
		mouseXstart = x;
	}
}

void Controller::keyboardSpecialAction(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		DrawerVisitor::moveY(viewPositionY);
		break;
	case GLUT_KEY_DOWN:
		DrawerVisitor::moveY(-viewPositionY);
		break;
	case GLUT_KEY_RIGHT:
		DrawerVisitor::moveX(viewPositionX);
		break;
	case GLUT_KEY_LEFT:
		DrawerVisitor::moveX(-viewPositionX);
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