#pragma once

#define DEFAULT_DELIMITER ";"
#define LOG(TEXT) Logger::Log(TEXT)
#define LOG_DELIMITED(TEXT, DELIMITER) Logger::Log(TEXT, false); Logger::Log(DELIMITER, false)
#define LOG_DELIMITED_DEFAULT(TEXT) LOG_DELIMITED(TEXT, DEFAULT_DELIMITER)

#include "Utilities/Utilities.h"
#include <string>
#include <fstream>

enum LogOutput
{
	NO_LOG,
	TO_CONSOLE,
	TO_FILE
};

class Logger
{
public:
	static void Log(std::string text, bool addNewLine = true);
	static void Log(double number, bool addNewLine = true);
	static void Log(int number, bool addNewLine = true);
	static void Log(unsigned int number, bool addNewLine = true);

	static void SetFilename(std::string filename);
	static void SetOutput(LogOutput output);
	static void CloseStream();
private:
	static std::string Filename;
	static LogOutput Output;
	static std::ofstream FileStream;
};
