#include "View.h"
#include "Visitor.h"


View::View()
{
}

View::View(std::string id, int x, int y, int width, int height, int color)
{
}

View::~View()
{
}

void View::setId(std::string id) {
	this->id = id;
}

void View::setX(int x){
	this->x = x;
}

void View::setY(int y ){
	this->y = y;
}

void View::setWidth(int width){
	this->width = width;
}

void View::setHeight(int height){
	this->height = height;
}

void View::setColor(int color){
	this->color = color;
}

void View::accept(Visitor& visitor) {
	std::cout << "" << std::endl;
}