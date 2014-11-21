#pragma once
#include <string>
#include "Matrix.h"
class Visitor;

class View
{
public:
	struct VertexColor {
	public:
		VertexColor();
		VertexColor(float r, float g, float b, float a);
		~VertexColor();
		float color[4];
	};

	struct VertexNormal {
	public:
		VertexNormal();
		VertexNormal(float nx, float ny, float nz);
		~VertexNormal();
		float normal[3];
	};

	struct VertexPosition {
	public:
		VertexPosition();
		VertexPosition(float x, float y, float z);
		~VertexPosition();
		float position[3];
	};

protected:
	const int POSITION_COUNT;
	const int VERTEX_COUNT;

	std::string id;

	float dx, dy, dz, angleX, angleY, angleZ, scaleX, scaleY, scaleZ;

	VertexColor vertexColor;
	VertexNormal* pVertexNormal;
	VertexPosition* pVertexPosition;
	int* pVertexIndex;

	Matrix modelMatrix;

	void initNormals();
	virtual void initIndexes() = 0;

	void computeNormalTriangle(int first, int second, int third);
public:
	View(std::string id, int positionCount, int vertexCount);

	virtual ~View();
	void setId(std::string);
	void setColor(float r, float g, float b, float alpha);

	float* getVertexColors();
	int getVertexColorSize();
	int getVertexColorCount();

	float* getVertexNormals();
	int getVertexNoramlsSize();
	int getVertexNormalsCount();

	const float* getVertexPosition();
	int getVertexPositionSize();
	int getVertexPositionCount();

	int* getVertexIndexes();
	int getVertexIndexSize();
	int getVertexIndexCount();

	float* getModelMatrixData();

	std::string getId();

	void move(float x, float y, float z);
	void rotate(float angX, float angY, float angZ);
	void scale(float sx, float sy, float sz);

	void updateVertexPosition(int vertex, VertexPosition position);

	virtual void accept(Visitor&) = 0;
};