#pragma once
#include "View.h"

//   0
//  * *
// *   *
//1******2

class Triangle :
	public View
{
private:
	VertexColor vertexColor[3];
	VertexNormal vertexNormal[3];
	VertexPosition vertexPosition[3];
	int index[3];

	void initIndexes();
public:
	Triangle();
	Triangle(std::string name);
	virtual ~Triangle();

	void setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3);

	void accept(Visitor&);
};