#pragma once

#include <fstream>
#include <windows.h>
#include <commdlg.h>
#include <iostream>


class FileUtils
{
	public:

	static bool getFilePath(std::string& meshFilePath, std::string& fileName);
	//void getFilePath(std::string* filePath);
};

