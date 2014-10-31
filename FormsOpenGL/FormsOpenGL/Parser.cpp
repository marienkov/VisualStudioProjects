#include "Parser.h"

Parser::Parser() : viewList(new std::list<std::shared_ptr<View>>())
{
	initSupportedViews();
}

Parser::~Parser()
{
}

std::shared_ptr<std::list<std::shared_ptr<View>>> Parser::parse(const char* fileName) {

	viewList->clear();

	if (supportedViewMap.size() == 0) {
		log("supportedList is empty");
		return viewList;
	}

	std::ifstream file(fileName);
	std::string currentLine;

	if (file.is_open()) {
		std::shared_ptr<View>(Parser::*parseFunction) (std::ifstream& file, std::string currentLine, int current);
		while (getline(file, currentLine)) {
			for (std::map<std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)>::iterator it = supportedViewMap.begin();
					it != supportedViewMap.end(); ++it) {
				size_t tagPosition = currentLine.find(it->first);
				if (tagPosition != std::string::npos) {
					parseFunction = it->second;
					std::shared_ptr<View> sPtr = (this->*parseFunction)(file, currentLine, tagPosition + (*it).first.size());
					if (sPtr)
						viewList->push_back(std::shared_ptr<View>(sPtr));

				}
			}
		}
	}

	file.close();
	return viewList;
}

std::shared_ptr<View> Parser::parseButton(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 63;
	
	std::shared_ptr<Button> rect = std::shared_ptr<Button>(new Button());
	std::string id;
	int color,x0, y0, width, height;
	
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
					if (var == "id") { id = value; validation |= 1; }
					else if (var == "x0"){ x0 = std::stoi(value); validation |= 2; }
					else if (var == "y0"){ y0 = std::stoi(value); validation |= 4; }
					else if (var == "width") { width = std::stoi(value); validation |= 8; }
					else if (var == "height") { height = std::stoi(value); validation |= 16; }
					else if (var == "color") { color = std::stoi(value); validation |= 32; }
					log("value = " + value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it+1)) == OPEN_END_TAG[1]) {
				if (validation != validationSuccess) {
					log("InValid Button");
					rect.reset();
					return rect;
				}
				log("Valid Button");
				rect->setId(id);
				rect->setColor(color);
				rect->setAllVer(View::VertexCoord(x0, y0, 0), View::VertexCoord(x0 + width, y0, 0),
					View::VertexCoord(x0 + width, y0 + height, 0), View::VertexCoord(x0, y0 + height, 0));
				return rect;
			}
			if (start == -1)
				start = current;
			else
				end = current;
		}
		current = 0;
	} while (getline(file, currentLine));
	log("InValid Button");
	rect.reset();
	return rect;
}

//NOT USING ANYWHERE
std::shared_ptr<View> Parser::parseTriangle(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 63;

	std::shared_ptr<Triangle> trian = std::shared_ptr<Triangle>(new Triangle());
	std::string id;
	int color, x0, y0, x1, y1, x2, y2;

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
					if (var == "id") { id = value; validation |= 1; }
					else if (var == "x0"){ x0 = std::stoi(value); validation |= 2; }
					else if (var == "y0"){ y0 = std::stoi(value); validation |= 4; }
					else if (var == "x1") { x1 = std::stoi(value); validation |= 8; }
					else if (var == "y1") { y1 = std::stoi(value); validation |= 16; }
					else if (var == "x2") { x2 = std::stoi(value); validation |= 8; }
					else if (var == "y2") { y2 = std::stoi(value); validation |= 16; }
					else if (var == "color") { color = std::stoi(value); validation |= 32; }
					log("value = " + value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it + 1)) == OPEN_END_TAG[1]) {
				if (validation != validationSuccess) {
					log("InValid Triangle");
					trian.reset();
					return trian;
				}
				log("Valid Triangle");
				trian->setId(id);
				trian->setColor(color);
				trian->setAllVer(View::VertexCoord(x0, y0, 0), View::VertexCoord(x1, y1, 0),
					View::VertexCoord(x2, y2, 0));
				return trian;
			}
			if (start == -1)
				start = current;
			else
				end = current;
		}
		current = 0;
	} while (getline(file, currentLine));
	log("InValid Triangle");
	trian.reset();
	return trian;
}

void Parser::initSupportedViews() {
	//Rectangel
	std::pair <std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair1;
	somePair1.first = "<Button>";
	somePair1.second = &Parser::parseButton;
	supportedViewMap.insert(somePair1);

	//Triangle
	std::pair <std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair2;
	somePair2.first = "<Triangle>";
	somePair2.second = &Parser::parseTriangle;
	supportedViewMap.insert(somePair2);
}

void Parser::log(std::string message) {
	if (debugMode) {
		std::cout << TAG << message << std::endl;
	}
}