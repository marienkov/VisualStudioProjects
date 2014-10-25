#pragma once
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "View.h"
#include "Rectangle.h"
#include "Triangle.h"

class Parser
{
private:
	const bool debugMode = true;
	const std::string TAG = "Parser:   ";

	const char OPEN_START_TAG = '\<';
	const char CLOSE_START_TAG = '\>';
	const char* OPEN_END_TAG = "\<\/";
	const char CLOSE_END_TAG = '\>';

	const char ASSING_MARK = '=';
	const char VALUE_MARK = '"';
	const char DEVIDER_MARK = ' ';

	std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
	std::list<std::string> supportedList;
public:
	Parser();
	virtual ~Parser();

	void setSupportedViews(std::list<std::string>);
	std::shared_ptr<View> parseRectangle(std::ifstream& file, std::string currentLine, int current);
	std::shared_ptr<std::list<std::shared_ptr<View>>> parse(const char* file);
	void log(std::string message);
};

