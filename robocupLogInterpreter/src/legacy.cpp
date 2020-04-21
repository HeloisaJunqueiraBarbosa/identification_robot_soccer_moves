
// // void Filter::setAllPaths(const std::string &inputPath, const std::string &rootDir, bool singleFile)
// // {
// //     // tests if files arguments are valid
// //     if (!(inputPath.rfind(".csv") == inputPath.size() - 4))
// //         throw std::runtime_error("Not a .csv file.");

// //     if (!std::filesystem::exists(inputPath))
// //         throw std::runtime_error("File doesnt exist.");

// //     // sets all system paths attributes
// //     this->rootDir = rootDir;

// //     //input
// //     setInputPath(inputPath);

// //     //filtered
// //     setFilteredPath();

// //     //teamDir
// //     setTeamsPath();

// //     //raw
// //     setRawPath(singleFile);

// //     return;
// // }

// // void Filter::setFilteredPath()
// // {
// //     this->filteredDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
// //     this->filteredDir = filteredDir + "/filtered" + inputDir.substr(rootDir.size());
// //     this->filteredPath = filteredDir + "/" + inputName;

// //     return;
// // }

// // void Filter::setRawPath(bool singleFile)
// // {
// //     this->rawDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
// //     if (singleFile)
// //     {
// //         this->rawDir = rawDir + "/raw";
// //         this->rawPath = rawDir + "/output";
// //     }
// //     else
// //     {
// //         this->rawDir = rawDir + "/raw" + inputDir.substr(rootDir.size());
// //         this->rawPath = rawDir + "/" + inputName;
// //     }

// //     return;
// // }

// // void Filter::setTeamsPath()
// // {
// //     //set teams dir
// //     this->teamsDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
// //     this->teamsDir = teamsDir + "/teams/";

// //     // open file
// //     std::fstream inputFile(this->inputPath);

// //     //scope declarations
// //     int position;

// //     //discarts headers and ball line from csv file
// //     getline(inputFile, inputLine);
// //     getline(inputFile, inputLine);

// //     //get first team line
// //     getline(inputFile, inputLine);

// //     //discard cycle cell
// //     position = inputLine.find(" ");
// //     inputLine = inputLine.substr(position + 1);

// //     //get first team name
// //     position = inputLine.find(" ");
// //     this->leftTeamPath = this->teamsDir + inputLine.substr(0, position);

// //     //discart same team lines
// //     for (int i = 0; i < 11; i++)
// //     {
// //         getline(inputFile, inputLine);
// //     }

// //     //get second team line
// //     getline(inputFile, inputLine);

// //     //discard cycle cell
// //     position = inputLine.find(" ");
// //     inputLine = inputLine.substr(position + 1);

// //     //get second team name
// //     position = inputLine.find(" ");
// //     this->rightTeamPath = this->teamsDir + inputLine.substr(0, position);

// //     return;
// // }

// // void Filter::saveCsv()
// // {
// //     // check if dir exists and creates it if it doesnt.
// //     if (!std::filesystem::exists(filteredDir))
// //         std::filesystem::create_directories(filteredDir);

// //     //  open file
// //     std::fstream csvFile;
// //     csvFile.open(filteredPath, std::ios::out | std::ios::trunc);

// //     // write headers
// //     csvFile << "cycle, team, player, ";
// //     for (int i = 0; i < MAX_PLAY_LENGTH; i++)
// //     {
// //         csvFile << "pos_x_" << i << ", "
// //                 << "pos_y_" << i;
// //         if (i != MAX_PLAY_LENGTH - 1)
// //             csvFile << ", ";
// //     }
// //     csvFile << std::endl;

// //     //print data
// //     for (unsigned int i = 0; i < paths.size(); i++)
// //     {
// //         for (unsigned int j = 0; j < paths[i].size(); j++)
// //         {
// //             csvFile << paths[i][j];
// //             if (j != paths[i].size() - 1)
// //                 csvFile << ", ";
// //         }
// //         csvFile << std::endl;
// //     }

// //     //close file
// //     csvFile.close();
// //     return;
// // }

// // void Filter::saveTeams()
// // {
// //     // check if dir exists and creates it if it doesnt.
// //     if (!std::filesystem::exists(teamsDir))
// //         std::filesystem::create_directories(teamsDir);

// //     //  open file
// //     std::fstream rightTeamFile, leftTeamFile;
// //     rightTeamFile.open(rightTeamPath, std::ios::app);
// //     leftTeamFile.open(leftTeamPath, std::ios::app);

// //     //print data
// //     unsigned int playsIndex;
// //     int attacker;
// //     for (unsigned int i = 0; i < paths.size(); i++)
// //     {
// //         //get play index and use it to determine who was attacker during this path execution
// //         playsIndex = 0;
// //         while (playsIndex < plays.size())
// //         {
// //             if (paths[i][0] == plays[playsIndex][0])
// //                 break;
// //             playsIndex++;
// //         }
// //         attacker = plays[playsIndex][2];

// //         //if the path in question is not from an attacker ignore it
// //         if (paths[i][1] != attacker)
// //             continue;

// //         //else write path into team file
// //         if (paths[i][1] == 0)
// //         {
// //             for (unsigned int j = 3; j < paths[i].size(); j++)
// //             {
// //                 leftTeamFile << paths[i][j];
// //                 if (j != paths[i].size() - 1)
// //                     leftTeamFile << ", ";
// //             }
// //             leftTeamFile << std::endl;
// //         }

// //         if (paths[i][1] == 1)
// //         {
// //             for (unsigned int j = 3; j < paths[i].size(); j++)
// //             {
// //                 rightTeamFile << -1 * paths[i][j];
// //                 if (j != paths[i].size() - 1)
// //                     rightTeamFile << ", ";
// //             }
// //             rightTeamFile << std::endl;
// //         }
// //     }

// //     //close file
// //     rightTeamFile.close();
// //     leftTeamFile.close();
// //     return;
// // }

// // void Filter::saveRaw()
// // {

// //     // check if dir exists and creates it if it doesnt.
// //     if (!std::filesystem::exists(rawDir))
// //         std::filesystem::create_directories(rawDir);

// //     // open file
// //     std::fstream rawFile;
// //     rawFile.open(rawPath, std::ios::out | std::ios::app);

// //     // print data
// //     for (unsigned int i = 0; i < paths.size(); i++)
// //     {
// //         for (unsigned int j = 3; j < paths[i].size(); j++)
// //         {
// //             rawFile << paths[i][j];
// //             if (j != paths[i].size() - 1)
// //                 rawFile << ", ";
// //         }
// //         rawFile << std::endl;
// //     }
// //     // close file
// //     rawFile.close();
// //     return;
// // }

// // void Filter::filterDir(const std::string &rootDir)
// // {
// //     //get list of all csv files in root dir
// //     std::vector<std::string> inputPaths = listFiles(rootDir, ".csv");

// //     //for each vsc file loads all data into class and outputs it
// //     for (unsigned int i = 0; i < inputPaths.size(); ++i)
// //     {
// //         std::cout << i << ". reading file: " << inputPaths[i] << std::endl;
// //         try
// //         {
// //             std::cout << "\t" << i << ".1. setting paths and attributes." << std::endl;
// //             setAllPaths(inputPaths[i], rootDir, true);
// //             std::cout << "\t" << i << ".2. loading file: '" << inputName << "'." << std::endl;
// //             loadData();
// //             std::cout << "\t" << i << ".3. evaluating ball possession." << std::endl;
// //             evalHold();
// //             std::cout << "\t" << i << ".4. loading plays." << std::endl;
// //             setPlays();
// //             std::cout << "\t" << i << ".5. filtering data." << std::endl;
// //             setFiltered();
// //             std::cout << "\t" << i << ".6. creating paths." << std::endl;
// //             createPaths();
// //             std::cout << "\t" << i << ".7. writing csv to I/O." << std::endl;
// //             saveCsv();
// //             std::cout << "\t" << i << ".8. writing teams to I/O." << std::endl;
// //             saveTeams();
// //             std::cout << "\t" << i << ".9. writin raw to I/O" << std::endl;
// //             saveRaw();
// //         }
// //         catch (const std::exception &e)
// //         {
// //             std::cerr << "ERROR: " << e.what() << std::endl;
// //             return;
// //         }
// //     }
// // }

// void Filter::setAllPaths(const std::string &inputPath, const std::string &rootDir, bool singleFile)
// {
//     // tests if files arguments are valid
//     if (!(inputPath.rfind(".csv") == inputPath.size() - 4))
//         throw std::runtime_error("Not a .csv file.");

//     if (!std::filesystem::exists(inputPath))
//         throw std::runtime_error("File doesnt exist.");

//     // sets all system paths attributes
//     this->rootDir = rootDir;

//     //input
//     setInputPath(inputPath);

//     //filtered
//     setFilteredPath();

//     //teamDir
//     setTeamsPath();

//     //raw
//     setRawPath(singleFile);

//     return;
// }

// void Filter::setFilteredPath()
// {
//     this->filteredDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
//     this->filteredDir = filteredDir + "/filtered" + inputDir.substr(rootDir.size());
//     this->filteredPath = filteredDir + "/" + inputName;

//     return;
// }

// void Filter::setRawPath(bool singleFile)
// {
//     this->rawDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
//     if (singleFile)
//     {
//         this->rawDir = rawDir + "/raw";
//         this->rawPath = rawDir + "/output";
//     }
//     else
//     {
//         this->rawDir = rawDir + "/raw" + inputDir.substr(rootDir.size());
//         this->rawPath = rawDir + "/" + inputName;
//     }

//     return;
// }

// void Filter::setTeamsPath()
// {
//     //set teams dir
//     this->teamsDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
//     this->teamsDir = teamsDir + "/teams/";

//     // open file
//     std::fstream inputFile(this->inputPath);

//     //scope declarations
//     int position;

//     //discarts headers and ball line from csv file
//     getline(inputFile, inputLine);
//     getline(inputFile, inputLine);

//     //get first team line
//     getline(inputFile, inputLine);

//     //discard cycle cell
//     position = inputLine.find(" ");
//     inputLine = inputLine.substr(position + 1);

//     //get first team name
//     position = inputLine.find(" ");
//     this->leftTeamPath = this->teamsDir + inputLine.substr(0, position);

//     //discart same team lines
//     for (int i = 0; i < 11; i++)
//     {
//         getline(inputFile, inputLine);
//     }

//     //get second team line
//     getline(inputFile, inputLine);

//     //discard cycle cell
//     position = inputLine.find(" ");
//     inputLine = inputLine.substr(position + 1);

//     //get second team name
//     position = inputLine.find(" ");
//     this->rightTeamPath = this->teamsDir + inputLine.substr(0, position);

//     return;
// }

// void Filter::saveCsv()
// {
//     // check if dir exists and creates it if it doesnt.
//     if (!std::filesystem::exists(filteredDir))
//         std::filesystem::create_directories(filteredDir);

//     //  open file
//     std::fstream csvFile;
//     csvFile.open(filteredPath, std::ios::out | std::ios::trunc);

//     // write headers
//     csvFile << "cycle, team, player, ";
//     for (int i = 0; i < MAX_PLAY_LENGTH; i++)
//     {
//         csvFile << "pos_x_" << i << ", "
//                 << "pos_y_" << i;
//         if (i != MAX_PLAY_LENGTH - 1)
//             csvFile << ", ";
//     }
//     csvFile << std::endl;

//     //print data
//     for (unsigned int i = 0; i < paths.size(); i++)
//     {
//         for (unsigned int j = 0; j < paths[i].size(); j++)
//         {
//             csvFile << paths[i][j];
//             if (j != paths[i].size() - 1)
//                 csvFile << ", ";
//         }
//         csvFile << std::endl;
//     }

//     //close file
//     csvFile.close();
//     return;
// }

// void Filter::saveTeams()
// {
//     // check if dir exists and creates it if it doesnt.
//     if (!std::filesystem::exists(teamsDir))
//         std::filesystem::create_directories(teamsDir);

//     //  open file
//     std::fstream rightTeamFile, leftTeamFile;
//     rightTeamFile.open(rightTeamPath, std::ios::app);
//     leftTeamFile.open(leftTeamPath, std::ios::app);

//     //print data
//     unsigned int playsIndex;
//     int attacker;
//     for (unsigned int i = 0; i < paths.size(); i++)
//     {
//         //get play index and use it to determine who was attacker during this path execution
//         playsIndex = 0;
//         while (playsIndex < plays.size())
//         {
//             if (paths[i][0] == plays[playsIndex][0])
//                 break;
//             playsIndex++;
//         }
//         attacker = plays[playsIndex][2];

//         //if the path in question is not from an attacker ignore it
//         if (paths[i][1] != attacker)
//             continue;

//         //else write path into team file
//         if (paths[i][1] == 0)
//         {
//             for (unsigned int j = 3; j < paths[i].size(); j++)
//             {
//                 leftTeamFile << paths[i][j];
//                 if (j != paths[i].size() - 1)
//                     leftTeamFile << ", ";
//             }
//             leftTeamFile << std::endl;
//         }

//         if (paths[i][1] == 1)
//         {
//             for (unsigned int j = 3; j < paths[i].size(); j++)
//             {
//                 rightTeamFile << -1 * paths[i][j];
//                 if (j != paths[i].size() - 1)
//                     rightTeamFile << ", ";
//             }
//             rightTeamFile << std::endl;
//         }
//     }

//     //close file
//     rightTeamFile.close();
//     leftTeamFile.close();
//     return;
// }

// void Filter::saveRaw()
// {

//     // check if dir exists and creates it if it doesnt.
//     if (!std::filesystem::exists(rawDir))
//         std::filesystem::create_directories(rawDir);

//     // open file
//     std::fstream rawFile;
//     rawFile.open(rawPath, std::ios::out | std::ios::app);

//     // print data
//     for (unsigned int i = 0; i < paths.size(); i++)
//     {
//         for (unsigned int j = 3; j < paths[i].size(); j++)
//         {
//             rawFile << paths[i][j];
//             if (j != paths[i].size() - 1)
//                 rawFile << ", ";
//         }
//         rawFile << std::endl;
//     }
//     // close file
//     rawFile.close();
//     return;
// }

// void Filter::filterDir(const std::string &rootDir)
// {
//     //get list of all csv files in root dir
//     std::vector<std::string> inputPaths = listFiles(rootDir, ".csv");

//     //for each vsc file loads all data into class and outputs it
//     for (unsigned int i = 0; i < inputPaths.size(); ++i)
//     {
//         std::cout << i << ". reading file: " << inputPaths[i] << std::endl;
//         try
//         {
//             std::cout << "\t" << i << ".1. setting paths and attributes." << std::endl;
//             setAllPaths(inputPaths[i], rootDir, true);
//             std::cout << "\t" << i << ".2. loading file: '" << inputName << "'." << std::endl;
//             loadData();
//             std::cout << "\t" << i << ".3. evaluating ball possession." << std::endl;
//             evalHold();
//             std::cout << "\t" << i << ".4. loading plays." << std::endl;
//             setPlays();
//             std::cout << "\t" << i << ".5. filtering data." << std::endl;
//             setFiltered();
//             std::cout << "\t" << i << ".6. creating paths." << std::endl;
//             createPaths();
//             std::cout << "\t" << i << ".7. writing csv to I/O." << std::endl;
//             saveCsv();
//             std::cout << "\t" << i << ".8. writing teams to I/O." << std::endl;
//             saveTeams();
//             std::cout << "\t" << i << ".9. writin raw to I/O" << std::endl;
//             saveRaw();
//         }
//         catch (const std::exception &e)
//         {
//             std::cerr << "ERROR: " << e.what() << std::endl;
//             return;
//         }
//     }
// }
