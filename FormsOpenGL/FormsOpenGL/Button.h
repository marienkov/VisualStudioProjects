#pragma once
#include "View.h"

// 0*********3
// *  *      *
// *     *   *
// 1*********2

class Button :
	public View
{
private:
	static const int VERTEX_COUNT = 4;
	static const int INDEX_COUNT = 6;

	VertexNormal vertexNormal[INDEX_COUNT];
	VertexPosition vertexPosition[VERTEX_COUNT];
	int index[INDEX_COUNT];

	void initIndexes();
public:
	Button();
	Button(std::string name);
	virtual ~Button();

	void setCoordinates(VertexPosition v1, VertexPosition v2,
		VertexPosition v3, VertexPosition v4);
	
	void accept(Visitor&) ;
};