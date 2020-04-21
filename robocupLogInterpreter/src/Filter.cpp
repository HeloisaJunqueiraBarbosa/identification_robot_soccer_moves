#include "Filter.h"

//STEP 1 -  SET SYSTEM PATHS (INPUT, OUTPUT)
void Filter::setPaths(const std::string &inputPath, const std::string &rootDir)
{
  // tests if files arguments are valid
  if (!(inputPath.rfind(".csv") == inputPath.size() - 4))
    throw std::runtime_error("Not a .csv file.");

  if (!std::filesystem::exists(inputPath))
    throw std::runtime_error("File doesnt exist.");

  // sets all system paths attributes
  this->rootDir = rootDir;

  //input
  setInputPath(inputPath);

  //output
  if (outputFormat.groupBy == 's')
    setSinglePath();

  else if (outputFormat.groupBy == 'g')
    setPerGamePath();

  else if (outputFormat.groupBy == 't')
    setPerTeamPath();

  return;
}

void Filter::setInputPath(const std::string &inputPath)
{
  this->inputPath = inputPath;
  this->inputDir = inputPath.substr(0, inputPath.rfind("/"));
  this->inputName = inputPath.substr(inputDir.size() + 1);

  return;
}

void Filter::setSinglePath()
{
  this->outputDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2)) + "/output/filtered";
  this->outputPath = outputDir + "/output";
  return;
}

void Filter::setPerGamePath()
{
  this->outputDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
  this->outputDir = outputDir + "/filtered" + inputDir.substr(rootDir.size());
  this->outputPath = outputDir + "/" + inputName;
  return;
}

void Filter::setPerTeamPath()
{
  //set teams dir
  this->outputDir = rootDir.substr(0, rootDir.rfind("/", rootDir.size() - 2));
  this->outputDir = outputDir + "/filtered/";

  // open file
  std::fstream inputFile(this->inputPath);

  //scope declarations
  int position;

  //discarts headers and ball line from csv file
  getline(inputFile, inputLine);
  getline(inputFile, inputLine);

  //get first team line
  getline(inputFile, inputLine);

  //discard cycle cell
  position = inputLine.find(" ");
  inputLine = inputLine.substr(position + 1);

  //get first team name
  position = inputLine.find(" ");
  this->outputPath = this->outputDir + inputLine.substr(0, position);

  //discart same team lines
  for (int i = 0; i < 11; i++)
  {
    getline(inputFile, inputLine);
  }

  //get second team line
  getline(inputFile, inputLine);

  //discard cycle cell
  position = inputLine.find(" ");
  inputLine = inputLine.substr(position + 1);

  //get second team name
  position = inputLine.find(" ");
  this->outputSecondPath = this->outputDir + inputLine.substr(0, position);
  return;
}

//STEP 2 - LOADS DATA FROM INPUT
void Filter::loadData()
{
  // open file
  std::fstream inputFile(inputPath);

  //scope declarations
  int position;
  float cycle = 0, team, player, pos_x, pos_y, speed_x, speed_y, playmode;
  std::string teamName;

  //clear data before writing new loaded data
  data.clear();

  //discarts headers from csv file
  getline(inputFile, inputLine);

  //while for each line
  while (getline(inputFile, inputLine))
  {
    //get cycle from line
    position = inputLine.find(" ");
    cycle = std::stof(inputLine.substr(0, position));
    inputLine = inputLine.substr(position + 1);

    //get team from line converts to float
    //-1 = ball, 0 = left, 1 = right
    position = inputLine.find(" ");
    if (inputLine.substr(0, position) == "ball,")
    {
      team = -1;
    }
    else if (!(teamName == inputLine.substr(0, position)))
    {
      team++;
      teamName = inputLine.substr(0, position);
    }
    inputLine = inputLine.substr(position + 1);

    //get player from line
    //ball is considered player 0
    if (team == -1)
    {
      player = 0;
    }
    else
    {
      position = inputLine.find(" ");
      player = std::stof(inputLine.substr(0, position));
      inputLine = inputLine.substr(position + 1);
    }

    //following could be a for loop, but that is less readable
    //int terms of wich data is being loaded and
    //has no performance advantadge.

    //get pos_x
    position = inputLine.find(" ");
    pos_x = std::stof(inputLine.substr(0, position));
    inputLine = inputLine.substr(position + 1);

    //get pos_y
    position = inputLine.find(" ");
    pos_y = std::stof(inputLine.substr(0, position));
    inputLine = inputLine.substr(position + 1);

    //get speed_x
    position = inputLine.find(" ");
    speed_x = std::stof(inputLine.substr(0, position));
    inputLine = inputLine.substr(position + 1);

    //get speed_y
    position = inputLine.find(" ");
    speed_y = std::stof(inputLine.substr(0, position));
    inputLine = inputLine.substr(position + 1);

    //get playmode and converts to a float via function
    playmode = playmodeToInt(inputLine);

    //clear line before loading
    //loads line
    //laods data
    dataLine.clear();
    dataLine.push_back(cycle);
    dataLine.push_back(team);
    dataLine.push_back(player);
    dataLine.push_back(pos_x);
    dataLine.push_back(pos_y);
    dataLine.push_back(speed_x);
    dataLine.push_back(speed_y);
    dataLine.push_back(0); //ihold
    dataLine.push_back(0); //fhold
    dataLine.push_back(0); //holding
    dataLine.push_back(playmode);
    data.push_back(dataLine);
  }
}

int Filter::playmodeToInt(const std::string &playmode)
{
  // there are 35 different playmodes
  // those are translated here to float.
  // 0 (falta) is play_on, game rolling
  // any other thing (true) is a deadball
  if (playmode == "play_on")
  {
    return 0;
  }
  if (playmode == "stopped")
  {
    return 1;
  }
  if (playmode == "free_kick_l")
  {
    return 2;
  }
  if (playmode == "free_kick_r")
  {
    return 3;
  }
  if (playmode == "kick_in_l")
  {
    return 4;
  }
  if (playmode == "kick_in_r")
  {
    return 5;
  }
  if (playmode == "offside_l")
  {
    return 6;
  }
  if (playmode == "offside_r")
  {
    return 7;
  }
  if (playmode == "foul_charge_l")
  {
    return 8;
  }
  if (playmode == "foul_charge_r")
  {
    return 9;
  }
  if (playmode == "kick_off_l")
  {
    return 10;
  }
  if (playmode == "kick_off_r")
  {
    return 11;
  }
  if (playmode == "goal_kick_l")
  {
    return 12;
  }
  if (playmode == "goal_kick_r")
  {
    return 13;
  }
  if (playmode == "goal_l")
  {
    return 14;
  }
  if (playmode == "goal_r")
  {
    return 15;
  }
  if (playmode == "corner_kick_l")
  {
    return 16;
  }
  if (playmode == "corner_kick_r")
  {
    return 17;
  }
  if (playmode == "back_pass_l")
  {
    return 18;
  }
  if (playmode == "back_pass_r")
  {
    return 19;
  }
  if (playmode == "indirect_free_kick_l")
  {
    return 20;
  }
  if (playmode == "indirect_free_kick_r")
  {
    return 21;
  }
  if (playmode == "back_pass_l")
  {
    return 22;
  }
  if (playmode == "back_pass_r")
  {
    return 23;
  }
  if (playmode == "penalty_setup_l")
  {
    return 24;
  }
  if (playmode == "penalty_setup_r")
  {
    return 25;
  }
  if (playmode == "penalty_ready_l")
  {
    return 26;
  }
  if (playmode == "penalty_ready_r")
  {
    return 27;
  }
  if (playmode == "penalty_taken_l")
  {
    return 28;
  }
  if (playmode == "penalty_taken_r")
  {
    return 29;
  }
  if (playmode == "penalty_score_l")
  {
    return 30;
  }
  if (playmode == "penalty_score_r")
  {
    return 31;
  }
  if (playmode == "penalty_miss_l")
  {
    return 32;
  }
  if (playmode == "penalty_miss_r")
  {
    return 33;
  }
  if (playmode == "free_kick_fault_l")
  {
    return 33;
  }
  if (playmode == "free_kick_fault_r")
  {
    return 34;
  }
  if (playmode == "time_over")
  {
    return 35;
  }

  std::cout << playmode << std::endl;
  throw std::runtime_error("invalid playmode.");
  return -1;
}

//STEP 3 - EVALUATE BALL POSSESSION BASED ON LOADED DATA (MODIFY DATA)
void Filter::evalHold()
{
  //scope declaration to facilitate readability
  bool holdFlag = false;
  int ballLine = 0;
  float distFromBall = 0, relSpeed = 0, ballAccelaration = 0, ballSpeed = 0;
  float pos_x = 0, pos_y = 0, speed_x = 0, speed_y = 0;
  float b_pos_x = 0, b_pos_y = 0, b_speed_x = 0, b_speed_y = 0;

  //stores ball data for a cycle
  for (unsigned int i = 0; i < data.size(); i++)
  {
    if (i % 23 == 0)
    {
      ballLine = i;
      b_pos_x = data[ballLine][3];
      b_pos_y = data[ballLine][4];
      b_speed_x = data[ballLine][5];
      b_speed_y = data[ballLine][6];
      data[ballLine][7] = 0;
      data[ballLine][8] = 0;
      continue;
    }

    pos_x = data[i][3];
    pos_y = data[i][4];
    speed_x = data[i][5];
    speed_y = data[i][6];

    //uses balls and players data to define important values sucha s relative speed and others
    //to after that use said values to infer ball posession.
    distFromBall = pow(pow((pos_x - b_pos_x), 2) + pow((pos_y - b_pos_y), 2), 0.5);
    relSpeed = pow(pow((speed_x - b_speed_x), 2) + pow((speed_y - b_speed_y), 2), 0.5);
    ballAccelaration = ballSpeed - pow(pow(b_speed_x, 2) + pow(b_speed_y, 2), 0.5);
    ballSpeed = pow(pow(b_speed_x, 2) + pow(b_speed_y, 2), 0.5);

    //iHold - defines begin of possesson (data seventh column)
    if (distFromBall <= PLAYER_AREA)
    {
      data[i][7] = true;
    }
    else if ((distFromBall <= KICKABLE_AREA) and (relSpeed <= REACTION or ballAccelaration > INTERACTION_TRESHOLD))
    {
      data[i][7] = true;
    }
    else
    {
      data[i][7] = false;
    }

    //fHold - defines end of poessions (data eigth column)
    if (distFromBall > DASH_DISTANCE)
    {
      data[i][8] = true;
    }
    else if (distFromBall > KICKABLE_AREA and ballSpeed > PLAYER_MOVEMENT)
    {
      data[i][8] = true;
    }
    else
    {
      data[i][8] = false;
    }
  }

  //holding - using beging and end of possession, defines possession
  holdFlag = false;
  for (unsigned int i = 0; i < data.size(); i++)
  {
    if (i > 23)
    {
      data[i][9] = data[i - 23][9];
    }
    if (data[i][8])
    {
      if (data[i][9])
        holdFlag = false;
      data[i][9] = false;
    }
    if (data[i][7] and !holdFlag)
    {
      data[i][9] = true;
      holdFlag = true;
    }
  }
}

//STEP 4 - CREATE PLAYS BASED ON LOADED DATA AND BALL POSSESSION
void Filter::setPlays()
{
  //clear plays before loading
  plays.clear();
  //for each data line, check if a
  //line is tthe finalization of play
  //and the line before is not
  //than finds the beginning of said play
  for (unsigned int i = 0; i < data.size(); i++)
  {
    if (isAnEnd(i) and !isAnEnd(i - 1))
    {
      play.clear();
      play.push_back(lookForBegin(i));
      play.push_back(data[i][0]);
      play.push_back(getAttacker(data[i][10]));
      plays.push_back(play);
    }
  }
}

bool Filter::isAnEnd(int i)
{
  //if its to early in a game cant be an end of play
  if (i < 2)
  {
    return false;
  }

  //check for finalizations using playmode, floats translation is wrinte in comments
  //check goalie kick off
  if (data[i][10] == 12 or data[i][10] == 13)
    return true;

  // // 	checkGoal();
  if (data[i][10] == 14 or data[i][10] == 15)
    return true;

  // check corner kick off
  if (data[i][10] == 16 or data[i][10] == 17)
    return true;

  //check goalie catch
  if ((data[i][10] == 2 or data[i][10] == 3) and data[i][9] == 1 and data[i][2] == 1)
    return true;

  //if none is true is not a finalization
  return false;
}

int Filter::lookForBegin(int i)
{
  //scope declaration for wich teams begins with the ball
  int teamOnBall = -1;

  //if its to early in the game it cant be a play
  if (i < 23 * 3)
  {
    return 0;
  }

  //check for wich teams was first in the ball
  for (int j = i - CHANGE_PLAYMODE_DELAY * 23; j > 0; j--)
  {
    if (data[j][9])
    {
      teamOnBall = data[j][1];
      break;
    }
  }
  //checks for last deadBall or change in
  //ball posession
  for (int j = i - CHANGE_PLAYMODE_DELAY * 23; j > i - (MAX_PLAY_LENGTH * 23) and j > 0; j--)
  {
    //stop ball
    //any play mode that not play_on
    if (data[j][10] and !data[j + 1][10])
    {
      return data[j + 1][0];
    }
    //change on team on ball
    //finding last time ball was with another team
    //that is not the one with the ball in the finalizatino
    if (data[j][9] and !(teamOnBall == data[j][1]))
    {
      //discarting cycles where no ball possession
      //was found
      int k = j + 1;
      while (!data[k][9])
      {
        k++;
      }
      return data[k][0];
    }
  }
  //if neither a deadball or change in possession
  //was found returns maximum length possibel
  //max play length
  if (i - MAX_PLAY_LENGTH * 23 < 0)
  {
    return 0;
  }
  else
  {

    return data[i - MAX_PLAY_LENGTH * 23][0];
  }
}

int Filter::getAttacker(int playmode)
{
  // table to visualize who is the attacler
  //based on the playmode of the end of play

  // id    playmode			  attacker
  // 2     free kick l		  r
  // 3     free kick r		  l
  // 12    goalie kick off l    r
  // 13    goalie kick off r	  l
  // 14    goal l				  l
  // 15    goal r				  r
  // 16    corner kick off l	  l
  // 17    corner kick off r    r

  //remembering that l = 0, r = 1;
  if (playmode == 3 or playmode == 13 or playmode == 14 or playmode == 16)
  {
    return 0;
  }

  if (playmode == 2 or playmode == 12 or playmode == 15 or playmode == 17)
  {
    return 1;
  }

  return -1;
}

//STEP 5 - CREATE FILTERED DATA BASED ON PLAYS
void Filter::setFiltered()
{
  //filters data using plays
  //basically checks if lines in data
  //are within plays boundaries
  //when a line in data is over a play
  //final boundarie, it starts checking
  //with the next play, no need to
  //redo past data lines, since they are in
  //cycle order.
  unsigned int playIndex = 0;
  filtered.clear();

  if (plays.empty())
    return;

  for (unsigned int i = 0; i < data.size(); i++)
  {

    if (data[i][0] >= plays[playIndex][0] and data[i][0] < plays[playIndex][1])
    {
      filtered.push_back(data[i]);
    }
    if (data[i][0] >= plays[playIndex][1])
    {
      playIndex++;
      if (playIndex == plays.size())
        break;
      i--;
    }
  }
}

//STEP 6 - CREATE TRAJECTORIES BASED ON FILTERED DATA
void Filter::createPaths()
{
  //clear path before loading
  paths.clear();
  path.clear();

  //scope declarations for a variable
  std::vector<int> playFirstLine;

  if (filtered.empty())
    return;

  //defining the first data line that represents each
  //plays first cycle.
  playFirstLine.push_back(0);
  for (unsigned int i = 1; i < filtered.size(); i++)
  {
    if (filtered[i][0] - filtered[i - 1][0] > 1)
    {
      playFirstLine.push_back(i);
    }
  }

  //this for is quite mind bogging, but what it is doing is.
  //takes the first line in data that represents the begin of a play
  //iterating over playFirstLine.
  //play 1 -> cycle 660 -> line 10000, for example (example)
  //the uses a delta for player (0-22) to iterate inside said cycle
  //because cycle 660 is actualy composed of 23 lines in data
  //than using data delta iterates with a sum of 23 so that
  //it will take the next cycles for the same player.
  //so inside for for cycles, medium for for players, outside for for plays
  //it will outputs something like the following:

  // i = 1000 -> cycle 660 (begin of first PLay) -> player 0
  // i = 1000 + 23 -> cycle 661 -> player 0
  // ...
  // i = 1000 + 23 * inside for -> cycle 810 (end of first Play) -> player 0

  // i = 1000 + 1 -> cycle 660 (begin of first PLay) -> player 1
  // i = 1000 + 1 + + 23 -> cycle 661 -> player 1
  // ...
  // i = 1000 + 1 + (23 * inside for) -> cycle 810 (end of first Play) -> player 1

  // i = 2000 -> cycle 900 (begin of second PLay) -> player 0
  // i = 2000 + 23 -> cycle 661 -> player 0
  // ...
  // i = 2000 + 23 * inside for -> cycle 1050 (end of second Play) -> player 0

  // and so on
  for (unsigned int plf = 0; plf < playFirstLine.size(); plf++)
  {
    for (int player = 0; player < 23; player++)
    {
      path.push_back(filtered[player + playFirstLine[plf]][0]);
      path.push_back(filtered[player + playFirstLine[plf]][1]);
      path.push_back(filtered[player + playFirstLine[plf]][2]);
      unsigned int delta = player + playFirstLine[plf];
      for (unsigned int i = delta; i < filtered.size(); i = i + 23)
      {
        if ((i > delta + 23 and (filtered[i][0] - filtered[i - 23][0] != 1)))
        {
          paths.push_back(path);
          path.clear();
          break;
        }

        path.push_back(filtered[i][3]); //pos x
        path.push_back(filtered[i][4]); //pos y

        if ((i > filtered.size() - 24))
        {
          paths.push_back(path);
          path.clear();
          break;
        }
      }
    }
  }
}

//STEP 7 - SAVE TRAJECTORIES AS OUTPUT IN FILES
void Filter::saveFile()
{
  // check if dir exists and creates it if it doesnt.
  if (!std::filesystem::exists(outputDir))
    std::filesystem::create_directories(outputDir);

  //file length and dimension

  // write header if needed
  if (outputFormat.header)
    writeHeaderIfEmpty();

  //write data
  writeBody();
}

void Filter::writeHeaderIfEmpty()
{
  std::fstream file;
  file.open(outputPath, std::ios::app);

  //check if its in first line
  file.seekp(0, std::ios::end);
  size_t size = file.tellg();
  if (size == 0)
  {
    // write headers
    if (outputFormat.rowId)
      file << "ID" << outputFormat.separator;
    if (outputFormat.cycle)
      file << "Cycle" << outputFormat.separator;
    if (outputFormat.team)
      file << "Team" << outputFormat.separator;
    if (outputFormat.player)
      file << "Player" << outputFormat.separator;
    if (outputFormat.playLength)
      file << "PlayLength" << outputFormat.separator;
    for (int i = 0; i < MAX_PLAY_LENGTH; i++)
    {
      file << "pos_x_" << i << outputFormat.separator;
      file << "pos_y_" << i;
      if (i != MAX_PLAY_LENGTH - 1)
        file << outputFormat.separator;
    }
    file << std::endl;
    file.close();
  }

  if (outputFormat.groupBy == 't')
  {
    std::fstream secondFile;
    secondFile.open(outputSecondPath, std::ios::app);

    //check if its in first line
    secondFile.seekp(0, std::ios::end);
    size_t size = secondFile.tellg();
    if (size == 0)
    {
      // write headers
      if (outputFormat.rowId)
        secondFile << "ID" << outputFormat.separator;
      if (outputFormat.cycle)
        secondFile << "Cycle" << outputFormat.separator;
      if (outputFormat.team)
        secondFile << "Team" << outputFormat.separator;
      if (outputFormat.player)
        secondFile << "Player" << outputFormat.separator;
      if (outputFormat.playLength)
        secondFile << "PlayLength" << outputFormat.separator;
      for (int i = 0; i < MAX_PLAY_LENGTH; i++)
      {
        secondFile << "pos_x_" << i << outputFormat.separator;
        secondFile << "pos_y_" << i;
        if (i != MAX_PLAY_LENGTH - 1)
          secondFile << outputFormat.separator;
      }
      secondFile << std::endl;
    }
    secondFile.close();
  }
}

bool Filter::getPathOffensiveTeam(unsigned int i)
{
  //get play index and use it to determine who was offensive during this path execution
  unsigned int playsIndex = 0;
  while (playsIndex < plays.size())
  {
    //found from wich play this path is
    if (paths[i][0] == plays[playsIndex][0])
      break;
    playsIndex++;
  }
  //plays third(2) collum determines whos the offensive
  return plays[playsIndex][2];
}

void Filter::writeBody()
{
  int rowIdFirstFile = 0, rowIdSecondFile = 0, fieldSide = 0, attacker = -1;
  std::string unusedString;
  if (outputFormat.header)
  {
    rowIdFirstFile--;
    rowIdSecondFile--;
  }

  std::fstream outputFile, secondOutputFile;
  outputFile.open(outputPath);
  while (std::getline(outputFile, unusedString))
    rowIdFirstFile++;
  outputFile.close();
  outputFile.open(outputPath, std::ios::app);

  if (outputFormat.groupBy == 't')
  {
    secondOutputFile.open(outputSecondPath);
    while (std::getline(secondOutputFile, unusedString))
      rowIdSecondFile++;
    secondOutputFile.close();
    secondOutputFile.open(outputSecondPath, std::ios::app);
  }

  // write data
  for (unsigned int i = 0; i < paths.size(); i++)
  {

    attacker = getPathOffensiveTeam(i);

    //skips defense if needed
    if (outputFormat.filterBy == 'o' and (paths[i][1] != attacker))
      continue;

    //if only half a field wanna be analised
    //that is both teams attacking on same size
    //not actually only one half of field data
    //then chooses when to apply the simmetry
    //multiplier
    if (outputFormat.halfField)
    {
      if (attacker == 1)
      {
        fieldSide = -1;
      }
      else
      {
        fieldSide = 1;
      }
    }

    if (paths[i][1] == 0 or outputFormat.groupBy != 't')
    {
      //write data not skipped
      if (outputFormat.rowId)
      {
        outputFile << rowIdFirstFile << outputFormat.separator;
        rowIdFirstFile++;
      }

      if (outputFormat.cycle)
        outputFile << paths[i][0] << outputFormat.separator;

      if (outputFormat.team)
        outputFile << paths[i][1] << outputFormat.separator;

      if (outputFormat.player)
        outputFile << paths[i][2] << outputFormat.separator;

      if (outputFormat.playLength)
        outputFile << (paths[i].size() - 3) / 2 << outputFormat.separator;

      for (unsigned int j = 3; j < paths[i].size(); j++)
      {
        outputFile << fieldSide * paths[i][j];
        if (j != paths[i].size() - 1)
          outputFile << outputFormat.separator;
      }
      outputFile << std::endl;
    }
    else if (paths[i][1] == 1 and outputFormat.groupBy == 't')
    {
      //write data not skipped
      if (outputFormat.rowId)
      {
        secondOutputFile << rowIdSecondFile << outputFormat.separator;
        rowIdSecondFile++;
      }

      if (outputFormat.cycle)
        secondOutputFile << paths[i][0] << outputFormat.separator;

      if (outputFormat.team)
        secondOutputFile << paths[i][1] << outputFormat.separator;

      if (outputFormat.player)
        secondOutputFile << paths[i][2] << outputFormat.separator;

      if (outputFormat.playLength)
        secondOutputFile << (paths[i].size() - 3) / 2 << outputFormat.separator;

      for (unsigned int j = 3; j < paths[i].size(); j++)
      {
        secondOutputFile << fieldSide * paths[i][j];
        if (j != paths[i].size() - 1)
          secondOutputFile << outputFormat.separator;
      }
      secondOutputFile << std::endl;
    }
    else if (paths[i][1] == -1 and outputFormat.groupBy == 't')
    {
      continue;
    }
    else
    {
      throw std::runtime_error("Something Went Wrong while Writing files.");
    }
  }
  outputFile.close();
  if (outputFormat.groupBy == 't')
    secondOutputFile.close();
  return;
}

//USAGE - APLIES STEPS ABOVE IN DIRECTORY RECCURSIVELY
void Filter::filterDir(const std::string &rootDir)
{
  //get list of all csv files in root dir
  std::vector<std::string> inputPaths = listFiles(rootDir, ".csv");

  //for each vsc file loads all data into class and outputs it
  for (unsigned int i = 0; i < inputPaths.size(); ++i)
  {
    std::cout << i << ". reading file: " << inputPaths[i] << std::endl;
    try
    {
      std::cout << "\t" << i << ".1. setting paths and attributes." << std::endl;
      setPaths(inputPaths[i], rootDir);
      std::cout << "\t" << i << ".2. loading file: '" << inputName << "'." << std::endl;
      loadData();
      std::cout << "\t" << i << ".3. evaluating ball possession." << std::endl;
      evalHold();
      std::cout << "\t" << i << ".4. loading plays." << std::endl;
      setPlays();
      std::cout << "\t" << i << ".5. filtering data." << std::endl;
      setFiltered();
      std::cout << "\t" << i << ".6. creating paths." << std::endl;
      createPaths();
      std::cout << "\t" << i << ".7. writing saving File." << std::endl;
      saveFile();
    }
    catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      return;
    }
  }
}