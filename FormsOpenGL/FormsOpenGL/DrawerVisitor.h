#pragma once
#include "Visitor.h"

class DrawerVisitor :
	public Visitor
{
public:
	DrawerVisitor();
	virtual ~DrawerVisitor();

	void visit(Button*);
};