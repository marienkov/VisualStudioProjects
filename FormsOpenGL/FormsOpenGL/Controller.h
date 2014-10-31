#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "gl\glew.h"
#include "gl\glut.h"
#include "View.h"

class Controller
{
private:
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
public:
	Controller();
	virtual ~Controller();

	void setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>);

	static void mouseAction(int,int,int,int);
	static void keyboardAction(unsigned char, int,int);
	static void resizeWindow(int width, int height);
};

