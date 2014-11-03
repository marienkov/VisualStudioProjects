#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "gl\glew.h"
#include "gl\freeglut.h"
#include "DrawerVisitor.h"

class Controller
{
private:
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;

	static float cameraPositionX;
	static float cameraPositionY;
	static float cameraPositionZ;

	static float cameraRotateY;
	static float cameraRotateX;
public:
	Controller();
	virtual ~Controller();

	void setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>);

	static void mouseAction(int,int,int,int);
	static void mouseScroll(int, int, int, int);
	static void keyboardPressedAction(unsigned char key, int x, int y);
	static void keyboardSpecialAction(int, int, int);
	static void resizeWindow(int width, int height);
};

