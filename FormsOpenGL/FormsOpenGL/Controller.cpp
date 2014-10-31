#include "Controller.h"


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

void Controller::keyboardAction(unsigned char key, int x, int y) {
	std::cout << "Key: " << key << "   X: " << x << "   Y: " << y << std::endl;
}

void Controller::resizeWindow(int width, int height)
{
	//std::cout << "glViewport(0, 0, width, height);" << std::endl;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.3, 0.6, -0.3, 0.3, -1., 1.);
}