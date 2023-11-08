#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <format>

int main()
{
    while (true)
    {
        std::cout << "This is your final destination?\n";
        std::cout << std::filesystem::current_path() << std::endl;

        std::cout << "Type y/n \n";

        std::string input;
        std::cin >> input;

        //transform string to lower case
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "y")
        {
            std::filesystem::directory_entry entry{".\\ff15"};
            std::cout << entry << "\n";
            if(entry.exists())
            {
                std::cout << "file exist\n";
            }
            else
            {
                while (true)
                {
                    std::cout << "ff doesnt exist, do you want to init? (y/n)\n";

                    std::string input;
                    std::cin >> input;

                    //transform string to lower case
                    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

                    if (input == "y")
                    {
                        std::filesystem::create_directories("ff15");
                        break;
                    }
                    else if ( input == "n" )
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Unknow command, try again\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }

            const std::filesystem::path sandbox{"sandbox"};
            std::filesystem::create_directories(sandbox/"dir1"/"dir2");
            std::ofstream{sandbox/"file1.txt"};
            std::ofstream{sandbox/"file2.txt"};


            std::cout << "\nrecursive_directory_iterator:\n";
            for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{sandbox})
            {
                std::filesystem::file_time_type ftime = std::filesystem::last_write_time(dir_entry);
                std::cout << std::format("File write time is {}\n", ftime);
                std::cout << dir_entry << '\n';
            }

            // delete the sandbox dir and all contents within it, including subdirs
            //std::filesystem::remove_all(sandbox);
            break;
        }
        else if (input == "n")
        {
            std::cout << "Do smth other" << std::endl;
            break;
        }
        else
        {
            std::cout << "Unknow command, try again\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
