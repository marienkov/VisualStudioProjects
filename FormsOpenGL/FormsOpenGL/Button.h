#pragma once
#include "View.h"

class Button :
	public View
{
private:
	VertexCoord vertexData[6];
public:
	Button();
	Button(std::string name, int, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3, VertexCoord ver4);
	virtual ~Button();

	void setAllVer(VertexCoord, VertexCoord, VertexCoord, VertexCoord);
	void setVer1(VertexCoord);
	void setVer2(VertexCoord);
	void setVer3(VertexCoord);
	void setVer4(VertexCoord);

	float* getVertexDataArray();
	int getVertexDataArraySize();

	void accept(Visitor&);
};