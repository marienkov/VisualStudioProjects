#pragma once
#include <string>
#include <memory>
#include <list>
#include <iostream>
#include "DrawerVisitor.h"
#include "View.h"
#include "gl\glew.h"
#include "gl\freeglut.h"

class Render
{
public:
	Render();
	~Render();

	void setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>& viewList);
	static void renderWrapper();
private:
	static Render* instance;
	DrawerVisitor drawerVisitor;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;

	void render();
};