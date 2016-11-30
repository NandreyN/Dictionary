#include "FileOperator.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <fstream>
#include "DirectoryOperator.h"

bool FileOperator::isExist(const std::string& filePath) const
{
	if (std::ifstream(filePath))
		return true;
	return false;
}

bool FileOperator::createFile(const std::string& filePath) const
{
	if (std::ofstream(filePath))
		return true;
	return false;
}

bool FileOperator::removeFile(const std::string& filePath) const
{
	if (this->isExist(filePath))
	{
		char* ptr = new char[filePath.length()];
		memcpy(ptr, filePath.c_str(), filePath.length());
		bool rmResult = std::remove(ptr);
		delete[] ptr;
		if (rmResult)
			return true;
	}
	return false;
}
