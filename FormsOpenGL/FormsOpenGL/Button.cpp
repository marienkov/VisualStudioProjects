#include "Button.h"
#include "Visitor.h"

Button::Button()
{
	pVertexColor = vertexColor;
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	colorCount = 4;
	normalCount = 6;
	vertexCount = 4;
	indexCount = 6;

	initIndexes();
}

Button::Button(std::string name)
	: View(name)
{
	pVertexColor = vertexColor;
	pVertexNormal = vertexNormal;
	pVertexPosition = vertexPosition;
	pVertexIndex = index;

	colorCount = 4;
	normalCount = 6;
	vertexCount = 4;
	indexCount = 6;

	initIndexes();
}

Button::~Button()
{
}

void Button::initIndexes() {
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 2;
	index[4] = 3;
	index[5] = 0;
}

void Button::setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3, VertexPosition v4) {
	updateVertexPosition(0, v1);
	updateVertexPosition(1, v2);
	updateVertexPosition(2, v3);
	updateVertexPosition(3, v4);
	initNormals();
}

void Button::accept(Visitor& visitor) {
	visitor.visit(this);
}