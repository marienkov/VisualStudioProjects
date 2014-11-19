#pragma once
#include <string>
#include <memory>
#include <list>
#include <iostream>
#include "Parser.h"
#include "DrawerVisitor.h"
#include "Controller.h"
#include "View.h"
#include "gl\glew.h"
#include "gl\freeglut.h"


typedef std::shared_ptr<View> sView;
typedef std::shared_ptr<std::list<sView>> sViewList;

class Engine
{
public:
	Engine();
	~Engine();
	void loadView(char* fileName);
	void initOpenGL(int argc1, char **argv1);
	void initLight();
	void initController();
	static void renderWrapper();
	void startRendering();
private:
	static Engine* instance;
	Controller controller;
	DrawerVisitor drawerVisitor;
	sViewList viewList;

	void render();
};