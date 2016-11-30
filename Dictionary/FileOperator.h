#pragma once
#include <string>

class OpenError
{
};

class CloseError
{
};

class FileOperator
{
public:
	bool isExist(const std::string& filePath) const;
	bool createFile(const std::string& filePath) const;
	bool removeFile(const std::string& filePath) const;
};
