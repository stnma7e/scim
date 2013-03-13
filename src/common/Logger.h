#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>

namespace scim
{

	namespace logger
	{

	void LogError(const std::string& str)
	{
		std::cout << "ERROR: " << str << std::endl;
	}
	void LogInfo(const std::string& str)
	{
		std::cout << "INFO: " << str << std::endl;
	}

	}

}

#endif
