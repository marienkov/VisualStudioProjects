#pragma once
#include <string>
#include <memory>
#include <list>
#include <iostream>
#include "DrawerVisitor.h"
#include "View.h"
#include "gl\glew.h"
#include "gl\freeglut.h"

typedef std::shared_ptr<View> sView;
typedef std::shared_ptr<std::list<sView>> sViewList;

class Render
{
public:
	Render();
	~Render();

	void setViewList(sViewList& viewList);
	static void renderWrapper();
private:
	static Render* instance;
	DrawerVisitor drawerVisitor;
	sViewList viewList;

	void render();
};