#include "View.h"
#include "Visitor.h"


View::View()
{
}

View::View(std::string name, int color) : id(name), col(color)
{
}

View::~View()
{
}

void View::setId(std::string id) {
	this->id = id;
}

void View::setColor(int color){
	col = color;
}

void View::accept(Visitor& visitor) {
	std::cout << "" << std::endl;
}

View::VertexCoord::VertexCoord() : x(0), y(0), z(0){
}

View::VertexCoord::VertexCoord(int x, int y, int z) : x(x), y(y), z(z){
}

View::VertexCoord::~VertexCoord(){
}