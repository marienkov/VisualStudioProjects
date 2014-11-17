#include "Render.h"

//Static initialization
Render* Render::instance = nullptr;

Render::Render() {
	instance = this;
}

Render::~Render() {
}

void Render::setViewList(sViewList& list) {
	viewList = list;
}

void Render::renderWrapper() {
	instance->render();
}

void Render::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (std::list<sView>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}
	//glutSolidSphere(0.5, 20, 16);
	glFlush();
	glutSwapBuffers();
}