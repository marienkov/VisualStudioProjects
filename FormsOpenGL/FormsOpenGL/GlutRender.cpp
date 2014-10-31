#include "GlutRender.h"

//Static initialization
DrawerVisitor GlutRender::drawerVisitor;
std::shared_ptr<std::list<std::shared_ptr<View>>> GlutRender::viewList;
GLuint GlutRender::Program = 0;
GLint GlutRender::Attrib_vertex = 0;
GLint GlutRender::Unif_color = 0;
GLuint GlutRender::VBO = 0;


GlutRender::~GlutRender() {
}

void GlutRender::startDrawing() {
	glutMainLoop();
}

void GlutRender::setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>& viewList) {
	this->viewList = viewList;
}

void GlutRender::mouseAction(int the_button, int button_state, int x, int y) {
	std::cout << "X: " << x << "   Y: " << y << std::endl;
}

void GlutRender::keyboardFunction(unsigned char key, int x, int y) {
	std::cout << "Key: " << key << "   X: " << x << "   Y: " << y << std::endl;
}

int GlutRender::initGlutWindow(int posX, int posY, int width, int height, std::string name) {
	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(width, height);
	glutCreateWindow(name.c_str());

	//! Before shader initialization
	GLenum glew_status = glewInit();
	if (GLEW_OK != glew_status)
	{
		//! GLEW is not initialized
		std::cout << "Error: " << glewGetErrorString(glew_status) << "\n";
		return 1;
	}

	//! Check OpenGL 2.0
	if (!GLEW_VERSION_2_0)
	{
		std::cout << "No support for OpenGL 2.0 found\n";
		return 1;
	}

	//! Initialization
	initGL();
	initVBO();
	initShader();

	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(render);
	//glutMouseFunc(mouseAction);
	//glutKeyboardFunc(keyboardFunction);

	return 0;
}

void GlutRender::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	//! Set current shader program
	glUseProgram(Program);
	float red[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
	//! Send uniform to shader
	glUniform4fv(Unif_color, 1, red);
	//! Enabling attribute array
	glEnableVertexAttribArray(Attrib_vertex);
	//! Enable VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//! 
	glVertexAttribPointer(Attrib_vertex, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//! Disable VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//! Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//! Disable attribute array
	glDisableVertexAttribArray(Attrib_vertex);

	//! Disable shader programs
	glUseProgram(0);

	checkOpenGLerror();
	glutSwapBuffers();

	glFlush();  // Render now

	/*for (std::list<std::shared_ptr<View>>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}*/
}

//! Logs for shaders
void GlutRender::shaderLog(unsigned int shader) {
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

//! Chech OpenGL errors, if it presents - send to log
void GlutRender::checkOpenGLerror() {
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}

// Init GL
void GlutRender::initGL() {
	glClearColor(1,0,0,0);

	std::cout << "InitGL()" << std::endl;
}

//! Shader initialization
void GlutRender::initShader()
{
	std::cout << "initShader()" << std::endl;
	//Shader's soource code
	const char* vsSource =
		"attribute vec2 coord;\n"
		"void main() {\n"
		"  gl_Position = vec4(coord, 0.0, 1.0);\n"
		"}\n";
	const char* fsSource =
		"uniform vec4 color;\n"
		"void main() {\n"
		"  gl_FragColor = color;\n"
		"}\n";
	//! Variable for storing shaders id
	GLuint vShader, fShader;

	//! Create Vertex shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//! Transfer source code
	glShaderSource(vShader, 1, &vsSource, NULL);
	//! Compile shader
	glCompileShader(vShader);

	std::cout << "vertex shader \n";
	shaderLog(vShader);

	//! Create Fragment shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//! Transfer source code
	glShaderSource(fShader, 1, &fsSource, NULL);
	//! Compile shader
	glCompileShader(fShader);

	std::cout << "fragment shader \n";
	shaderLog(fShader);

	//! Create program and add shaders to it
	Program = glCreateProgram();
	glAttachShader(Program, vShader);
	glAttachShader(Program, fShader);

	//! Link shader program
	glLinkProgram(Program);

	//! Check program build status
	int link_ok;
	glGetProgramiv(Program, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		std::cout << "error attach shaders \n";
		return;
	}
	///! Get ID of vertex attribute from already built program 
	const char* attr_name = "coord";
	Attrib_vertex = glGetAttribLocation(Program, attr_name);
	if (Attrib_vertex == -1)
	{
		std::cout << "could not bind attrib " << attr_name << std::endl;
		return;
	}
	//! Get ID of color attribute from already built program
	const char* unif_name = "color";
	Unif_color = glGetUniformLocation(Program, unif_name);
	if (Unif_color == -1)
	{
		std::cout << "could not bind uniform " << unif_name << std::endl;
		return;
	}

	checkOpenGLerror();
}

//! Init Vertex Buffer Object(VBO)
void GlutRender::initVBO()
{
	std::cout << "initVBO()" << std::endl;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	vertex triangle[3] = {
			{ -1.0f, -1.0f },
			{ 0.0f, 1.0f },
			{ 1.0f, -1.0f }
	};
	// Put Vertex in VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //buffer deactivation
	checkOpenGLerror();
}

//! Free shaders
void GlutRender::freeShader()
{
	std::cout << "freeShader()" << std::endl;
	//! Disable shader program
	glUseProgram(0);
	//! Delete shader program
	glDeleteProgram(Program);
}

//! Free VBO
void GlutRender::freeVBO()
{
	std::cout << "freeVBO()" << std::endl;
	glDeleteBuffers(1, &VBO);
}

void GlutRender::resizeWindow(int width, int height)
{
	//std::cout << "glViewport(0, 0, width, height);" << std::endl;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.3, 0.6, -0.3, 0.3, -1., 1.);
}