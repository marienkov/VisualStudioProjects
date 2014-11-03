#include "Button.h"
#include "Visitor.h"

Button::Button()
{
}

Button::Button(std::string name, int color, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4)
	: View(name)
{
	vertexData[0] = ver1;
	vertexData[1] = ver2;
	vertexData[2] = ver4;
	vertexData[3] = ver4;
	vertexData[4] = ver2;
	vertexData[5] = ver3;
}

Button::~Button()
{
}

void Button::setAllVer(VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4) {
	vertexData[0] = ver1;
	vertexData[1] = ver2;
	vertexData[2] = ver4;
	vertexData[3] = ver4;
	vertexData[4] = ver2;
	vertexData[5] = ver3;
}

void Button::setVer1(VertexCoord ver) {
	vertexData[0] = ver;
}

void Button::setVer2(VertexCoord ver) {
	vertexData[1] = ver;
	vertexData[4] = ver;
}

void Button::setVer3(VertexCoord ver) {
	vertexData[5] = ver;
}

void Button::setVer4(VertexCoord ver) {
	vertexData[2] = ver;
	vertexData[3] = ver;
}

float* Button::getVertexDataArray() {
	return (vertexData[0]).data;
}

int Button::getVertexDataArraySize() {
	return sizeof(vertexData) * 6;
}

void Button::accept(Visitor& visitor) {
	visitor.visit(this);
}