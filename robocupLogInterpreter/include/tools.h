#pragma once
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>

// function to list all files of one specified extension into
// a root directory
std::vector<std::string> listFiles(const std::string &rootDir, const std::string &extension);
