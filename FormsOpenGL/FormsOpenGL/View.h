#pragma once
#include <string>

class View
{
private:
	std::string id;
	int x, y;
	int width, height;
public:
	View();
	View(std::string,int,int,int,int);
	virtual ~View();

	void setId(std::string);
	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);
};

