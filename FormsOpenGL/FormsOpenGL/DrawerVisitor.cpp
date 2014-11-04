#include "DrawerVisitor.h"

DrawerVisitor* DrawerVisitor::instance = nullptr;

DrawerVisitor::DrawerVisitor() : Attrib_vertex(0), Unif_color(0), Program(0)
{
	initShader();
	instance = this;
}


DrawerVisitor::~DrawerVisitor()
{
	freeShader();
}

void DrawerVisitor::visit(Button* button) {
	std::cout << "DrawerVisitor::visit(Button* button)" << std::endl;

	glUseProgram(Program);
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, button->getVertexDataArraySize(), button->getVertexDataArray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //buffer deactivation
	checkOpenGLerror();
	glUniformMatrix4fv(Unif_MVP, 1, GL_TRUE, MVP.getCurrentMVP4());

	glUniform4fv(Unif_color, 1, button->getVertexColorArray());
	checkOpenGLerror();
	glEnableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	checkOpenGLerror();
	glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkOpenGLerror();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkOpenGLerror();
	glDisableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glUseProgram(0);

	checkOpenGLerror();
	glutSwapBuffers();
	glFlush();  // Render now
}

void DrawerVisitor::visit(Triangle* triangle) {
	std::cout << "DrawerVisitor::visit(Triangle* triangle)" << std::endl;

	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, triangle->getVertexDataArraySize(), triangle->getVertexDataArray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //buffer deactivation
	checkOpenGLerror();

	glUseProgram(Program);
	glUniform4fv(Unif_color, 1, triangle->getVertexColorArray());
	checkOpenGLerror();
	glEnableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //free buffer
	checkOpenGLerror();
	glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkOpenGLerror();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	checkOpenGLerror();
	glDisableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glUseProgram(0);

	checkOpenGLerror();
	glutSwapBuffers();
	glFlush();  // Render now
}

void DrawerVisitor::initShader()
{
	std::cout << "initShader()" << std::endl;
	const char* vsSource =
		"attribute vec3 coord;\n"
		"uniform mat4 MVP;\n"
		"void main() {\n"
		"  gl_Position = MVP*vec4(coord, 1.0);\n"
		"}\n";
	const char* fsSource =
		"uniform vec4 color;\n"
		"void main() {\n"
		"  gl_FragColor = color;\n"
		"}\n";
	GLuint vShader, fShader;

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vsSource, NULL);
	glCompileShader(vShader);
	shaderLog(vShader);

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fsSource, NULL);
	glCompileShader(fShader);
	shaderLog(fShader);

	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);
	glLinkProgram(Program);

	int link_ok;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		std::cout << "error attach shaders \n";
		return;
	}

	///! Get ID of vertex attribute from already built program 
	const char* attr_name = "coord";
	Attrib_vertex = glGetAttribLocation(Program, attr_name);
	if (Attrib_vertex == -1) {
		std::cout << "could not bind attrib " << attr_name << std::endl;
		return;
	}
	//! Get ID of color attribute from already built program
	const char* unif_name = "color";
	Unif_color = glGetUniformLocation(Program, unif_name);
	if (Unif_color == -1) {
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}
	//! Get ID of MVP from already built program
	const char* MVP_name = "MVP";
	Unif_MVP = glGetUniformLocation(Program, MVP_name);
	if (Unif_MVP == -1) {
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}

	checkOpenGLerror();
}

void DrawerVisitor::checkOpenGLerror() {
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

void DrawerVisitor::shaderLog(unsigned int shader) {
	int   infologLen = 0;
	int   charsWritten = 0;
	char *infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << "ERROR: Could not allocate InfoLog buffer\n";
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}

void DrawerVisitor::freeShader()
{
	std::cout << "freeShader()" << std::endl;
	glDeleteProgram(Program);
	glUseProgram(0);
}

void DrawerVisitor::freeVBO()
{
	std::cout << "freeVBO()" << std::endl;
	//glDeleteBuffers(1, &VBO);
}

void DrawerVisitor::moveX(float dx) {
	instance->MVP.translateModel4({ dx, 0, 0, 0});
	//glutPostRedisplay();
}

void DrawerVisitor::moveY(float dy) {
	instance->MVP.translateModel4({ 0, dy, 0, 0 });
	//glutPostRedisplay();
}

void DrawerVisitor::scale(float s) {
	instance->MVP.scaleModel4({ s, s, s, 1 });
	glutPostRedisplay();
}