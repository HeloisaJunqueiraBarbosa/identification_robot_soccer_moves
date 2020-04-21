#pragma once
#include <iostream>

struct fileFormat
{
    char groupBy;
    char filterBy;
    bool header;
    bool rowId;
    bool playLength;
    bool team;
    bool cycle;
    bool player;
    bool halfField;
    std::string separator;

    void print();
};
fileFormat UserInterface();
