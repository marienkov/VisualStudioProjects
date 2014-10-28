#pragma once
#include <string>
#include <gl/glut.h>
#include <gl/glu.h>
#include <memory>
#include <list>
#include <iostream>
#include "DrawerVisitor.h"
#include "View.h"

class GlutRender
{
public:
	GlutRender(int argc, char **argv) : argc1(argc), argv1(argv){};
	~GlutRender();

	void initGlutWindow(int posX, int posY, int width, int height, std::string name);
	void startDrawing();
	void setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>& viewList);
private:
	int argc1;
	char **argv1;
	static DrawerVisitor drawerVisitor;
	static std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
	static void render();
	static void mouseAction(int the_button, int button_state, int x, int y);
	static void keyboardFunction(unsigned char key, int x, int y);
};

