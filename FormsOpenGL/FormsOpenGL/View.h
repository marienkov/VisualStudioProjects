#pragma once
#include <string>
class Visitor;

class View
{
public:
	struct VertexCoord {
	public:
		VertexCoord();
		VertexCoord(float, float, float);
		~VertexCoord();
		float data[3];
	};

	struct VertexColor {
	public:
		VertexColor();
		VertexColor(float, float, float, float);
		~VertexColor();
		float color[4];
	};

protected:
	std::string id;
	VertexColor vertexColor;
public:
	View();
	View(std::string);
	virtual void setId(std::string);
	virtual void setColor(float,float,float,float);
	virtual float* getVertexColorArray();
	virtual int getVertexColorArraySize();
	virtual void accept(Visitor&) = 0;
	virtual ~View();
};