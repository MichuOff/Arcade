/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ArcadeData
*/

#ifndef ARCADEDATA_HPP_
#define ARCADEDATA_HPP_

#include "LibLoader.hpp"
#include "IGames.hpp"
#include "IGraph.hpp"
#include <iostream>
#include <vector>

class ArcadeData {
    public:
        ArcadeData(const std::string &libName);
        ~ArcadeData();

        //Getter && Setter
        std::vector<std::string> getLibs() const { return _libs; };
        std::string getCurrentLib() const { return _currentLib; };
        std::vector<std::string> getGames() const { return _games; };
        std::string getCurrentGame() const { return _currentGame; };
        std::vector<std::string> getScores() const { return _scores; };
        std::string getUserName() const { return _username; };
        int getCurrentScore() const { return _currentScore; };
        void setCurrentLib(const std::string &lib) { _currentLib = lib; };
        void setCurrentGame(const std::string &game) { _currentGame = game; };
        void setCurrentScore(const int &score) { _currentScore = score; };
        void setUserName(const std::string &username) { _username = username; };
        void setScores(const std::vector<std::string> &scores) { _scores = scores; };

        //Functions
        void addScore() const;
        std::vector<std::string> sortScores() const;
        void changeLib(int move);
        void changeGame(int move);

    protected:
    private:
        //Var
        std::vector<std::string> _libs;
        std::string _currentLib;
        std::vector<std::string> _games;
        std::string _currentGame;
        int _currentScore;
        std::string _username;
        std::vector<std::string> _scores;
};

#endif /* !ARCADEDATA_HPP_ */
