#include "Button.h"
#include "Visitor.h"

Button::Button()
{
}

Button::Button(std::string name, int color, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4)
	: View(name,color), v1(ver1), v2(ver2), v3(ver3), v4(ver4)
{
}

Button::~Button()
{
}

void Button::setAllVer(VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4) {
	v1 = ver1;
	v2 = ver2;
	v3 = ver3;
	v4 = ver4;
}

void Button::setVer1(VertexCoord ver) {
	v1 = ver;
}

void Button::setVer2(VertexCoord ver) {
	v2 = ver;
}

void Button::setVer3(VertexCoord ver) {
	v1 = ver;
}

void Button::setVer4(VertexCoord ver) {
	v1 = ver;
}

void Button::accept(Visitor& visitor) {
	visitor.visit(this);
}