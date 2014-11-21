#include "Rectangle2D.h"
#include "Visitor.h"

Rectangle2D::Rectangle2D()
	: View("", POSITION_COUNT, VERTEX_COUNT) {
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	initIndexes();
}

Rectangle2D::Rectangle2D(std::string name)
	: View(name, POSITION_COUNT, VERTEX_COUNT) {
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	initIndexes();
}

Rectangle2D::~Rectangle2D() {
}

void Rectangle2D::initIndexes() {
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 2;
	index[4] = 3;
	index[5] = 0;
}

void Rectangle2D::setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3, VertexPosition v4) {
	updateVertexPosition(0, v1);
	updateVertexPosition(1, v2);
	updateVertexPosition(2, v3);
	updateVertexPosition(3, v4);
	initNormals();
}

void Rectangle2D::accept(Visitor& visitor) {
	visitor.visit(this);
}