#include "View.h"
#include "Visitor.h"


View::View()
{
}

View::View(std::string name) : id(name)
{
}

View::~View()
{
}

void View::setId(std::string id) {
	this->id = id;
}

void View::setColor(float alpha, float r, float g, float b){
	vertexColor.color[0] = r;
	vertexColor.color[1] = g;
	vertexColor.color[2] = b;
	vertexColor.color[3] = alpha;
}

float* View::getVertexColorArray() {
	return vertexColor.color;
}
int View::getVertexColorArraySize() {
	return sizeof(vertexColor);
}

View::VertexCoord::VertexCoord() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

View::VertexCoord::VertexCoord(float x, float y, float z){
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

View::VertexCoord::~VertexCoord() {

}

View::VertexColor::VertexColor() {
	color[0] = 1.0f;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

View::VertexColor::VertexColor(float alpha, float r, float g, float b){
	color[0] = alpha;
	color[1] = r;
	color[2] = g;
	color[3] = b;
}

View::VertexColor::~VertexColor(){
}