/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_OBJECT_
#define PACMAN_HPP_OBJECT_

#include "IGames.hpp"
#include <chrono>
#include <ctime>

class Pacman : public IGames {
    public:
        Pacman();
        ~Pacman();
        IGames::return_value_t process(std::vector<IGraph::key> keyPressed);
        Map &get_map();

    protected:
    private:
        enum GHOST_STATE {
			CHASING,
			RUNNING,
			SLEEPING
		};

        int update_pacman(void);
        int move_pacman(int, int);
        void update_ghost(int);
        void move_ghost(int, std::vector<int>);
        void go_back(int);
        int verif_pos(int, int);
        void recup_direction(IGraph::key);
        int check_collision();
        std::string recup_pos(Map::pos);
        int check_win(void);
        IGames::return_value_t reset(void);

        Map _map;
        Map::pos _pacman;
        std::vector<Map::pos> _ghost;
        std::vector<GHOST_STATE> _ghost_state;
        std::vector<int> algo;
        int score;
        int direction;
        int speed_pacman;
        int speed_ghost;
        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point time_pacman;
        std::chrono::steady_clock::time_point time_ghost;
};

#endif /* !PACMAN_HPP_OBJECT_ */
