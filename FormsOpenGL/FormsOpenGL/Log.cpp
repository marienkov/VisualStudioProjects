#include "Log.h"

bool Log::debug = false;
Log Log::instance;

Log::Log()
{
}


Log::~Log()
{
}

Log& Log::log(std::string message) {
	if (debug) {
		std::cout << message << std::endl;
	}
	return instance;
}