/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** load_filedir
*/

#include "arcade.hpp"
#include "Error.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

//Return name, for lib_arcade_name.so
std::string getSharedLibName(const std::string &sharedLib)
{
    size_t posName = sharedLib.rfind("_") + 1;
    std::string name(sharedLib.substr(posName, sharedLib.rfind(".so") - posName));

    if (posName == std::string::npos || name.empty())
        throw(Error("getSharedLibName: sharedLib is uncompliant.\n"));
    return (name);
}

//Return the .so of a directory
std::vector<std::string> loadSharedLib(const std::string &dirName)
{
    std::vector<std::string> sharedLib;
    DIR *dirp = opendir(dirName.c_str());
    struct dirent *dirData = NULL;

    if (!dirp)
        usage();
    errno = 0;
    while ((dirData = readdir(dirp))) {
        if (dirData->d_type == DT_REG && 
            std::string(dirData->d_name).find(".so") != std::string::npos &&
            std::string(dirData->d_name).find("lib_arcade_menu.so") == std::string::npos)
            sharedLib.push_back(dirData->d_name);
        errno = 0;
    }
    if (!dirData && errno != 0)
        throw(Error());
    if (closedir(dirp) == -1)
        throw(Error());
    return (sharedLib);
}

//Return the scores of a game
std::vector<std::string> loadScore(const std::string &gameName)
{
    std::vector<std::string> scores;
    std::string path = GAMES_FOLDER + gameName + std::string("/scores.txt");
    std::fstream file(path);
    std::string line("\0");

    if (!file)
        throw(Error());
    while (std::getline(file, line))
        scores.push_back(line);
    if (scores.empty())
        return (scores);
    for (std::string score : scores) {
        if (score.find(" ") != 3 || score.length() != 7)
            throw(Error("Error: " + path + " is uncompliant.\n"));
        if (!std::regex_match(score.substr(4, 3), std::regex{"[0-9]+"}))
            throw(Error("Error: " + path + " is uncompliant.\n"));
    }
    return (scores);
}