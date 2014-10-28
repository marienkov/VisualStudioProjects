#include "GlutRender.h"

DrawerVisitor GlutRender::drawerVisitor;
std::shared_ptr<std::list<std::shared_ptr<View>>> GlutRender::viewList;

GlutRender::~GlutRender()
{
}

void GlutRender::initGlutWindow(int posX, int posY, int width, int height, std::string name) {
	glutInit(&argc1, argv1);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(width, height);
	glutCreateWindow(name.c_str());
	glutDisplayFunc(render);
	glutMouseFunc(mouseAction);
	glutKeyboardFunc(keyboardFunction);
}

void GlutRender::startDrawing() {
	glutMainLoop();
}

void GlutRender::setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>& viewList) {
	this->viewList = viewList;
}

void GlutRender::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.8, -0.8, 0.0);
	glVertex3f(0.8, -0.8, 0.0);
	glVertex3f(0.8, 0.8, 0.0);
	glVertex3f(-0.8, 0.8, 0.0);
	glEnd();
	glFlush();
	for (std::list<std::shared_ptr<View>>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}
}

void GlutRender::mouseAction(int the_button, int button_state, int x, int y){
	std::cout << "X: " << x << "   Y: " << y << std::endl;
}

void GlutRender::keyboardFunction(unsigned char key, int x, int y){
	std::cout << "Key: " << key << "   X: " << x << "   Y: " << y << std::endl;
}