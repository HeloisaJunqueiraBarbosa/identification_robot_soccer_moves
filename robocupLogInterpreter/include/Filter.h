#pragma once
#include "tools.h"
#include "constants.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include "fileFormat.h"

// FILTER CLASS
// used to filter csv interpreted
// results, this will output two files
// a new filtered csv and a raw data
// file used as input for clustering alg..
class Filter
{

	// #### ATTRIBUTES ####
private:
	// struct with data that represents the format
	// in wich the output will be displayed on save
	fileFormat outputFormat;

	// System Paths
	// System Paths will be used constantly, so to avoid
	// overhead they will be infered a single time
	// and stored in the class
	std::string rootDir;
	std::string inputDir;
	std::string inputPath;
	std::string inputName;
	std::string outputDir;
	std::string outputPath;
	std::string outputSecondPath;

	//	std::string filteredDir;
	//	std::string filteredPath;
	//	std::string rawDir;
	//	std::string rawPath;
	//	std::string teamsDir;
	//	std::string leftTeamPath;
	//	std::string rightTeamPath;

	// Data
	// this class has 4 data structures:
	// 1. "data" wich is the raw data loaded from csv file
	// plays wich is the a filtered version of the raw
	// 2. "plays" wich is a definition with the cycle bounds
	// of the plays in interest
	// 3. "filtered" with only the plays in interest after
	// 4. "paths" wich is the data in plays allocated in
	// a sequence line the forms the path the players took.
	std::vector<std::vector<float>> data;
	std::vector<std::vector<int>> plays;
	std::vector<std::vector<float>> filtered;
	std::vector<std::vector<float>> paths;

	//Data containers
	// the 3 data sctructures defined above are cosntructured
	// via 3 containers of data that are:
	// 1. "dataLine" wich represents one line of data for "data".
	// 2. "play" wich represents the cycle bounds of a single play.
	// 3. "path" wich represents a single path taken by a player.
	// 4. Since "data" has the same structure as "filtered", being different
	// only in terms of wich lines show, "dataline" is also used for
	// "filtered".
	// obs.: dataLine is defined as sting for reading from files, but
	// data and filtered are float vectores, that occurs because
	// inside of the class casts are being made to float.
	std::vector<float> dataLine;
	std::vector<int> play;
	std::vector<float> path;
	std::string inputLine;

	// #### METHODS ####

	// SYSTEM PATHS
	// setAllPaths sets root Dir and Calls all the other setters in order.
	//void setAllPaths(const std::string &inputPath, const std::string &rootDir, bool singleFile = false);
	//void setPathsByFormat(fileFormat &format, const std::string &inputPath, const std::string &rootDir);
	//void setInputPath(const std::string &inputPath);
	//void setFilteredPath();
	//void setTeamsPath();
	//void setRawPath(bool singleFile);
	void setPaths(const std::string &inputPath, const std::string &rootDir);
	void setInputPath(const std::string &inputPat);
	void setSinglePath();
	void setPerGamePath();
	void setPerTeamPath();
	// DATA

	// The 4 data structures are created via following methods

	// 1. data
	// loadData takes data from files to "data";
	// using playmodeToFloat to convert playmodes
	// into a float indexing list (integer values)
	void
	loadData();
	int playmodeToInt(const std::string &playmode);
	void saveLoadedData();
	// 2. plays
	// setPlays uses a evalHold,isAnEnd and lookForBegin
	// those are function to define ball possession and then
	// using team on ball and playmode (dead ball) definitions
	// can define boundaries to the begin and end of each play
	void setPlays();
	void evalHold();
	bool isAnEnd(int i);
	int lookForBegin(int i);
	int getAttacker(int playmdoe);
	void printPlays();

	// 3. filter
	// filter uses "plays" to create a filtered version of "data".
	void setFiltered();

	// 4. paths
	// createPahts generates "pahts" using "filtered".
	void createPaths();

	// OUTPUT
	// writes paths to files, raw is raw data and
	// csv is a file with headers and more info.
	//void saveCsv();
	//void saveRaw();
	//void saveTeams();
	void saveFile();
	void writeHeaderIfEmpty();
	bool getPathOffensiveTeam(unsigned int i);
	void writeBody();

public:
	Filter(fileFormat format) : outputFormat(format)
	{
	}
	//filterDir is a callable method that uses the above
	//methods in a recursive way for all files in a root dir.
	void filterDir(const std::string &rootDir = "../data/output/unfiltered");
};