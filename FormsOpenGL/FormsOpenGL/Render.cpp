#include "Render.h"

//Static initialization
Render* Render::instance = nullptr;

Render::Render() {
	instance = this;
}

Render::~Render() {
}

void Render::setViewList(std::shared_ptr<std::list<std::shared_ptr<View>>>& list) {
	viewList = list;
}

void Render::renderWrapper() {
	instance->render();
}

void Render::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static int i = 0;
	glPushMatrix();
	glRotatef(++i, 1, 0, 0);
	for (std::list<std::shared_ptr<View>>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}
	//glutSolidSphere(0.5, 20, 16);
	glPopMatrix();
	glLoadIdentity();
	
	glFlush();  // Render now*/
	glutSwapBuffers();
}