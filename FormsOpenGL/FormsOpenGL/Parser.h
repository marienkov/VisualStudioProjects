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
	char OPEN_START_TAG = '\<';
	char CLOSE_START_TAG = '\>';
	char* OPEN_END_TAG = "\<\/";
	char CLOSE_END_TAG= '\>';

	char ASSING_MARK = '=';
	char VALUE_MARK = '"';
	char DEVIDER_MARK = ' ';

	const std::shared_ptr<std::list<std::shared_ptr<View>>> viewList;
public:
	Parser();
	virtual ~Parser();

	void setSupportedViews(const std::string[]);
	const std::shared_ptr<std::list<std::shared_ptr<View>>> parse(const char* file);
};

