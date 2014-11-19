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
	static const int VERTEX_COUNT = 3;
	static const int INDEX_COUNT = 3;

	VertexNormal vertexNormal[INDEX_COUNT];
	VertexPosition vertexPosition[VERTEX_COUNT];
	int index[INDEX_COUNT];

	void initIndexes();
public:
	Triangle();
	Triangle(std::string name);
	virtual ~Triangle();

	void setCoordinates(VertexPosition v1, VertexPosition v2, VertexPosition v3);

	void accept(Visitor&);
};