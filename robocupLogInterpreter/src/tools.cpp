#include "tools.h"

std::vector<std::string> listFiles(const std::string &rootDir, const std::string &extension)
{
	// scope declarations
	std::vector<std::string> listOfRcgs;
	std::string entryPath;

	//recursively lis all paths in a directory
	//for each entry(paths) checks if its a file or direcotry
	//and checks file extension.
	for (const auto &entry : std::filesystem::recursive_directory_iterator(rootDir))
	{
		if (std::filesystem::is_directory(entry.path()))
			continue;

		entryPath = entry.path();
		if (!(entryPath.rfind(extension) == entryPath.size() - 4))
			continue;

		listOfRcgs.push_back(entry.path());
	}
	return listOfRcgs;
}
