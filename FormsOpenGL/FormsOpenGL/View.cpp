﻿#include "View.h"
#include "Visitor.h"



View::View(std::string id, int positionCount, int vertexCount)
	: id(id), POSITION_COUNT(positionCount), VERTEX_COUNT(vertexCount),
	dx(0), dy(0), dz(0), angleX(0), angleY(0), angleZ(0), scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f) {
}

View::~View() {
}

void View::setId(std::string id) {
	this->id = id;
}

void View::setColor(float r, float g, float b, float alpha) {
	vertexColor.color[0] = r;
	vertexColor.color[1] = g;
	vertexColor.color[2] = b;
	vertexColor.color[3] = alpha;
}

//Check size of normal and position
//Calculation for one vertex could be applied for another????
// 1<--v3--3
// |      /
// v1    /
// |   v2
// |  /
// v /
// 2
//First vector
void View::computeNormalTriangle(int first, int second, int third) {
	float vec1x = (pVertexPosition + *(pVertexIndex + second))->position[0]
		- (pVertexPosition + *(pVertexIndex + first))->position[0];
	float vec1y = (pVertexPosition + *(pVertexIndex + second))->position[1]
		- (pVertexPosition + *(pVertexIndex + first))->position[1];
	float vec1z = (pVertexPosition + *(pVertexIndex + second))->position[2]
		- (pVertexPosition + *(pVertexIndex + first))->position[2];

	float vec2x = (pVertexPosition + *(pVertexIndex + third))->position[0]
		- (pVertexPosition + *(pVertexIndex + second))->position[0];
	float vec2y = (pVertexPosition + *(pVertexIndex + third))->position[1]
		- (pVertexPosition + *(pVertexIndex + second))->position[1];
	float vec2z = (pVertexPosition + *(pVertexIndex + third))->position[2]
		- (pVertexPosition + *(pVertexIndex + second))->position[2];

	float vec3x = (pVertexPosition + *(pVertexIndex + first))->position[0]
		- (pVertexPosition + *(pVertexIndex + third))->position[0];
	float vec3y = (pVertexPosition + *(pVertexIndex + first))->position[1]
		- (pVertexPosition + *(pVertexIndex + third))->position[1];
	float vec3z = (pVertexPosition + *(pVertexIndex + first))->position[2]
		- (pVertexPosition + *(pVertexIndex + third))->position[2];

	float nx1 = vec3y * vec1z - vec3z * vec1y;
	float ny1 = vec3z * vec1x - vec3x * vec1z;
	float nz1 = vec3x * vec1y - vec3y * vec1x;

	float nx2 = vec1y * vec2z - vec1z * vec2y;
	float ny2 = vec1z * vec2x - vec1x * vec2z;
	float nz2 = vec1x * vec2y - vec1y * vec2x;

	float nx3 = vec2y * vec3z - vec2z * vec3y;
	float ny3 = vec2z * vec3x - vec2x * vec3z;
	float nz3 = vec2x * vec3y - vec2y * vec3x;

	float n_mod = std::sqrt(nx1 * nx1 + ny1 * ny1 + nz1 * nz1)
		+ std::sqrt(nx2 * nx2 + ny2 * ny2 + nz2 * nz2)
		+ std::sqrt(nx3 * nx3 + ny3 * ny3 + nz3 * nz3);
	n_mod /= 3;

	(pVertexNormal + first)->normal[0] = nx1 / n_mod;
	(pVertexNormal + first)->normal[1] = ny1 / n_mod;
	(pVertexNormal + first)->normal[2] = nz1 / n_mod;

	(pVertexNormal + second)->normal[0] = nx2 / n_mod;
	(pVertexNormal + second)->normal[1] = ny2 / n_mod;
	(pVertexNormal + second)->normal[2] = nz2 / n_mod;

	(pVertexNormal + third)->normal[0] = nx3 / n_mod;
	(pVertexNormal + third)->normal[1] = ny3 / n_mod;
	(pVertexNormal + third)->normal[2] = nz3 / n_mod;
}

void View::initNormals() {
	for (int i = 0; i < VERTEX_COUNT; i += 3)
		computeNormalTriangle(i, i + 1, i + 2);
}

float* View::getVertexColors() {
	return (float*)(&vertexColor);
}

int View::getVertexColorSize(){
	return sizeof(vertexColor);
}

float* View::getVertexNormals() {
	return (float*)pVertexNormal;
}

int View::getVertexNoramlsSize(){
	return sizeof(*pVertexNormal) * VERTEX_COUNT;
}

int View::getVertexNormalsCount(){
	return VERTEX_COUNT;
}

const float* View::getVertexPosition() {
	return (float*)pVertexPosition;
}

int View::getVertexPositionSize(){
	return sizeof(*pVertexPosition) * POSITION_COUNT;
}

int View::getVertexPositionCount(){
	return POSITION_COUNT;
}

int* View::getVertexIndexes() {
	return pVertexIndex;
}

int View::getVertexIndexSize(){
	return sizeof(*pVertexIndex) * VERTEX_COUNT;
}

int View::getVertexIndexCount(){
	return VERTEX_COUNT;
}

float* View::getModelMatrixData() {
	modelMatrix = Matrix();
	modelMatrix.scale(scaleX, scaleY, scaleZ);
	modelMatrix.rotate(angleX, angleY, angleZ);
	modelMatrix.translate(dx,dy,dz);
	return modelMatrix.getData();
}

std::string View::getId() {
	return id;
}

void View::move(float x = 0, float y = 0, float z = 0) {
	dx += x;
	dy += y;
	dz += z;
}

void View::rotate(float angX = 0, float angY = 0, float angZ = 0) {
	angleX += angX;
	angleY += angY;
	angleZ += angZ;
}

void View::scale(float sx = 0, float sy = 0, float sz = 0) {
	scaleX *= sx;
	scaleY *= sy;
	scaleZ *= sz;
}

void View::updateVertexPosition(int vertex, VertexPosition position) {
	(pVertexPosition + vertex)->position[0] = position.position[0];
	(pVertexPosition + vertex)->position[1] = position.position[1];
	(pVertexPosition + vertex)->position[2] = position.position[2];
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