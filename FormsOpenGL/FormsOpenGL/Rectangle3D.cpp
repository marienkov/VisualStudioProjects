#include "Rectangle3D.h"
#include "Visitor.h"

Rectangle3D::Rectangle3D()
{
}

Rectangle3D::Rectangle3D(std::string name, int,
		VertexCoord ver1,  VertexCoord ver2,  VertexCoord ver3,  VertexCoord ver4,
		VertexCoord ver5,  VertexCoord ver6,  VertexCoord ver7,  VertexCoord ver8) {
	side[0].setAllVer(ver1, ver2, ver3, ver4);
	side[1].setAllVer(ver4, ver3, ver5, ver6);
	side[2].setAllVer(ver6, ver5, ver7, ver8);
	side[3].setAllVer(ver8, ver7, ver2, ver1);
	side[4].setAllVer(ver8, ver1, ver4, ver6);
	side[5].setAllVer(ver2, ver7, ver5, ver3);
}

Rectangle3D::~Rectangle3D()
{
}

void Rectangle3D::setAllVer(
		VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4,
		VertexCoord ver5, VertexCoord ver6, VertexCoord ver7, VertexCoord ver8) {
	side[0].setAllVer(ver1, ver2, ver3, ver4);
	side[1].setAllVer(ver4, ver3, ver5, ver6);
	side[2].setAllVer(ver6, ver5, ver7, ver8);
	side[3].setAllVer(ver8, ver7, ver2, ver1);
	side[4].setAllVer(ver8, ver1, ver4, ver6);
	side[5].setAllVer(ver2, ver7, ver5, ver3);
}

float* Rectangle3D::getSideVertexDataArray(int sideNumber) {
	return side[sideNumber].getVertexDataArray();
}

int Rectangle3D::getSideVertexDataArraySize() {
	return sizeof(side[0]) * 6;
}

void Rectangle3D::accept(Visitor& visitor) {
	visitor.visit(this);
}