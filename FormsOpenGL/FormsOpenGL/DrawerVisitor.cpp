#include "DrawerVisitor.h"

DrawerVisitor* DrawerVisitor::instance = nullptr;

DrawerVisitor::DrawerVisitor() : atrPosition(0), unifColor(1), atrNormal(3), unifMVP(0), program(0)
{
	instance = this;
}

DrawerVisitor::~DrawerVisitor()
{
	freeShader();
}

void DrawerVisitor::visit(Button* view) {
	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrPosition);
	glVertexAttribPointer(atrPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrNormal);
	glVertexAttribPointer(atrNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glUniformMatrix4fv(unifMVP, 1, GL_TRUE, view->getModelMatrixData());

	glUniform4fv(unifColor, 1, view->getVertexColors());

	glDrawElements(GL_TRIANGLES, view->getVertexIndexLenght(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(atrPosition);
	glDisableVertexAttribArray(atrNormal);

	glDeleteBuffers(1, &vId);
	glDeleteBuffers(1, &nId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::visit(Triangle* view) {
	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrPosition);
	glVertexAttribPointer(atrPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrNormal);
	glVertexAttribPointer(atrNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glUniformMatrix4fv(unifMVP, 1, GL_TRUE, view->getModelMatrixData());

	glUniform4fv(unifColor, 1, view->getVertexColors());

	glDrawElements(GL_TRIANGLES, view->getVertexIndexLenght(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(atrPosition);
	glDisableVertexAttribArray(atrNormal);

	glDeleteBuffers(1, &vId);
	glDeleteBuffers(1, &nId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::visit(Rectangle3D* view) {
	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrPosition);
	glVertexAttribPointer(atrPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(atrNormal);
	glVertexAttribPointer(atrNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glUniformMatrix4fv(unifMVP, 1, GL_TRUE, view->getModelMatrixData());

	glUniform4fv(unifColor, 1, view->getVertexColors());

	glDrawElements(GL_TRIANGLES, view->getVertexIndexLenght(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(atrPosition);
	glDisableVertexAttribArray(atrNormal);

	glDeleteBuffers(1, &vId);
	glDeleteBuffers(1, &nId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::initShader()
{
	const char* vsSource =
		"attribute vec3 coord;\n"
		"attribute vec3 norm;\n"
		"uniform mat4 MVP;\n"
		"varying vec3 N;\n"
		"varying vec3 v;\n"
		"void main() {\n"
		"  gl_Position = MVP * vec4(coord, 1.0);\n"
		"  N = vec3(MVP * vec4(norm, 1.0));\n"
		"  v = coord;"
		"}\n";
	const char* fsSource =
		"uniform vec4 color;\n"
		"varying vec3 N;"
		"varying vec3 v;"
		"void main() {\n"
		"  vec3 L = normalize(gl_LightSource[0].position.xyz - v);"
		"  vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N, L), 0.0);"
		"  Idiff = clamp(Idiff, 0.0, 1.0);"
		"  gl_FragColor = color + Idiff;\n"
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

	program = glCreateProgram();

	const char* attr_name = "coord";
	glBindAttribLocation(program, atrPosition, attr_name);

	attr_name = "norm";
	glBindAttribLocation(program, atrNormal, attr_name);

	attr_name = "color";
	glBindAttribLocation(program, unifColor, attr_name);

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	int link_ok;
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		std::cout << "error attach shaders \n";
		return;
	}

	attr_name = "MVP";
	unifMVP = glGetUniformLocation(program, attr_name);

	checkOpenGLerror();
	glUseProgram(program);
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
	glUseProgram(0);
	glDeleteProgram(program);
}