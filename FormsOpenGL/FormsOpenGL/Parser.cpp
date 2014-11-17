#include "Parser.h"

Parser::Parser() : viewList(new std::list<sView>())
{
	initSupportedViews();
}

Parser::~Parser()
{
}

sViewList Parser::parse(const char* fileName) {

	viewList->clear();

	if (supportedViewMap.size() == 0) {
		log("supportedList is empty");
		return viewList;
	}

	std::ifstream file(fileName);
	std::string currentLine;

	if (file.is_open()) {
		sView(Parser::*parseFunction) (std::ifstream& file, std::string currentLine, int current);
		while (getline(file, currentLine)) {
			for (std::map<std::string, sView(Parser::*) (std::ifstream& file, std::string currentLine, int current)>::iterator it = supportedViewMap.begin();
					it != supportedViewMap.end(); ++it) {
				size_t tagPosition = currentLine.find(it->first);
				if (tagPosition != std::string::npos) {
					parseFunction = it->second;
					sView sPtr = (this->*parseFunction)(file, currentLine, tagPosition + (*it).first.size());
					if (sPtr)
						viewList->push_back(sView(sPtr));

				}
			}
		}
	}

	file.close();
	return viewList;
}

sView Parser::parseButton(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 1023;
	
	sButton rect = sButton(new Button());
	std::string id;
	float cAlpha, cRed, cGreen, cBlue, x0, y0, z0, width, height;
	
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
					else if (var == "x0"){ x0 = std::stof(value); validation |= 2; }
					else if (var == "y0"){ y0 = std::stof(value); validation |= 4; }
					else if (var == "z0"){ z0 = std::stof(value); validation |= 8; }
					else if (var == "width") { width = std::stof(value); validation |= 16; }
					else if (var == "height") { height = std::stof(value); validation |= 32; }

					else if (var == "cAlpha") { cAlpha = std::stof(value);  validation |= 64; }
					else if (var == "cRed") { cRed = std::stof(value);  validation |= 128; }
					else if (var == "cGreen") { cGreen = std::stof(value);  validation |= 256; }
					else if (var == "cBlue") { cBlue = std::stof(value);  validation |= 512; }
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
				rect->setCoordinates(View::VertexPosition(x0, y0, z0), View::VertexPosition(x0, y0 - height, z0),
					View::VertexPosition(x0 + width, y0 - height, z0), View::VertexPosition(x0 + width, y0, z0));
				rect->setColor(cRed, cGreen, cBlue, cAlpha);
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

sView Parser::parseTriangle(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 16383;

	sTriangle trian = sTriangle(new Triangle());
	std::string id;
	float cAlpha, cRed, cGreen, cBlue, x0, y0, z0, x1, y1, z1, x2, y2, z2;

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
					else if (var == "x0"){ x0 = std::stof(value); validation |= 2; }
					else if (var == "y0"){ y0 = std::stof(value); validation |= 4; }
					else if (var == "z0"){ z0 = std::stof(value); validation |= 8; }
					else if (var == "x1") { x1 = std::stof(value); validation |= 16; }
					else if (var == "y1") { y1 = std::stof(value); validation |= 32; }
					else if (var == "z1") { z1 = std::stof(value); validation |= 64; }
					else if (var == "x2") { x2 = std::stof(value); validation |= 128; }
					else if (var == "y2") { y2 = std::stof(value); validation |= 256; }
					else if (var == "z2") { z2 = std::stof(value); validation |= 512; }

					else if (var == "cAlpha") { cAlpha = std::stof(value);  validation |= 1024; }
					else if (var == "cRed") { cRed = std::stof(value);  validation |= 2048; }
					else if (var == "cGreen") { cGreen = std::stof(value);  validation |= 4096; }
					else if (var == "cBlue") { cBlue = std::stof(value);  validation |= 8192; }
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
				trian->setColor(cRed, cGreen, cBlue, cAlpha);
				trian->setCoordinates(View::VertexPosition(x0, y0, z0), View::VertexPosition(x1, y1, z1),
					View::VertexPosition(x2, y2, z2));
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

sView Parser::parseRectangle3D(std::ifstream& file, std::string currentLine, int current) {
	unsigned char validation = 0;
	unsigned char validationSuccess = 2047;

	sRecnatgle3D rect3D = sRecnatgle3D(new Rectangle3D());
	std::string id;
	float cAlpha, cRed, cGreen, cBlue, x0, y0, z0, width, height, lenght;

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
					else if (var == "x0"){ x0 = std::stof(value); validation |= 2; }
					else if (var == "y0"){ y0 = std::stof(value); validation |= 4; }
					else if (var == "z0"){ z0 = std::stof(value); validation |= 8; }
					else if (var == "width") { width = std::stof(value); validation |= 16; }
					else if (var == "height") { height = std::stof(value); validation |= 32; }
					else if (var == "lenght") { lenght = std::stof(value); validation |= 64; }

					else if (var == "cAlpha") { cAlpha = std::stof(value);  validation |= 128; }
					else if (var == "cRed") { cRed = std::stof(value);  validation |= 256; }
					else if (var == "cGreen") { cGreen = std::stof(value);  validation |= 512; }
					else if (var == "cBlue") { cBlue = std::stof(value);  validation |= 1024; }
					log("value = " + value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it + 1)) == OPEN_END_TAG[1]) {
				if (validation != validationSuccess) {
					log("InValid Button");
					rect3D.reset();
					return rect3D;
				}
				log("Valid Button");
				rect3D->setId(id);
				rect3D->setCoordinates(
					View::VertexPosition(x0, y0, z0), View::VertexPosition(x0, y0 - height, z0),
					View::VertexPosition(x0 + width, y0 - height, z0), View::VertexPosition(x0 + width, y0, z0),
					View::VertexPosition(x0, y0, z0 - lenght), View::VertexPosition(x0, y0 - height, z0 - lenght),
					View::VertexPosition(x0 + width, y0 - height, z0 - lenght), View::VertexPosition(x0 + width, y0, z0 - lenght));
				rect3D->setColor(cRed, cGreen, cBlue, cAlpha);
				return rect3D;
			}
			if (start == -1)
				start = current;
			else
				end = current;
		}
		current = 0;
	} while (getline(file, currentLine));
	log("InValid Button");
	rect3D.reset();
	return rect3D;
}

void Parser::initSupportedViews() {
	//Rectange
	std::pair <std::string, sView(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair1;
	somePair1.first = "<Button>";
	somePair1.second = &Parser::parseButton;
	supportedViewMap.insert(somePair1);

	//Triangle
	std::pair <std::string, sView(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair2;
	somePair2.first = "<Triangle>";
	somePair2.second = &Parser::parseTriangle;
	supportedViewMap.insert(somePair2);

	//Rectangle3D
	std::pair <std::string, sView(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair3;
	somePair3.first = "<Rectangle3D>";
	somePair3.second = &Parser::parseRectangle3D;
	supportedViewMap.insert(somePair3);
}

void Parser::log(std::string message) {
	if (debugMode) {
		std::cout << TAG << message << std::endl;
	}
}