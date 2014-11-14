#pragma once
#include <string>
#include <cmath>
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

	VertexColor* pVertexColor = nullptr;
	VertexNormal* pVertexNormal = nullptr;
	VertexPosition* pVertexPosition = nullptr;
	int* pVertexIndex = nullptr;

	void initNormals();
	virtual void initIndexes() = 0;

	void computeNormalTriangleIndex(int index);
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

	void updateVertexPosition(int vertex, VertexPosition position);
	void updateVertexColor(int vertex, VertexColor color);

	virtual void accept(Visitor&) = 0;
};