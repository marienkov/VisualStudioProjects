#include "Parser.h"

Parser::Parser() : viewList(new std::list<std::shared_ptr<View>>())
{
}

Parser::~Parser()
{
}

std::shared_ptr<std::list<std::shared_ptr<View>>> Parser::parse(const char* fileName) {

	viewList->clear();

	if (supportedList.size() == 0) {
		log("supportedList is empty");
		return viewList;
	}

	std::ifstream file(fileName);
	std::string currentLine;

	if (file.is_open()) {
		std::shared_ptr<View>(Parser::*parseFunction) (std::ifstream& file, std::string currentLine, int current);
		while (getline(file, currentLine)) {
			for (std::list<std::string>::iterator it = supportedList.begin(); it != supportedList.end(); ++it) {
				size_t tagPosition = currentLine.find(*it);
				if (tagPosition != std::string::npos) {
					parseFunction = &Parser::parseRectangle;
					std::shared_ptr<View> sPtr = (this->*parseFunction)(file, currentLine, tagPosition + (*it).size());
					if (sPtr)
						viewList->push_back(std::shared_ptr<View>(sPtr));

				}
			}
		}
	}

	file.close();
	return viewList;
}

std::shared_ptr<View> Parser::parseRectangle(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 63;
	std::shared_ptr<View> view = std::shared_ptr<View>(new Rectangle());
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
					log("var = " + var);
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
					if (var == "id") { view->setId(value); validation |= 1; }
					else if (var == "x"){ view->setX(std::stoi(value)); validation |= 2; }
					else if (var == "y"){ view->setY(std::stoi(value)); validation |= 4; }
					else if (var == "width") { view->setWidth(std::stoi(value)); validation |= 8; }
					else if (var == "height") { view->setHeight(std::stoi(value)); validation |= 16; }
					else if (var == "color") { view->setColor(std::stoi(value)); validation |= 32; }
					log("value = " + value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it+1)) == OPEN_END_TAG[1]) {
				if (validation != validationSuccess) {
					log("InValid rectangle");
					view.reset();
					return view;
				}
				log("Valid rectangle");
				return view;
			}
			if (start == -1)
				start = current;
			else
				end = current;
		}
		current = 0;
	} while (getline(file, currentLine));
	log("InValid rectangle");
	view.reset();
	return view;
}

void Parser::setSupportedViews(std::list<std::string>  supportedViews) {
	this->supportedList = supportedViews;
}

void Parser::log(std::string message) {
	if (debugMode) {
		std::cout << TAG << message << std::endl;
	}
}