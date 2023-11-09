#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>

short chooseOption(std::string optionName)
{
    while (true)
    {
        std::cout << optionName << "\n";
        std::cout << "Type y/n \n";
        std::string input;
        std::cin >> input;

        //transform string to lower case
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "y")
        {
            return 1;
        }
        else if (input == "n")
        {
            return 0;
        }
        else
        {
            std::cout << "Type Y / n\n";
        }
    }

    return -1;
}

void createDirectory()
{
    std::filesystem::create_directories("ff15");
}

int main()
{
    short result = chooseOption(std::string("This is your final destination?\n") + std::filesystem::current_path().string());
    if(result == -1)
    {
        std::cout << "Unexpected error in line " << __LINE__ << "\n";
    }
    else if(result == 0)
    {
        //choose other location
    }
    else if(result == 1)
    {
        std::filesystem::directory_entry entry{".\\ff15"};
        std::cout << entry << "\n";
        if(entry.exists())
        {
            //fiel exist and we can load information here
        }
        else
        {
            result = chooseOption("ff doesnt exist, do you want to init? (y/n)\n");
            if(result == -1)
            {
                std::cout << "Unexpected error in line " << __LINE__ << "\n";
            }

            else if(result == 0)
            {
                std::cout << "OK so why u run this program?\n";
            }
            else if(result == 1)
            {
                createDirectory();
                std::cout << "File created\n";
            }
        }

    }

    return 0;
}
