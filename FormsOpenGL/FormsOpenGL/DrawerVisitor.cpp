#include "DrawerVisitor.h"


DrawerVisitor::DrawerVisitor()
{
}


DrawerVisitor::~DrawerVisitor()
{
}

void DrawerVisitor::visit(Button* button) {
	std::cout << "DrawerVisitor::visit(Button* button)" << std::endl;
}