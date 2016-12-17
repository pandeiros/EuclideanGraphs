#pragma once

#define LOG(TEXT) Logger::Log(TEXT)

#include <string>

class Logger
{
public:
	static void Log(std::string text);
};
