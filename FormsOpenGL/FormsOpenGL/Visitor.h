#pragma once
#include <iostream>
#include "Button.h"
#include "Triangle.h"

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();

	virtual void visit(Button*) = 0;
	virtual void visit(Triangle*) = 0;
};