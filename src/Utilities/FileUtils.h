#pragma once

#include <fstream>
#include <windows.h>
#include <iostream>
#include <filesystem>


class FileUtils
{
public:
	static std::filesystem::path getAssetsFolderPath();
	static std::filesystem::path getExecutablePath();

	static bool getFilePath(std::string& filePath, std::string& fileName);
	//void getFilePath(std::string* filePath);
};

