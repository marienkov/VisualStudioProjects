#include "Controller.h"

Controller* Controller::instance = nullptr;

float Controller::viewPositionX = 0.05f;
float Controller::viewPositionY = 0.05f;
float Controller::viewPositionZ = 0.05f;

float Controller::viewRotateX = 0.005f;
float Controller::viewRotateY = 0.005f;
float Controller::viewRotateZ = 0;

float Controller::viewZoomIn = 1.1f;
float Controller::viewZoomOut = 0.9f;

int Controller::mouseXstart = 0;
int Controller::mouseYstart = 0;
int Controller::mouseXend = 0;
int Controller::mouseYend = 0;

bool Controller::mouseLeftRectangle2DPressed = false;

Controller::Controller() {
	instance = this;
}

Controller::~Controller() {
}

void Controller::setViewList(sViewList list) {
	viewList = list;
}

void Controller::mouseAction(int the_rectanlge, int rectanlge_state, int x, int y) {
	if (the_rectanlge == GLUT_LEFT_BUTTON && !rectanlge_state == GLUT_UP) {
		mouseLeftRectangle2DPressed = true;
	}
	else
		mouseLeftRectangle2DPressed = false;
}

void Controller::mouseMove(int x, int y) {
	if (mouseLeftRectangle2DPressed) {
		mouseXstart = x;
		mouseYstart = y;
		mouseLeftRectangle2DPressed = false;
	}
	else {
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->rotate(viewRotateY * (mouseYstart - y), viewRotateX * (mouseXstart - x), 0);
		glutPostRedisplay();
		mouseYstart = y;
		mouseXstart = x;
	}
}

void Controller::keyboardSpecialAction(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->move(0,viewPositionY,0);
		break;
	case GLUT_KEY_DOWN:
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->move(0, -viewPositionY, 0);
		break;
	case GLUT_KEY_RIGHT:
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->move(viewPositionX, 0, 0);
		break;
	case GLUT_KEY_LEFT:
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->move(-viewPositionX, 0, 0);
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void Controller::mouseScroll(int rectanlge, int dir, int x, int y) {
	if (dir > 0) {
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->scale(viewZoomIn, viewZoomIn, viewZoomIn);
	} else {
		for (std::list<sView>::iterator it = instance->viewList->begin(); it != instance->viewList->end(); ++it)
			it->get()->scale(viewZoomOut, viewZoomOut, viewZoomOut);
	}
	glutPostRedisplay();
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