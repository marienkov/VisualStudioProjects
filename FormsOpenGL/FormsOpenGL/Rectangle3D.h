#pragma once
#include "View.h"
class Rectangle3D :
	public View
{
protected:
	static const int POSITION_COUNT = 8;
	static const int VERTEX_COUNT = 36;

private:
	VertexNormal vertexNormal[VERTEX_COUNT];
	VertexPosition vertexPosition[POSITION_COUNT];
	int index[VERTEX_COUNT];

	void initIndexes();
public:
	Rectangle3D();
	Rectangle3D(std::string name);
	virtual ~Rectangle3D();

	void setCoordinates(
		VertexPosition v1, VertexPosition v2,
		VertexPosition v3, VertexPosition v4,
		VertexPosition v5, VertexPosition v6,
		VertexPosition v7, VertexPosition v8);
	
	void accept(Visitor&);
};