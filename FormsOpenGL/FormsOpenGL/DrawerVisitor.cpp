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

void DrawerVisitor::visit(Button* button) {
	glUseProgram(Program);
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, button->getVertexDataArraySize(), button->getVertexDataArray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkOpenGLerror();
	glUniformMatrix4fv(Unif_MVP, 1, GL_TRUE, MVP.getMVPTransform4()->getDataPointer());

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
	glDeleteBuffers(1, &VBO);
	checkOpenGLerror();
	glUseProgram(0);

	checkOpenGLerror();
}

void DrawerVisitor::visit(Triangle* triangle) {
	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, triangle->getVertexDataArraySize(), triangle->getVertexDataArray(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkOpenGLerror();

	glUseProgram(Program);
	glUniform4fv(Unif_color, 1, triangle->getVertexColorArray());
	checkOpenGLerror();
	glEnableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	checkOpenGLerror();
	glVertexAttribPointer(Attrib_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	checkOpenGLerror();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	checkOpenGLerror();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	checkOpenGLerror();
	glDisableVertexAttribArray(Attrib_vertex);
	checkOpenGLerror();
	glDeleteBuffers(1, &VBO);
	checkOpenGLerror();
	glUseProgram(0);

	checkOpenGLerror();
}

void DrawerVisitor::visit(Rectangle3D* rect3d) {
	GLuint VBO[6];
	glGenBuffers(6, VBO);

	for (int i = 0; i < 6; ++i) {
		glUseProgram(Program);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, rect3d->getSideVertexDataArraySize(), rect3d->getSideVertexDataArray(i), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		checkOpenGLerror();
		glUniformMatrix4fv(Unif_MVP, 1, GL_TRUE, MVP.getMVPTransform4()->getDataPointer());

		glUniform4fv(Unif_color, 1, rect3d->getVertexColorArray());
		checkOpenGLerror();
		glEnableVertexAttribArray(Attrib_vertex);
		checkOpenGLerror();
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
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
	}
	glDeleteBuffers(6, VBO);
	checkOpenGLerror();
}

void DrawerVisitor::initShader()
{
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
	glDeleteProgram(Program);
	glUseProgram(0);
}

void DrawerVisitor::moveX(float dx) {
	Matrix<float> transf = Matrix<float>(
		new float[16]{ 1, 0, 0, dx,
					   0, 1, 0, 0,
		   			   0, 0, 1, 0,
					   0, 0, 0, 1, }, 4, 4);
	instance->MVP.getModelTransfer4()->multiply(&transf);
}

void DrawerVisitor::moveY(float dy) {
	Matrix<float> transf = Matrix<float>(
		new float[16]{ 1, 0, 0, 0,
					   0, 1, 0, dy,
					   0, 0, 1, 0,
					   0, 0, 0, 1, }, 4, 4);
	instance->MVP.getModelTransfer4()->multiply(&transf);
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

void DrawerVisitor::rotateCamera(float dAngleX, float dAngleY, float dAngleZ) {
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