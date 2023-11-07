#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <format>

int main()
{
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
    std::filesystem::remove_all(sandbox);
}

