#pragma once
#include <string>
#include "FileOperator.h"

class DirectoryOperator
{
public:
	bool isExist(const std::string &folderPath) const;
	bool createFileInDir(const std::string &folderPath, const std::string& fileNameWithoutExtension) const;
	bool removeFileInDir(const std::string &folderPath, const std::string& fileNameWithoutExtension) const;
	bool createFolder( std::string &pathToFolder, std::string &fodlerName);
	
	static std::string getWorkspaceDirName();
	static std::string getAppDataFolderPath();
private:
	FileOperator _fOperator;
};

