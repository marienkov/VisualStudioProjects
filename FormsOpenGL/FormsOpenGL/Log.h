#pragma once
#include <iostream>
#include <string>

class Log
{
private:
	Log();
	~Log();
	static Log instance;
public:
	static bool debug;
	static Log& log(std::string message);
};

