#include "Utilities.h"

#include <iostream>
#include <iomanip>

std::string Logger::Filename = "";
LogOutput Logger::Output = LogOutput::TO_CONSOLE;
std::ofstream Logger::FileStream = std::ofstream();

void Logger::Log(std::string text, bool addNewLine)
{
	if (Output == TO_CONSOLE)
		std::cout << text << (addNewLine ? "\n" : "");
	else if (Output == TO_FILE)
		FileStream << text << (addNewLine ? "\n" : "");
}

void Logger::Log(double number, bool addNewLine)
{
	if (Output == TO_CONSOLE)
		std::cout << std::fixed << std::setprecision(9) << number << (addNewLine ? "\n" : "");
	else if (Output == TO_FILE)
		FileStream << std::fixed << std::setprecision(9) << number << (addNewLine ? "\n" : "");
}

void Logger::Log(unsigned int number, bool addNewLine)
{
	if (Output == TO_CONSOLE)
		std::cout << number << (addNewLine ? "\n" : "");
	else if (Output == TO_FILE)
		FileStream << number << (addNewLine ? "\n" : "");
}

void Logger::Log(int number, bool addNewLine)
{
	if (Output == TO_CONSOLE)
		std::cout << number << (addNewLine ? "\n" : "");
	else if (Output == TO_FILE)
		FileStream << number << (addNewLine ? "\n" : "");
}

void Logger::SetFilename(std::string filename)
{
	Filename = filename;
	//FileStream.open(filename.c_str(), std::ofstream::app);
	FileStream.open(filename.c_str());
}

void Logger::SetOutput(LogOutput output)
{
	Output = output;
}

void Logger::CloseStream()
{
	if (FileStream.is_open())
		FileStream.close();
}
