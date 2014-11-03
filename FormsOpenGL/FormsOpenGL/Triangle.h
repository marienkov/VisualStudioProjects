#pragma once
#include "View.h"
class Triangle :
	public View
{
private:
	VertexCoord vertexData[3];
public:
	Triangle();
	Triangle(std::string name, int, VertexCoord ver1, VertexCoord ver2, VertexCoord ver3);
	virtual ~Triangle();

	void setAllVer(VertexCoord, VertexCoord, VertexCoord);
	void setVer1(VertexCoord);
	void setVer2(VertexCoord);
	void setVer3(VertexCoord);

	float* getVertexDataArray();
	int getVertexDataArraySize();

	void accept(Visitor&);
};