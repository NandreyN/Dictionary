#pragma once
#include <string>
#include "FileOperator.h"

class DirectoryOperator
{
public:
	bool isExist(const std::string &filePath) const;
	bool createFileInDir(const std::string &filePath, const std::string& fileNameWithoutExtension) const;
	bool removeFileInDir(const std::string &filePath, const std::string& fileNameWithoutExtension) const;
	static std::string getAppDataFolderPath();
private:
	FileOperator _fOperator;
};

