#include "FileOperator.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <fstream>

bool FileOperator::isExist(const std::string &filePath) const
{
	if (std::ifstream(filePath))
		return true;
	return false;
}

bool FileOperator::createFile(const std::string &filePath) const
{
	if (std::ofstream(filePath))
		return true;
	return false;
}

bool FileOperator::removeFile(const std::string &filePath) const 
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

std::string FileOperator::getAppDataFolderPath()
{
	TCHAR szPath[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		size_t size = 150;
		char * pMBBuffer = new char[size];
		int count = wcstombs(pMBBuffer, szPath, size);
		std::string s = pMBBuffer;
		delete[] pMBBuffer;
		return s;
	}
	return std::string("");
}