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

void DrawerVisitor::visit(Triangle* triangle) {
	std::cout << "DrawerVisitor::visit(Triangle* triangle)" << std::endl;
}