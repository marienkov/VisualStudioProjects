#include <iostream>
#include "Parser.h"
#include <memory>

using namespace std;

char* fileName = "Form.xml";
std::list<std::string>  supportedViews;

void initSupportedViews();

int main() {
	initSupportedViews();

	Parser parser;
	parser.setSupportedViews(supportedViews);
	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList = parser.parse(fileName);

	system("pause");
	return 0;
}

void initSupportedViews() {
	supportedViews.push_back("<Rectangle>");
	supportedViews.push_back("<Triangle>");
}