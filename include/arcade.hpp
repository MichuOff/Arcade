/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include "LibLoader.hpp"
#include "ArcadeData.hpp"
#include <iostream>
#include <vector>

typedef enum status_e {
    SUCCESS = 0,
    ERROR = 84
} status;

typedef struct arcade_s {
    int let1;
    int let2;
    int let3;
    std::string name;
} arcade_t;

static const std::string LIBS_FOLDER = std::string("./lib/");
static const std::string GAMES_FOLDER = std::string("./games/");

//arcade.cpp
int main(int ac, char **av);
int arcade(int ac, char **av);
void usage();
void launchMenu(ArcadeData &data);

//menu_display.cpp
void display_menu(IGraph **graph_menu, ArcadeData &data, LibLoader<IGraph> &lib);

//menu_name.cpp
void choose_name(IGraph *graph_menu, ArcadeData &data, std::vector<IGraph::key> &keyPressed);

//score_page.cpp
void score_page(IGraph *graph_menu, std::vector<IGraph::key> &keyPressed, ArcadeData &data);

//load_filedir.cpp
std::string getSharedLibName(const std::string &sharedLib);
std::vector<std::string> loadSharedLib(const std::string &dirName);
std::vector<std::string> loadScore(const std::string &gameName);

//launch_game.cpp
void launchGame(ArcadeData &data);

#endif /* !ARCADE_HPP_ */
