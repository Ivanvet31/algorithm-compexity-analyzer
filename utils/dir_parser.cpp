#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>

#include "dir_parser.h"


std::string getPath()
{
    char cwd[200] = {0};

    getcwd(cwd,  200);

    std::string path = std::string(cwd);

    return path;
}


std::vector<std::string> getDirs(const std::string &path)
{
    std::vector<std::string> dirs;

    for (const std::filesystem::directory_entry &dir : std::filesystem::directory_iterator(path))
    {
        dirs.push_back(dir.path().string());
    }

    return dirs;
}

