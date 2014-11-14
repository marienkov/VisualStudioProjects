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
	VertexColor vertexColor[4];
	VertexNormal vertexNormal[6];
	VertexPosition vertexPosition[4];
	int index[6];

	void initIndexes();
public:
	Button();
	Button(std::string name);
	virtual ~Button();

	void setCoordinates(VertexPosition v1, VertexPosition v2,
		VertexPosition v3, VertexPosition v4);
	
	void accept(Visitor&);
};