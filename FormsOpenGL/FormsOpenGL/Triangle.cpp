#include "Triangle.h"
#include "Visitor.h"

Triangle::Triangle()
	: View("") {
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	vertexCount = VERTEX_COUNT;
	indexCount = INDEX_COUNT;

	initIndexes();
}

Triangle::Triangle(std::string name)
	: View(name) {
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	vertexCount = VERTEX_COUNT;
	indexCount = INDEX_COUNT;

	initIndexes();
}

Triangle::~Triangle() {
}

void Triangle::initIndexes() {
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
}

void Triangle::setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3) {
	updateVertexPosition(0, v1);
	updateVertexPosition(1, v2);
	updateVertexPosition(2, v3);
	initNormals();
}

void Triangle::accept(Visitor& visitor) {
	visitor.visit(this);
}