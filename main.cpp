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

inline bool createDirectory(std::filesystem::path fileName)
{
    return std::filesystem::create_directories(fileName);
}

void initFFDirectory(std::filesystem::path dirPath)
{
    std::filesystem::copy(dirPath, dirPath / "ff15");

    createDirectory(dirPath / "ff15/meta");
    createDirectory(dirPath / "ff15/objects");

    std::ofstream lastMod(dirPath / "ff15/meta/LastMod.txt");

    for (auto entry = std::filesystem::recursive_directory_iterator(dirPath); entry != std::filesystem::recursive_directory_iterator(); ++entry)
    {
        if(std::filesystem::is_directory(entry->path()))
        {
            if(entry->path().filename().string()[0] == '.' || entry->path().filename().string() == "ff15")
            {
                entry.disable_recursion_pending();
            }

            continue;
        }

        lastMod << "File: " << entry->path().relative_path().string() << "\n";
        lastMod << "Last Modified: " << std::filesystem::last_write_time(entry->path()) << "\n";
        lastMod << "-----------------------------" << "\n";
    }
}


int main()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    short result = chooseOption(std::string("This is your final destination?\n") + currentPath.string());
    if(result == -1)
    {
        std::cout << "Unexpected error in line " << __LINE__ << "\n";
    }
    else if(result == 1 || result == 0)
    {
        if(result == 0)
        {
            do
            {
                std::cout << "Insert current path\n";
                std::string input;
                std::cin >> input;
                if(!std::filesystem::exists(input))
                {
                    std::cout << "Path is incorrect, nothing here\n";
                }
                else
                {
                    currentPath = input;
                    break;
                }
            }while(true);
        }


        std::filesystem::directory_entry entry{currentPath / "ff15"};
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
                if(createDirectory(currentPath / "ff15"))
                {
                    std::cout << "File created\n";
                    initFFDirectory(currentPath);
                }
                else
                {
                    std::cout << "I couldnt create a directory\n";
                }
            }
        }

    }

    return 0;
}
