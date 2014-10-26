#include <iostream>
#include "Parser.h"
#include <memory>

using namespace std;

char* fileName = "Form.xml";
std::list<std::string>  supportedViews;

int main() {
	Parser parser;
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	system("pause");
	return 0;
}