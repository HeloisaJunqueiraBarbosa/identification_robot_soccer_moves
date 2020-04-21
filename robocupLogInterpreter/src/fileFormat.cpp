#include "fileFormat.h"

fileFormat UserInterface()
{
    fileFormat option;

    //file grouping option
    std::cout << "### Choosing output type ##" << std::endl;
    std::cout << "1. How do you wish to group data in files?" << std::endl;
    std::cout << "  g) by game" << std::endl;
    std::cout << "  t) by teams" << std::endl;
    std::cout << "  t) single file" << std::endl;
    std::cout << "  g/t/s > ";
    do
    {
        scanf(" %c", &option.groupBy);
        getchar();
        if (option.groupBy == 'g' or option.groupBy == 't' or option.groupBy == 's')
        {
            if (option.groupBy == 't')
                std::cout << "    WARNING: Since ball has no team organizing per Team ignores ball data!" << std::endl;
            //std::cout << "you chosed: " << groupBy << std::endl;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  g/t > ";
        }

    } while (true);

    //filter type option
    std::cout << "2. Wich data do you want to gather?" << std::endl;
    std::cout << "  f) Finalization Plays" << std::endl;
    std::cout << "  o) Finzaliation Plays filtered for the Offenser" << std::endl;
    std::cout << "  f/o > ";
    do
    {
        scanf(" %c", &option.filterBy);
        getchar();
        if (option.filterBy == 'f' or option.filterBy == 'o')
        {
            //std::cout << "you chosed: " << option.filterBy << std::endl;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  a/f/o > ";
        }
    } while (true);

    //separator option
    char separator;
    std::cout << "3. Wich CSV Separator do you want to use?" << std::endl;
    std::cout << "  c) Comma ', '" << std::endl;
    std::cout << "  b) blank space ' '" << std::endl;
    std::cout << "  c/b > ";
    do
    {
        scanf(" %c", &separator);
        getchar();
        if (separator == 'c')
        {
            //std::cout << "you chosed: " << separator << std::endl;
            option.separator = ", ";
            break;
        }
        else if (separator == 'b')
        {
            //std::cout << "you chosed: " << separator << std::endl;
            option.separator = " ";
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  c/b > ";
        }
    } while (true);

    //header option
    char yesOrNo;
    std::cout << "4. Do you want Headers on the file?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.header = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.header = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //row id option
    std::cout << "5. Do you want row IDs on the file?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.rowId = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.rowId = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //cycle option
    std::cout << "6. Do you want a first cycle column on the File?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.cycle = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.cycle = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //team option
    std::cout << "7. Do you want a team column on the File?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.team = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.team = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //player option
    std::cout << "8. Do you want a player column on the File?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.player = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.player = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //play length option
    std::cout << "9. Do you want plays length column on the File?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.playLength = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.playLength = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);

    //play length option
    std::cout << "9. Do you want to Annalize offenses in a single direction?" << std::endl;
    std::cout << "  y/n > ";
    do
    {
        scanf(" %c", &yesOrNo);
        getchar();
        if (yesOrNo == 'y')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.halfField = true;
            break;
        }
        else if (yesOrNo == 'n')
        {
            //std::cout << "you chosed: " << yesOrNo << std::endl;
            option.halfField = false;
            break;
        }
        else
        {
            std::cout << "  Invalid option try again: " << std::endl;
            std::cout << "  y/n > ";
        }
    } while (true);
    return option;
}