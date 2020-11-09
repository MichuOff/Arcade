/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** arcade
*/

#include "arcade.hpp"
#include "ArcadeData.hpp"
#include "Error.hpp"
#include "LibLoader.hpp"
#include "IGames.hpp"
#include "NCurses.hpp"
#include <iostream>
#include <string>
#include <ncurses.h>

//Throw Error(usage)
void usage()
{
    std::string usage("USAGE:\n");

    usage += "\t./arcade [./lib/*.so]\n";
    throw(Error(usage));
}

//Launch the menu
void launchMenu(ArcadeData &data)
{
    LibLoader<IGraph> lib = LibLoader<IGraph>(LIBS_FOLDER + data.getCurrentLib());
    IGraph *graphMenu = lib.init();
    std::vector<IGraph::key> keyPressed;

    choose_name(graphMenu, data, keyPressed);
    display_menu(&graphMenu, data, lib);
    score_page(graphMenu, keyPressed, data);
    lib.stop(graphMenu);
}

//Main function
int arcade(int ac, char **av)
{
    if (ac != 2)
        usage();
    ArcadeData data = ArcadeData(std::string(av[1]));
    data.setCurrentLib(data.getCurrentLib().substr(data.getCurrentLib().rfind("/") + 1));
    launchMenu(data);
    launchGame(data);
    return (SUCCESS);
}

//Main, catch the errors (class Error)
int main(int ac, char **av)
{
    try {
        arcade(ac, av);
    }
    catch (Error const &error) {
        std::cerr << error.what() << std::endl;
        return (ERROR);
    }
    return (SUCCESS);
}