#include <iostream>
#include "FileOperator.h"
#include "DirectoryOperator.h"
#include "DictionaryItem.h"
#include "StopWatch.h"
#define FOLDER_DATA "Dictionary"

using namespace std;

int main()
{
	DirectoryOperator dO;
	FileOperator fO;
	string o = DirectoryOperator::getAppDataFolderPath();

}