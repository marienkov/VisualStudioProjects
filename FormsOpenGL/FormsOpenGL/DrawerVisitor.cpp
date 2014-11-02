#include "DrawerVisitor.h"

DrawerVisitor::DrawerVisitor() : Attrib_vertex(0), Unif_color(0), Program(0)
{
	initShader();
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
	vertex rect[6] = {
			{ 0.5f, -0.5f },
			{ 0.5f, 0.5f },
			{ -0.5f, -0.5f },
			{ 0.5f, 0.5f },
			{ -0.5f, 0.5f },
			{ -0.5f, -0.5f }
	};
	float green[4] = { 0.5f, 1.0f, 0.0f, 0.5f };
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //buffer deactivation
	checkOpenGLerror();

	glUniform4fv(Unif_color, 1, green);
	checkOpenGLerror();
	glEnableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	checkOpenGLerror();
	glVertexAttribPointer(Attrib_vertex, 2, GL_FLOAT, GL_FALSE, 0, 0);
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
	vertex trian[3] = {
			{ -0.7f, -0.7f },
			{ 0.0f, 0.7f },
			{ 0.7f, -0.7f }
	};
	float red[4] = { 0.5f, 0.0f, 1.0f, 0.5f };
	glBufferData(GL_ARRAY_BUFFER, sizeof(trian), trian, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //buffer deactivation
	checkOpenGLerror();

	glUseProgram(Program);
	glUniform4fv(Unif_color, 1, red);
	checkOpenGLerror();
	glEnableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	checkOpenGLerror();
	glVertexAttribPointer(Attrib_vertex, 2, GL_FLOAT, GL_FALSE, 0, 0);
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
		"attribute vec2 coord;\n"
		"void main() {\n"
		"  gl_Position = gl_ModelViewProjectionMatrix*vec4(coord, 0.0, 1.0);\n"
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