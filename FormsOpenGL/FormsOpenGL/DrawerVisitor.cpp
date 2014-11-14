#include "DrawerVisitor.h"

DrawerVisitor* DrawerVisitor::instance = nullptr;

DrawerVisitor::DrawerVisitor() : Attrib_vertex(0), Unif_color(0), Program(0), scaleFactor(1), angleX(0), angleY(0), angleZ(0)
{
	initShader();
	instance = this;
}

DrawerVisitor::~DrawerVisitor()
{
	freeShader();
}

void DrawerVisitor::visit(Button* view) {
	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glGenBuffers(1, &cId);
	glBindBuffer(GL_ARRAY_BUFFER, cId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexColorSize(), view->getVertexColors(), GL_STATIC_DRAW);
	glColorPointer(4, GL_FLOAT, 0, 0);

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDeleteBuffers(1, &vId);
	glDeleteBuffers(1, &cId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::visit(Triangle* view) {
	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glGenBuffers(1, &cId);
	glBindBuffer(GL_ARRAY_BUFFER, cId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexColorSize(), view->getVertexColors(), GL_STATIC_DRAW);
	glColorPointer(4, GL_FLOAT, 0, 0);

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDeleteBuffers(1, &vId);
	glDeleteBuffers(1, &cId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::visit(Rectangle3D* view) {
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.1f,
		0.8f, -0.5f, -0.5f,
		0.0f, 0.5f, 0.7f
	};
	static const GLfloat color[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
	};

	static const unsigned int normals[] = {
		0.0f, 0.5f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.1f,
	};
	static const unsigned int index[] = {
		0, 1, 2 };

	GLuint vId = 0, iId = 0, cId = 0, nId = 0;

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glGenBuffers(1, &vId);
	glBindBuffer(GL_ARRAY_BUFFER, vId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexPositionSize(), view->getVertexPosition(), GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	/*glGenBuffers(1, &cId);
	glBindBuffer(GL_ARRAY_BUFFER, cId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexColorSize(), view->getVertexColors(), GL_STATIC_DRAW);
	glColorPointer(4, GL_FLOAT, 0, 0);*/

	glGenBuffers(1, &nId);
	glBindBuffer(GL_ARRAY_BUFFER, nId);
	glBufferData(GL_ARRAY_BUFFER, view->getVertexNoramlsSize(), view->getVertexNormals(), GL_STATIC_DRAW);
	glNormalPointer(GL_FLOAT, 0, 0);

	glGenBuffers(1, &iId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, view->getVertexIndexSize(), view->getVertexIndexes(), GL_STATIC_DRAW);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDeleteBuffers(1, &vId);
	//glDeleteBuffers(1, &cId);
	glDeleteBuffers(1, &iId);
}

void DrawerVisitor::initShader()
{
	const char* vsSource =
		"attribute vec3 coord;\n"
		"uniform mat4 MVP;\n"
		"void main() {\n"
		"  gl_Position = vec4(coord, 1.0);\n"
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

	const char* attr_name = "coord";
	Attrib_vertex = glGetAttribLocation(Program, attr_name);
	if (Attrib_vertex == -1) {
		std::cout << "could not bind attrib " << attr_name << std::endl;
		return;
	}

	const char* unif_name = "color";
	Unif_color = glGetUniformLocation(Program, unif_name);
	if (Unif_color == -1) {
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}

	const char* MVP_name = "MVP";
	Unif_MVP = glGetUniformLocation(Program, MVP_name);
	if (Unif_MVP == -1) {
		std::cout << "could not bind uniform " << MVP_name << std::endl;
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
	glDeleteProgram(Program);
	glUseProgram(0);
}

void DrawerVisitor::moveX(float dx) {
	Matrix<float> transf = Matrix<float>(
		new float[16]{ 1, 0, 0, dx,
					   0, 1, 0, 0,
		   			   0, 0, 1, 0,
					   0, 0, 0, 1, }, 4, 4);
	instance->MVP.getModelTranslate4()->multiply(&transf);
}

void DrawerVisitor::moveY(float dy) {
	Matrix<float> transf = Matrix<float>(
		new float[16]{ 1, 0, 0, 0,
					   0, 1, 0, dy,
					   0, 0, 1, 0,
					   0, 0, 0, 1, }, 4, 4);
	instance->MVP.getModelTranslate4()->multiply(&transf);
}

void DrawerVisitor::scale(float s) {
	instance->scaleFactor *= s;
	float *scale = new float[16]{
		instance->scaleFactor, 0, 0, 0,
		0, instance->scaleFactor, 0, 0,
		0, 0, instance->scaleFactor, 0, 
		0, 0, 0, 1, };
	instance->MVP.getModelScaling4()->reset(scale, 4, 4);
	glutPostRedisplay();
}

void DrawerVisitor::rotateModel(float dAngleX, float dAngleY, float dAngleZ) {
	instance->angleX += dAngleX;
	instance->angleY += dAngleY;
	instance->angleZ += dAngleZ;

	Matrix<float> rotateX = Matrix<float>(
		new float[16]{
		1, 0,					   0,                     0,
		0, cos(instance->angleX), -sin(instance->angleX), 0,
		0, sin(instance->angleX),  cos(instance->angleX), 0,
		0, 0,					   0,                     1 },4, 4);
	Matrix<float> rotateY = Matrix<float>(
		new float[16]{
		cos(instance->angleY), 0, sin(instance->angleY), 0,
		0,					   1, 0,			         0,
		-sin(instance->angleY),0, cos(instance->angleY), 0,
		0,					   0, 0,					 1 }, 4, 4);
	Matrix<float> rotateZ = Matrix<float>(
		new float[16]{
		cos(instance->angleZ), -sin(instance->angleZ), 0, 0,
		sin(instance->angleZ), cos(instance->angleZ),  0, 0,
		0,					   0,				       1, 0,
		0,					   0,                      0, 1 }, 4, 4);
		instance->MVP.getModelRotating4()->loadIdentityMatrix();
		instance->MVP.getModelRotating4()->multiply(rotateX)->multiply(rotateY)->multiply(rotateZ);
}