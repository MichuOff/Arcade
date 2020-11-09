/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGames
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <vector>
#include "Map.hpp"
#include "MapChar.hpp"
#include "IGraph.hpp"

class IGames {
    public:
        enum return_type {
            NOTHING,
            PREV_LIB,
            NEXT_LIB,
            CHANGE_LIB,
            PREV_GAME,
            NEXT_GAME,
            CHANGE_GAME,
            RESTART,
            MENU,
            EXIT
        };
        typedef struct return_value_s {
            return_type type;
            std::string value;
        } return_value_t;

        virtual ~IGames() = default;
        virtual return_value_t process(std::vector<IGraph::key> keyPressed) = 0;
        virtual Map &get_map() = 0;
    protected:
    private:
        int score;
};

#endif /* !IGAMES_HPP_ */
