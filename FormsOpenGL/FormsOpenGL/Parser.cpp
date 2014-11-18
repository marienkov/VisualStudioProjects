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

	if (supportedViewMap.size() == 0)
		return viewList;

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
	std::shared_ptr<Button> rect = std::shared_ptr<Button>(new Button());
	std::string id;
	float cAlpha = 0, cRed = 0, cGreen = 0, cBlue = 0, x0 = 0, y0 = 0, z0 = 0, width = 0, height = 0;

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
					if (var == "id") id = value;
					else if (var == "x0") x0 = std::stof(value);
					else if (var == "y0") y0 = std::stof(value);
					else if (var == "z0") z0 = std::stof(value);
					else if (var == "width") width = std::stof(value);
					else if (var == "height") height = std::stof(value);
					else if (var == "cAlpha") cAlpha = std::stof(value);
					else if (var == "cRed") cRed = std::stof(value);
					else if (var == "cGreen") cGreen = std::stof(value);
					else if (var == "cBlue") cBlue = std::stof(value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it+1)) == OPEN_END_TAG[1]) {
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
	rect.reset();
	return rect;
}

std::shared_ptr<View> Parser::parseTriangle(std::ifstream& file, std::string currentLine, int current) {
	std::shared_ptr<Triangle> trian = std::shared_ptr<Triangle>(new Triangle());
	std::string id;
	float cAlpha = 0, cRed = 0, cGreen = 0 , cBlue = 0, x0 = 0, y0 = 0, z0 = 0, x1 = 0, y1 = 0, z1 = 0 , x2 = 0, y2 = 0, z2 = 0;

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
					if (var == "id") id = value;
					else if (var == "x0") x0 = std::stof(value);
					else if (var == "y0") y0 = std::stof(value);
					else if (var == "z0") z0 = std::stof(value);
					else if (var == "x1") x1 = std::stof(value);
					else if (var == "y1") y1 = std::stof(value);
					else if (var == "z1") z1 = std::stof(value);
					else if (var == "x2") x2 = std::stof(value);
					else if (var == "y2") y2 = std::stof(value);
					else if (var == "z2") z2 = std::stof(value);
					else if (var == "cAlpha") cAlpha = std::stof(value);
					else if (var == "cRed") cRed = std::stof(value);
					else if (var == "cGreen") cGreen = std::stof(value);
					else if (var == "cBlue") cBlue = std::stof(value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it + 1)) == OPEN_END_TAG[1]) {
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
	trian.reset();
	return trian;
}

std::shared_ptr<View> Parser::parseRectangle3D(std::ifstream& file, std::string currentLine, int current) {
	std::shared_ptr<Rectangle3D> rect3D = std::shared_ptr<Rectangle3D>(new Rectangle3D());
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
					if (var == "id") id = value;
					else if (var == "x0") x0 = std::stof(value);
					else if (var == "y0") y0 = std::stof(value);
					else if (var == "z0") z0 = std::stof(value);
					else if (var == "width") width = std::stof(value);
					else if (var == "height") height = std::stof(value);
					else if (var == "lenght") lenght = std::stof(value);
					else if (var == "cAlpha") cAlpha = std::stof(value);
					else if (var == "cRed") cRed = std::stof(value);
					else if (var == "cGreen") cGreen = std::stof(value);
					else if (var == "cBlue") cBlue = std::stof(value);
					start = -1;
					end = -1;
				}
				continue;
			}
			if ((*it) == OPEN_END_TAG[0] && (*(it + 1)) == OPEN_END_TAG[1]) {
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
	rect3D.reset();
	return rect3D;
}

void Parser::initSupportedViews() {
	//Rectange
	std::pair <std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair1;
	somePair1.first = "<Button>";
	somePair1.second = &Parser::parseButton;
	supportedViewMap.insert(somePair1);

	//Triangle
	std::pair <std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair2;
	somePair2.first = "<Triangle>";
	somePair2.second = &Parser::parseTriangle;
	supportedViewMap.insert(somePair2);

	//Rectangle3D
	std::pair <std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> somePair3;
	somePair3.first = "<Rectangle3D>";
	somePair3.second = &Parser::parseRectangle3D;
	supportedViewMap.insert(somePair3);
}