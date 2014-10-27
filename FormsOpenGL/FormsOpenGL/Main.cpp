#include <iostream>
#include <memory>

#include "Parser.h"
#include "Visitor.h"
#include "DrawerVisitor.h"
#include "Button.h"

using namespace std;

char* fileName = "Form.xml";

void glutInitialization(int argc, char **argv);
void render(void);

int main(int argc, char **argv) {
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	Visitor* drawerVisitor = new DrawerVisitor();
	View* view = new Button();
	view->accept(*drawerVisitor);

	system("pause");
	return 0;
}