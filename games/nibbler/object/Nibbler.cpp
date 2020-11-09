/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

static std::vector<std::string> NIBBLER_MAP = {
    "+--------------------+",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "|                    |",
    "+--------------------+"
};

static bool isSpace(Nibbler nibbler)
{
    std::vector<std::vector<MapChar>> map = nibbler.get_map().mapData;

    for (size_t y = 0 ; y < map.size(); y++)
        for (size_t x = 0; x < map[y].size(); x++)
            if (map[y][x].c == ' ')
                return true;
    return false;
}

Map::pos Nibbler::addApple()
{
    Map::pos pos;

    pos.x = rand() % 20 + 1;
    pos.y = rand() % 20 + 1;
    for (Map::pos apple : _apples)
        if (apple.x == pos.x && apple.y == pos.y)
            return addApple();
    for (Map::pos body : _body)
        if (body.x == pos.x && body.y == pos.y)
            return addApple();
    _map.fill_str(pos, "6");
    return pos;
}

Nibbler::Nibbler(): _map(Map(55, 30))
{
    Map::pos pos = {0, 0};
    for (std::string line : NIBBLER_MAP) {
        _map.fill_str(pos, line);
        pos.y++;
    }

    _head = {10, 10};
    _map.fill_str(_head, "o");
    _body.push_back(_head);
    _bodySize = 4;
    _move = RIGHT;
    _changeMove = true;
    _apples.push_back(addApple());
    _score = 0;
    _chronoStart = std::chrono::steady_clock::now();
    _chronoEnd = std::chrono::steady_clock::now();
    _loop = false;
    _nbLoop = 0;
    srand(time(0));
}

Nibbler::~Nibbler()
{
}

void Nibbler::updateDirection(IGraph::key keyPressed)
{
    if (!_changeMove)
        return;
    if (keyPressed == IGraph::RightArrow)
        switch (_move) {
            case RIGHT:
                _move = UP;
                break;
            case DOWN:
                _move = RIGHT;
                break;
            case LEFT:
                _move = DOWN;
                break;
            case UP:
                _move = LEFT;
                break;
        }
    if (keyPressed == IGraph::LeftArrow)
    switch (_move) {
            case RIGHT:
                _move = DOWN;
                break;
            case DOWN:
                _move = LEFT;
                break;
            case LEFT:
                _move = UP;
                break;
            case UP:
                _move = RIGHT;
                break;
        }
    _changeMove = false;
}

void Nibbler::updateChrono()
{
    _chronoEnd = std::chrono::steady_clock::now();
    int seconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (_chronoEnd - _chronoStart).count();
    if (seconds >= 400) {
        _chronoStart = std::chrono::steady_clock::now();
        _loop = true;
        _nbLoop++;
    }
}

void Nibbler::updateSnake()
{
    while (_body.size() > _bodySize - 1) {
        _map.fill_str(_body.back(), " ");
        _body.pop_back();
    }
    if (_move == RIGHT || _move == LEFT)
        _map.fill_str(_head, "-");
    if (_move == UP || _move == DOWN)
        _map.fill_str(_head, "|");
    if (_move == RIGHT)
        _head.x++;
    if (_move == LEFT)
        _head.x--;
    if (_move == UP)
        _head.y++;
    if (_move == DOWN)
        _head.y--;
    _map.fill_str(_head, "o");
    _body.insert(_body.begin(), _head);
    while (_body.size() > _bodySize) {
        _map.fill_str(_body.back(), " ");
        _body.pop_back();
    }
}

void Nibbler::updateApple()
{
    std::vector<Map::pos>::iterator it = _apples.begin();

    for ( ; it != _apples.end() ; it++) {
        if (_head.x == (*it).x && _head.y == (*it).y) {
            _apples.erase(it);
            _bodySize++;
            _score++;
            break;
        }}
    if (_apples.empty() && isSpace(*this)) {
        _apples.push_back(addApple());
        _map.fill_str(_apples.back(), "6");
    } else if (rand() % 25 == 0 && isSpace(*this)) {
        _apples.push_back(addApple());
        _map.fill_str(_apples.back(), "6");
    }
}

bool Nibbler::isDead()
{
    std::vector<Map::pos>::iterator it = _body.begin() + 1;

    if (_head.x == 0 || _head.x == 21)
        return true;
    if (_head.y == 0 || _head.y == 21)
        return true;
    for ( ; it != _body.end() ; it++)
        if ((*it).x == _head.x && (*it).y == _head.y)
            return true;
    return false;
}

IGames::return_value_t Nibbler::process(std::vector<IGraph::key> keyPressed)
{
    if (!keyPressed.empty())
        updateDirection(keyPressed[0]);
    updateChrono();
    if (_loop) {
        _loop = false;
        _changeMove = true;
        updateSnake();
        updateApple();
        if (_apples.empty() || isDead())
            return (IGames::return_value_t{MENU, std::to_string(_score)});
    }
    return (IGames::return_value_t{NOTHING, std::to_string(_score)});
}

Map &Nibbler::get_map()
{
    return (_map);
}