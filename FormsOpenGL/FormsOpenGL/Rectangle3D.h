#pragma once
#include "View.h"
class Rectangle3D :
	public View
{
private:
	VertexColor vertexColor[8];
	VertexNormal vertexNormal[36];
	VertexPosition vertexPosition[8];
	int index[36];

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