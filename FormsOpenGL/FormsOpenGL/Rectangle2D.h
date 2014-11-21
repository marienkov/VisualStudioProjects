#pragma once
#include "View.h"

// 0*********3
// *  *      *
// *     *   *
// 1*********2

class Rectangle2D :
	public View
{
protected:
	static const int POSITION_COUNT = 4;
	static const int VERTEX_COUNT = 6;

private:
	VertexNormal vertexNormal[VERTEX_COUNT];
	VertexPosition vertexPosition[POSITION_COUNT];
	int index[VERTEX_COUNT];

	void initIndexes();
public:
	Rectangle2D();
	Rectangle2D(std::string name);
	virtual ~Rectangle2D();

	void setCoordinates(VertexPosition v1, VertexPosition v2,
		VertexPosition v3, VertexPosition v4);
	
	void accept(Visitor&) ;
};