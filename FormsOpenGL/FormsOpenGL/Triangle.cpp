#include "Triangle.h"
#include "Visitor.h"

Triangle::Triangle()
{
}

Triangle::Triangle(std::string name, int color, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3)
	: View(name, color), v1(ver1), v2(ver2), v3(ver3)
{
}

Triangle::~Triangle()
{
}

void Triangle::setAllVer(VertexCoord ver1, VertexCoord ver2, VertexCoord ver3) {
	v1 = ver1;
	v2 = ver2;
	v3 = ver3;
}

void Triangle::setVer1(VertexCoord ver) {
	v1 = ver;
}

void Triangle::setVer2(VertexCoord ver) {
	v2 = ver;
}

void Triangle::setVer3(VertexCoord ver) {
	v1 = ver;
}

void Triangle::accept(Visitor& visitor) {
	visitor.visit(this);
}