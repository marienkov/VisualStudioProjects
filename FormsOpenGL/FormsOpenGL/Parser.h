#pragma once
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "Button.h"
#include "Triangle.h"
#include "Rectangle3D.h"
#include "map"

typedef std::shared_ptr<View> sView;
typedef std::shared_ptr<Triangle> sTriangle;
typedef std::shared_ptr<Button> sButton;
typedef std::shared_ptr<Rectangle3D> sRecnatgle3D;

typedef std::shared_ptr<std::list<sView>> sViewList;

class Parser
{
private:
	const bool debugMode = false;
	const std::string TAG = "Parser:   ";

	const char OPEN_START_TAG = '\<';
	const char CLOSE_START_TAG = '\>';
	const char* OPEN_END_TAG = "\<\/";
	const char CLOSE_END_TAG = '\>';

	const char ASSING_MARK = '=';
	const char VALUE_MARK = '"';
	const char DEVIDER_MARK = ' ';

	sViewList viewList;
	std::map<std::string, sView(Parser::*) (std::ifstream& file, std::string currentLine, int current)> supportedViewMap;
	
	sView parseButton(std::ifstream& file, std::string currentLine, int current);
	sView parseTriangle(std::ifstream& file, std::string currentLine, int current);
	sView parseRectangle3D(std::ifstream& file, std::string currentLine, int current);
	void initSupportedViews();
public:
	Parser();
	virtual ~Parser();
	sViewList parse(const char* file);
	void log(std::string message);
};