#include "Triangle.h"
#include "Visitor.h"

Triangle::Triangle()
{

}

Triangle::Triangle(std::string name, int color, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3)
	: View(name) {
	vertexData[0] = ver1;
	vertexData[1] = ver2;
	vertexData[2] = ver3;
}

Triangle::~Triangle()
{
}

void Triangle::setAllVer(VertexCoord ver1, VertexCoord ver2, VertexCoord ver3) {
	vertexData[0] = ver1;
	vertexData[1] = ver2;
	vertexData[2] = ver3;
}

void Triangle::setVer1(VertexCoord ver) {
	vertexData[0] = ver;
}

void Triangle::setVer2(VertexCoord ver) {
	vertexData[1] = ver;
}

void Triangle::setVer3(VertexCoord ver) {
	vertexData[2] = ver;
}

float* Triangle::getVertexDataArray() {
	return (vertexData[0]).data;
}

int Triangle::getVertexDataArraySize() {
	return sizeof(vertexData) * 3;
}

void Triangle::accept(Visitor& visitor) {
	visitor.visit(this);
}