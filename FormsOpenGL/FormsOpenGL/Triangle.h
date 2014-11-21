#pragma once
#include "View.h"

//   0
//  * *
// *   *
//1******2

class Triangle :
	public View
{
protected:
	static const int POSITION_COUNT = 3;
	static const int VERTEX_COUNT = 3;

private:
	VertexNormal vertexNormal[VERTEX_COUNT];
	VertexPosition vertexPosition[POSITION_COUNT];
	int index[VERTEX_COUNT];

	void initIndexes();
public:
	Triangle();
	Triangle(std::string name);
	virtual ~Triangle();

	void setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3);

	void accept(Visitor&);
};