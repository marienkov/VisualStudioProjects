#pragma once
#include "Button.h"
class Rectangle3D :
	public View
{
private:
	Button side[6];
public:
	Rectangle3D();
	Rectangle3D(std::string name, int,
		VertexCoord ver1,  VertexCoord ver2,  VertexCoord ver3,  VertexCoord ver4,
		VertexCoord ver5,  VertexCoord ver6,  VertexCoord ver7,  VertexCoord ver8);
	virtual ~Rectangle3D();

	void setAllVer(
		VertexCoord ver1,  VertexCoord ver2,  VertexCoord ver3,  VertexCoord ver4,
		VertexCoord ver5,  VertexCoord ver6,  VertexCoord ver7,  VertexCoord ver8);
	
	void setVer1(VertexCoord);
	void setVer2(VertexCoord);
	void setVer3(VertexCoord);
	void setVer4(VertexCoord);

	void setVer5(VertexCoord);
	void setVer6(VertexCoord);
	void setVer7(VertexCoord);
	void setVer8(VertexCoord);

	float* getSideVertexDataArray(int sideNumber);
	int getSideVertexDataArraySize();

	void accept(Visitor&);
};

