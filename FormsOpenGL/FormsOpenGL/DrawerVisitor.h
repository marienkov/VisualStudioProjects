#pragma once
#include "Visitor.h"
#include "gl\glew.h"
#include "gl\glut.h"

class DrawerVisitor :
	public Visitor
{
private:
	GLint DrawerVisitor::Attrib_vertex;
	GLint DrawerVisitor::Unif_color;
	GLuint DrawerVisitor::Program;
public:
	DrawerVisitor();
	virtual ~DrawerVisitor();

	void visit(Button*);
	void visit(Triangle*);

	void initShader();
	void checkOpenGLerror();
	void shaderLog(unsigned int shader);
	void DrawerVisitor::freeShader();
	void DrawerVisitor::freeVBO();
};

struct vertex {
	GLfloat x;
	GLfloat y;
};