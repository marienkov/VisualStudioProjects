#include "Parser.h"
#include "View.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <typeinfo>

Parser::Parser() : viewList(new std::list<std::shared_ptr<View>>())
{
}


Parser::~Parser()
{
}

const std::shared_ptr<std::list<std::shared_ptr<View>>> Parser::parse(const char* fileName) {

	std::ifstream file(fileName);
	std::string currentLine;

	if (file.is_open()) {
		while (getline(file, currentLine)) {
			size_t start = currentLine.find_first_of(OPEN_START_TAG)+1;
			size_t end = currentLine.find_first_of(CLOSE_START_TAG);
			if (start != std::string::npos && end != std::string::npos && start < end) {
				std::string currentItem = currentLine.substr(start, end - start);
				View* v = nullptr;
				if ("Rectangle" == currentItem)
					v = new Rectangle();
				else if ("Triangle" == currentItem)
					v = new Triangle();
				else
					continue;
				//OPEN_END_TAG????
				while (getline(file, currentLine) && currentLine.find_first_of(OPEN_END_TAG) == std::string::npos)
				{
					size_t variablePositionStart = 0;
					size_t sizeOfLine = currentLine.size();
					for (std::string::iterator it = currentLine.begin(); it != currentLine.end(); ++it, ++variablePositionStart)
						if ('\ ' != *it)
							break;
					if (variablePositionStart >= sizeOfLine)
						break;

					size_t variablePositionEnd = currentLine.find_first_of(ASSING_MARK);
					size_t valuePositionStart = currentLine.find_first_of(VALUE_MARK)+1;
					size_t valuePositionEnd = currentLine.find_last_of(VALUE_MARK);
					if (variablePositionStart != std::string::npos && variablePositionEnd != std::string::npos
							&& variablePositionStart < variablePositionEnd
							&& valuePositionStart != std::string::npos && valuePositionEnd != std::string::npos
							&& valuePositionStart < valuePositionEnd) {
						std::string variable = currentLine.substr(variablePositionStart, variablePositionEnd - variablePositionStart);
						std::string value = currentLine.substr(valuePositionStart, valuePositionEnd - valuePositionStart);
						if ("id" == variable)
							v->setId(value);
						if ("x" == variable)
							v->setX(std::stoi(value));
						if ("y" == variable)
							v->setY(std::stoi(value));
						if ("width" == variable)
							v->setWidth(std::stoi(value));
						if ("height" == variable)
							v->setHeight(std::stoi(value));
					}
				}
				viewList->push_back(std::shared_ptr<View>(v));
			}
			std::cout << currentLine << std::endl;
		}
	}

	file.close();

	return viewList;
}