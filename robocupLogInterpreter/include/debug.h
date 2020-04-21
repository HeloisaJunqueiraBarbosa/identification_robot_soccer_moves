#pragma once

// debug tool to facilitate printing
// debug messagens to console
// DEBUG is defined via cmakelist
// that said, when compiled for release
// debug(a) lines will be compiled as blank
//being ignored by the compiler
#ifdef DEBUG
#define debug(a) std::cout << a << std::endl
#else
#define debug(a)
#endif

#include "Filter.h";
#include "fileFormat.h";

//debug for plays
void Filter::printPlays()
{
    for (unsigned int i = 0; i < plays.size(); i++)
        std::cout << "[DEBUG] play " << i << " goes from: " << plays[i][0] << " to: " << plays[i][1] << " and attacker is team " << plays[i][2] << std::endl;
}

//debug file format
void fileFormat::print()
{
    std::cout << "## FILE FORMAT STUCT ##" << std::endl;
    std::cout << "    Grouping by team: " << groupBy << std::endl;
    std::cout << "    Header: " << header << std::endl;
    std::cout << "    row ID: " << rowId << std::endl;
    std::cout << "    Play Length: " << playLength << std::endl;
    std::cout << "    Filtering type: " << filterBy << std::endl;
}