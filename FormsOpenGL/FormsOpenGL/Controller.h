#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "gl\glew.h"
#include "gl\freeglut.h"
#include "View.h"

typedef std::shared_ptr<View> sView;
typedef std::shared_ptr<std::list<sView>> sViewList;

class Controller
{
private:

	static Controller* instance;

	sViewList viewList;

	static float viewRotateX;
	static float viewRotateY;
	static float viewRotateZ;

	static float viewPositionX;
	static float viewPositionY;
	static float viewPositionZ;

	static float viewZoomIn;
	static float viewZoomOut;

	static bool mouseLeftButtonPressed;
	static int mouseXstart;
	static int mouseYstart;
	static int mouseXend;
	static int mouseYend;
public:
	Controller();
	virtual ~Controller();

	void setViewList(sViewList);

	static void mouseAction(int,int,int,int);
	static void mouseScroll(int, int, int, int);
	static void mouseMove(int, int);
	static void keyboardPressedAction(unsigned char key, int x, int y);
	static void keyboardSpecialAction(int, int, int);
	static void resizeWindow(int width, int height);
};

