#include "Exceptions.h"
#include<sstream>

Exceptions::Exceptions(int line, const char* file) noexcept : _line(line), _file(file)
{
}

const char* Exceptions::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Exceptions::GetType() const noexcept
{
	return "Exceptions Exception";
}

int Exceptions::GetLine() const noexcept
{
	return _line;
}

const std::string& Exceptions::GetFile() const noexcept
{
	return _file;
}

std::string Exceptions::GetOriginString() const noexcept
{
	return std::string();
}
