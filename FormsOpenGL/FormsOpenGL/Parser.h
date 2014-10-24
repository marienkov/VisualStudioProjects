#pragma once
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "View.h"

class Parser
{
private:
	const char OPEN_START_TAG = '\<';
	const char CLOSE_START_TAG = '\>';
	const char* OPEN_END_TAG = "\<\/";
	const char CLOSE_END_TAG = '\>';

	const char ASSING_MARK = '=';
	const char VALUE_MARK = '"';
	const char DEVIDER_MARK = ' ';

	const std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
public:
	Parser();
	virtual ~Parser();

	void setSupportedViews(const std::string[]);
	void parseRectangle(std::ifstream& file, std::string currentLine, int current);
	const std::shared_ptr<std::list<std::shared_ptr<View>>> parse(const char* file);
	
};

