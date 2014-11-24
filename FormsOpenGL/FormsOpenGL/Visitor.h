#pragma once
#include <iostream>
#include "Rectangle2D.h"
#include "Triangle.h"
#include "Rectangle3D.h"

class Visitor
{
public:
	Visitor() {};
	virtual ~Visitor() {};

	virtual void visit(View*) = 0;
};