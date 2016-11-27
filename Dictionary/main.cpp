#include <iostream>
#include "FileOperator.h"
#include "DirectoryOperator.h"
#include "DictionaryItem.h"
#include "StopWatch.h"
#include "Shell.h"

using namespace std;

int main()
{
	DirectoryOperator dO;
	FileOperator fO;
	string o = DirectoryOperator::getAppDataFolderPath();
	Shell shell;
	shell.Listen();
}