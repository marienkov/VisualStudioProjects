#pragma once
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "Button.h"
#include "Triangle.h"
#include "map"

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

	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
	std::map<std::string, std::shared_ptr<View>(Parser::*) (std::ifstream& file, std::string currentLine, int current)> supportedViewMap;
	
	std::shared_ptr<View> parseButton(std::ifstream& file, std::string currentLine, int current);
	std::shared_ptr<View> parseTriangle(std::ifstream& file, std::string currentLine, int current);
	void initSupportedViews();
public:
	Parser();
	virtual ~Parser();
	std::shared_ptr<std::list<std::shared_ptr<View>>> parse(const char* file);
	void log(std::string message);
};