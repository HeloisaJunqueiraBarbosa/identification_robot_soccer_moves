#pragma once
#include "constants.h"
#include "tools.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Reader
{
private:
	// Paths
	// paths are setted and stored to avoid overhead
	std::string gameDir;
	std::string saveDir;
	std::string rcgName;
	std::string rcgPath;
	std::string csvPath;

	// Data
	// data structure used for loading from file to memmory
	std::vector<std::string> csvData;

private:
	// sets all paths a single time before loading and writing
	void setAllPaths(const std::string &rcgPath, const std::string &rootDir);
	// loads data from files and format them in a more readable manner
	void loadRcg();
	// saves data in to new file
	void saveCsv();

public:
	// Calling Reader
	void readDir(const std::string &rootDir = "../data/input");
};