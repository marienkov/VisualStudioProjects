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
	glClear(GL_COLOR_BUFFER_BIT);
	for (std::list<std::shared_ptr<View>>::iterator it = viewList->begin(); it != viewList->end(); ++it) {
		it->get()->accept(drawerVisitor);
	}
}