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
	std::string id;

	int colorCount = 0;
	int normalCount = 0;
	int vertexCount = 0;
	int indexCount = 0;

	float dx = 0, dy = 0, dz = 0, angleX = 0, angleY = 0, angleZ = 0, scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;

	VertexColor* pVertexColor = nullptr;
	VertexNormal* pVertexNormal = nullptr;
	VertexPosition* pVertexPosition = nullptr;
	int* pVertexIndex = nullptr;

	Matrix modelMatrix;

	void initNormals();
	virtual void initIndexes() = 0;

	void computeNormalTriangle(int first, int second, int third);
public:
	View();
	View(std::string);
	virtual ~View();
	void setId(std::string);
	void setColor(float r, float g, float b, float alpha);

	float* getVertexColors();
	int getVertexColorSize();
	int getVertexColorLenght();

	float* getVertexNormals();
	int getVertexNoramlsSize();
	int getVertexNormalsLenght();

	float* getVertexPosition();
	int getVertexPositionSize();
	int getVertexPositionLenght();

	int* getVertexIndexes();
	int getVertexIndexSize();
	int getVertexIndexLenght();

	float* getModelMatrixData();

	void move(float x, float y, float z);
	void rotate(float angX, float angY, float angZ);
	void scale(float sx, float sy, float sz);

	void updateVertexPosition(int vertex, VertexPosition position);
	void updateVertexColor(int vertex, VertexColor color);

	virtual void accept(Visitor&) = 0;
};