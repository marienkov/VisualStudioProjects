#pragma once
#include <iostream>
#include "Button.h"
#include "Triangle.h"
#include "Rectangle3D.h"

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();

	virtual void visit(Button*) = 0;
	virtual void visit(Triangle*) = 0;
	virtual void visit(Rectangle3D*) = 0;
};