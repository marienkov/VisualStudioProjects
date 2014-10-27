#pragma once
#include <string>
class Visitor;

class View
{
private:
	std::string id;
	int x, y;
	int width, height;
	int color;
public:
	View();
	View(std::string,int,int,int,int,int);
	virtual ~View();

	void setId(std::string);
	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);
	void setColor(int);

	virtual void accept(Visitor&);
};