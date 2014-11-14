#include "Rectangle3D.h"
#include "Visitor.h"

Rectangle3D::Rectangle3D()
{
	pVertexColor = vertexColor;
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	colorCount = 8;
	normalCount = 36;
	vertexCount = 8;
	indexCount = 36;

	initIndexes();
}

Rectangle3D::Rectangle3D(std::string name) 
	: View(name) {
	pVertexColor = vertexColor;
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	colorCount = 8;
	normalCount = 36;
	vertexCount = 8;
	indexCount = 36;

	initIndexes();
}

Rectangle3D::~Rectangle3D()
{
}

void Rectangle3D::initIndexes() {
	index[0] = 0;   index[6] = 3;
	index[1] = 1;   index[7] = 2;
	index[2] = 2;   index[8] = 5;
	index[3] = 2;   index[9] = 5;
	index[4] = 3;   index[10] = 4;
	index[5] = 0;   index[11] = 3;

	index[12] = 4;   index[18] = 7;
	index[13] = 5;   index[19] = 6;
	index[14] = 6;   index[20] = 1;
	index[15] = 6;   index[21] = 1;
	index[16] = 7;   index[22] = 0;
	index[17] = 4;   index[23] = 7;

	index[24] = 7;   index[30] = 1;
	index[25] = 0;   index[31] = 6;
	index[26] = 3;   index[32] = 5;
	index[27] = 3;   index[33] = 5;
	index[28] = 4;   index[34] = 2;
	index[29] = 0;   index[35] = 6;
}

void Rectangle3D::setCoordinates(
		VertexPosition v1, VertexPosition v2,
		VertexPosition v3, VertexPosition v4,
		VertexPosition v5, VertexPosition v6,
		VertexPosition v7, VertexPosition v8) {
	updateVertexPosition(0, v1);
	updateVertexPosition(1, v2);
	updateVertexPosition(2, v3);
	updateVertexPosition(3, v4);
	updateVertexPosition(4, v5);
	updateVertexPosition(5, v6);
	updateVertexPosition(6, v7);
	updateVertexPosition(7, v8);
	//initNormals();
}

void Rectangle3D::accept(Visitor& visitor) {
	visitor.visit(this);
}