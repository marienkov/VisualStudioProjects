#pragma once
#include "Visitor.h"
#include "gl\glew.h"
#include "gl\freeglut.h"
#include "MVPMatrix4.h"

class DrawerVisitor :
	public Visitor
{
private:
	static DrawerVisitor* instance;

	GLint DrawerVisitor::Attrib_vertex;
	GLint DrawerVisitor::Unif_color;
	GLfloat DrawerVisitor::Unif_MVP;
	GLuint DrawerVisitor::Program;

	MVPMatrix4 MVP;
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

	static void moveX(float dx);
	static void moveY(float dy);
	static void scale(float s);

	static void rotate(float angleX, float angleY);
};

struct vertex {
	GLfloat x;
	GLfloat y;
};