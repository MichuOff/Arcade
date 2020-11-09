/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeData
*/

#include "ArcadeData.hpp"
#include "arcade.hpp"
#include "Error.hpp"
#include "IGraph.hpp"
#include "IGames.hpp"
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>
#include <string>

//Arcade Constructor
ArcadeData::ArcadeData(const std::string &libname):
_currentLib(libname), _currentGame("NULL"), _currentScore(0)
{
    _libs = loadSharedLib(LIBS_FOLDER);
    _games = loadSharedLib(GAMES_FOLDER);
    if (_libs.empty() || _games.empty())
        throw(Error("Error: shared library unfound.\n"));
    _currentGame = _games.front();
    _scores = loadScore(getSharedLibName(_currentGame));
}

ArcadeData::~ArcadeData()
{
}

void ArcadeData::addScore() const
{
    std::string gameName(getSharedLibName(_currentGame));
    std::string path = GAMES_FOLDER + gameName + std::string("/scores.txt");
    std::fstream file(path, std::ios::app);
    char buf[4] = "000";

    if (!file)
        throw(Error());
    if (_currentScore > 999)
        throw(Error("_currentScore is too big.\n"));
    sprintf(buf, "%03d", _currentScore);
    file << _username.substr(0, 3);
    file << " ";
    file << buf;
    file << std::endl;
}

std::vector<std::string> ArcadeData::sortScores() const
{
    std::vector<std::string> tmp;
    std::vector<std::string> sorted;

    for (std::string score : _scores) {
        std::string rString(score.substr(4, 3) + " " + score.substr(0, 3));
        tmp.push_back(rString);
    }
    std::sort(tmp.begin(), tmp.end(), std::greater<std::string>());
    for (std::string elem : tmp) {
        std::string rString(elem.substr(4, 3) + " " + elem.substr(0, 3));
        sorted.push_back(rString);
    }
    return sorted;
}

void ArcadeData::changeLib(int move)
{
    int nbLib = 0;
    int pos = 0;

    for (std::string lib : _libs)
        nbLib++;
    for (std::string lib : _libs) {
        if (lib.find(_currentLib) != std::string::npos)
            break;
        pos++;
    }
    int newPos = pos + move;
    if (newPos < 0)
        newPos = nbLib + move;
    if (newPos >= nbLib)
        newPos = -1 + move;
    _currentLib = _libs[newPos];
}

void ArcadeData::changeGame(int move)
{
    int nbGame = 0;
    int pos = 0;

    for (std::string game : _games)
        nbGame++;
    for (std::string game : _games) {
        if (game.find(_currentGame) != std::string::npos)
            break;
        pos++;
    }
    int newPos = pos + move;
    if (newPos < 0)
        newPos = nbGame + move;
    if (newPos >= nbGame)
        newPos = -1 + move;
    _currentGame = _games[newPos];
}