#include "Engine.h"

//Static initialization
Engine* Engine::instance = nullptr;

Engine::Engine() {
	instance = this;
}

Engine::~Engine() {
}

void Engine::loadView(char* fileName) {
	Parser parser;
	viewList = parser.parse(fileName);
}

void Engine::initOpenGL(int argc1, char **argv1) {
	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(800, 400);
	glutInitWindowSize(600, 600);
	glutCreateWindow("FormsOpenGL");

	GLenum glew_status = glewInit();
	if (GLEW_OK != glew_status)
		throw std::runtime_error("glewInit failed");

	if (!GLEW_VERSION_2_0)
		throw std::runtime_error("GLEW_VERSION is not");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Enable transperancy
	glEnable(GL_BLEND);
	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	drawerVisitor.initShader();

	glutDisplayFunc(renderWrapper);
}

void Engine::initLight() {
	//Enable light
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 2000 };

	GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };
	GLfloat lightColor[] = { 1, 0, 0, 1 };

	glEnable(GL_COLOR_MATERIAL);

	//only for specular light
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess); //blik radius

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Engine::initController() {
	controller.setViewList(viewList);
	glutReshapeFunc(Controller::resizeWindow);
	glutMouseFunc(Controller::mouseAction);
	glutMotionFunc(Controller::mouseMove);
	glutSpecialFunc(Controller::keyboardSpecialAction);
	glutMouseWheelFunc(Controller::mouseScroll);
	glutKeyboardFunc(Controller::keyboardPressedAction);
}

void Engine::renderWrapper() {
	instance->render();
}

void Engine::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (std::list<sView>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}
	//glutSolidSphere(0.5, 20, 16);
	glFlush();
	glutSwapBuffers();
}

void Engine::startRendering() {
	glutMainLoop();
}