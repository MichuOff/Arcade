/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_OBJECT_
#define NIBBLER_HPP_OBJECT_

#include "IGames.hpp"
#include <chrono>
#include <ctime>

class Nibbler : public IGames {
    public:
        Nibbler();
        ~Nibbler();
        IGames::return_value_t process(std::vector<IGraph::key> keyPressed);
        Map &get_map();

    protected:
    private:
    typedef enum direction_e {
        UP,
        DOWN,
        RIGHT,
        LEFT
    } direction;

        Map::pos addApple();
        void updateDirection(IGraph::key keyPressed);
        void updateChrono();
        void updateSnake();
        void updateApple();
        bool isDead();

        Map _map;
        Map::pos _head;
        std::vector<Map::pos> _body;
        unsigned int _bodySize;
        direction _move;
        bool _changeMove;
        std::vector<Map::pos> _apples;
        int _score;
        std::chrono::time_point<std::chrono::steady_clock> _chronoStart;
        std::chrono::time_point<std::chrono::steady_clock> _chronoEnd;
        bool _loop;
        unsigned int _nbLoop;
};

#endif /* !NIBBLER_HPP_OBJECT_ */
