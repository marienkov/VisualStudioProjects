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
		View* v = nullptr;
		while (getline(file, currentLine)) {
			int start = -1;
			int end = -1;
			int current = 0;


			size_t rectPosition = currentLine.find("<Rectangle>");
			if (currentLine.find("<Rectangle>"))
			for (std::string::iterator it = currentLine.begin(); it != currentLine.end(); ++it, ++current) {
				

				
				/*
				//DEVIDER_MARK
				if ((*it) == DEVIDER_MARK) {
					continue;
				}
				//OPEN_START_TAG
				if ((*it) == OPEN_START_TAG) {
					start = current+1;
					continue;
				}
				//CLOSE_START_TAG
				if ((*it) == CLOSE_START_TAG) {
					end = current;
					std::string view = currentLine.substr(start, current - start);
					std::cout << "VIEW is " << view << std::endl;
					if ("Rectangle" == view)
						parseRectangle(file, currentLine, current);
				}
				*/
				/*std::shared_ptr<std::string> nameValue = std::shared_ptr<std::string>(new std::string(currentLine.substr(start, current - start)));
				std::shared_ptr<std::string> name = std::shared_ptr<std::string>(new std::string("name"));
				std::shared_ptr<std::pair<std::string, std::string>> pair = std::shared_ptr<std::pair<std::string, std::string>>(new std::pair<>);*/
			}




			/*size_t start = currentLine.find_first_of(OPEN_START_TAG)+1;
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
			}*/
		}
	}

	file.close();

	return viewList;
}

void Parser::parseRectangle(std::ifstream& file, std::string currentLine, int current) {
		View* v = nullptr;
		do {
			std::string var;
			std::string value;
			int start = -1;
			int end = -1;
			for (std::string::iterator it = currentLine.begin() + current; it != currentLine.end(); ++it, ++current) {
				//DEVIDER_MARK
				if ((*it) == DEVIDER_MARK) {
						continue;
				}
				//ASSING_MARK
				if ((*it) == ASSING_MARK) {
					if (start != -1) {
						if (end == -1)		//if only one symbol
							end = start;
						// +1 because we have not increase "end" on latest iteration
						var = currentLine.substr(start, end - start + 1); 
						std::cout << "var = " << var << std::endl;
						start = -1;
						end = -1;
					}
					continue;
				}
				//VALUE_MARK
				if ((*it) == VALUE_MARK) {
					if (start != -1) {
						if (end == -1)		//if only one symbol
							end = start;
						// +1 because we have not increase "end" on latest iteration
						value = currentLine.substr(start, end - start + 1);
						std::cout << "value = " << value << std::endl;
						start = -1;
						end = -1;
					}
					continue;
				}
				if ((*it) == OPEN_END_TAG[0] && (*(it+1)) == OPEN_END_TAG[1]) {

				}
				if (start == -1)
					start = current;
				else
					end = current;
			}
			current = 0;
		} while (getline(file, currentLine));
}