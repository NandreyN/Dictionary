#include "DirectoryOperator.h"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <direct.h>
#include <windows.h>

#define FOLDER_DATA "Dictionary"

bool DirectoryOperator::isExist(const std::string& folderPath) const
{
	DWORD ftyp = GetFileAttributesA(folderPath.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		std::cerr << "Wrong path" << std::endl;
		return false;
	}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}

bool DirectoryOperator::createFileInDir(const std::string& folderPath, const std::string& fileNameWithoutExtension) const
{
	if (!DirectoryOperator::isExist(folderPath))
		return false;

	std::string fullPath = folderPath + "\\" +  fileNameWithoutExtension + ".txt";

	if (this->_fOperator.createFile(fullPath))
		return true;

	return false;
}

bool DirectoryOperator::removeFileInDir(const std::string&folderPath, const std::string& fileNameWithoutExtension) const
{
	if (!DirectoryOperator::isExist(folderPath))
		return false;

	std::string fullPath = folderPath + "\\" + fileNameWithoutExtension + ".txt";

	if (this->_fOperator.removeFile(fullPath))
		return true;

	return false;
}

bool DirectoryOperator::createFolder( std::string& pathToFolder,  std::string& folderName)
{
	std::string full = pathToFolder + "\\" + folderName;
	if (mkdir(full.c_str()))
		return true;
	return false;
}

std::string DirectoryOperator::getAppDataFolderPath()
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

std::string DirectoryOperator::getWorkspaceDirName()
{
	return DirectoryOperator::getAppDataFolderPath() + "\\" + FOLDER_DATA + "\\";
}