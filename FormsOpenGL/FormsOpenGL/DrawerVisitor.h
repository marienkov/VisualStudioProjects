#pragma once
#include "Visitor.h"
#include "gl\glew.h"
#include "gl\freeglut.h"

class DrawerVisitor :
	public Visitor
{
private:
	static DrawerVisitor* instance;

	GLint DrawerVisitor::atrPosition;
	GLint DrawerVisitor::atrNormal;
	GLint DrawerVisitor::unifColor;
	GLfloat DrawerVisitor::unifMVP;
	GLuint DrawerVisitor::program;
public:
	DrawerVisitor();
	virtual ~DrawerVisitor();

	void visit(Rectangle2D*);
	void visit(Triangle*);
	void visit(Rectangle3D*);

	void initShader();
	void checkOpenGLerror();
	void shaderLog(unsigned int shader);
	void DrawerVisitor::freeShader();
	void DrawerVisitor::freeVBO();
};