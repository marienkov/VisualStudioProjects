#pragma once
#include <iostream>
class Button;
class Triangle;

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();

	virtual void visit(Button*) = 0;
	virtual void visit(Triangle*) = 0;
};