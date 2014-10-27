#pragma once
#include <iostream>
class Button;

class Visitor
{
public:
	Visitor();
	virtual ~Visitor();

	virtual void visit(Button*) = 0;
};