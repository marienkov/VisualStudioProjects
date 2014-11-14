#include "View.h"
#include "Visitor.h"


View::View()
{
}

View::View(std::string name) : id(name)
{
}

View::~View()
{
}

void View::setId(std::string id) {
	this->id = id;
}

void View::setColor(float r, float g, float b, float alpha) {
	for (int i = 0; i < colorCount; ++i) {
		(pVertexColor + i)->color[0] = r;
		(pVertexColor + i)->color[1] = g;
		(pVertexColor + i)->color[2] = b;
		(pVertexColor + i)->color[3] = alpha;
	}
}
//Check size of normal and position
void View::computeNormalTriangleIndex(int index) {
		//Next vector
		float lnx = (pVertexPosition + *(pVertexIndex + 1))->position[0] - (pVertexPosition + *(pVertexIndex))->position[0];
		float lny = (pVertexPosition + *(pVertexIndex + 1))->position[1] - (pVertexPosition + *(pVertexIndex))->position[1];
		float lnz = (pVertexPosition + *(pVertexIndex + 1))->position[2] - (pVertexPosition + *(pVertexIndex))->position[2];

		//Prev vector
		float lpx = (pVertexPosition + *(pVertexIndex))->position[0] - (pVertexPosition + *(pVertexIndex + 2))->position[0];
		float lpy = (pVertexPosition + *(pVertexIndex))->position[1] - (pVertexPosition + *(pVertexIndex + 2))->position[1];
		float lpz = (pVertexPosition + *(pVertexIndex))->position[2] - (pVertexPosition + *(pVertexIndex + 2))->position[2];

		float nx = lpy * lnz - lpz * lny;
		float ny = lpz * lnx - lpx * lnz;
		float nz = lpx * lny - lpy * lnx;

		float n_mod = std::sqrt(nx * nx + ny * ny + nz * nz);

		(pVertexNormal + index)->normal[0] = nx / n_mod;
		(pVertexNormal + index)->normal[1] = ny / n_mod;
		(pVertexNormal + index)->normal[2] = nz / n_mod;
}

void View::initNormals() {
	for (int i = 0; i < indexCount; ++i)
		computeNormalTriangleIndex(i);
}

float* View::getVertexColors() {
	return (float*)pVertexColor;
}

int View::getVertexColorSize(){
	return sizeof(*pVertexColor) * colorCount;
}

int View::getVertexColorLenght(){
	return colorCount;
}

float* View::getVertexNormals() {
	return (float*)pVertexNormal;
}

int View::getVertexNoramlsSize(){
	return sizeof(*pVertexNormal) * normalCount;
}

int View::getVertexNormalsLenght(){
	return normalCount;
}

float* View::getVertexPosition() {
	return (float*)pVertexPosition;
}

int View::getVertexPositionSize(){
	return sizeof(*pVertexPosition) * vertexCount;
}

int View::getVertexPositionLenght(){
	return vertexCount;
}

int* View::getVertexIndexes() {
	return pVertexIndex;
}

int View::getVertexIndexSize(){
	return sizeof(*pVertexIndex) * indexCount;
}

int View::getVertexIndexLenght(){
	return indexCount;
}

void View::updateVertexPosition(int vertex, VertexPosition position) {
	(pVertexPosition + vertex)->position[0] = position.position[0];
	(pVertexPosition + vertex)->position[1] = position.position[1];
	(pVertexPosition + vertex)->position[2] = position.position[2];
}

void View::updateVertexColor(int vertex, VertexColor color) {
	(pVertexColor + vertex)->color[0] = color.color[0];
	(pVertexColor + vertex)->color[1] = color.color[1];
	(pVertexColor + vertex)->color[2] = color.color[2];
	(pVertexColor + vertex)->color[3] = color.color[3];
}

View::VertexColor::VertexColor() {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

View::VertexColor::VertexColor(float r, float g, float b, float a) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

View::VertexColor::~VertexColor() {
}

View::VertexNormal::VertexNormal() {
	normal[0] = 0;
	normal[1] = 0;
	normal[2] = 0;
}

View::VertexNormal::VertexNormal(float nx, float ny, float nz) {
	normal[0] = nx;
	normal[1] = ny;
	normal[2] = nz;
}

View::VertexNormal::~VertexNormal() {
}

View::VertexPosition::VertexPosition() {
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
}

View::VertexPosition::VertexPosition(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

View::VertexPosition::~VertexPosition() {
}