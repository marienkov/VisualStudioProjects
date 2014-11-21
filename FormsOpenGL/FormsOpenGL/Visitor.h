#pragma once
#include <iostream>
#include "Rectangle2D.h"
#include "Triangle.h"
#include "Rectangle3D.h"

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();

	virtual void visit(Rectangle3D*) = 0;
	virtual void visit(Triangle*) = 0;
	virtual void visit(Rectangle2D*) = 0;
};