/*
** EPITECH PROJECT, 2020
** Pacman
** File description:
** Pacman
*/

#include "Pacman.hpp"

static std::vector<std::string> PACMAN_MAP = {
    "   +---------------------+    ",
	"   |XXXXXXXXXXXXXXXXXXXXX|   ",
	"   |X.........X.........X|   ",
	"   |X.XXX.XXX.X.XXX.XXX.X|   ",
	"   |XoX X.X X.X.X X.X XoX|   ",
	"   |X.XXX.XXX.X.XXX.XXX.X|   ",
	"   |X...................X|   ",
	"   |X.XXX.X.XXXXX.X.XXX.X|   ",
	"   |X.XXX.X.XXXXX.X.XXX.X|   ",
	"   |X.....X...X...X.....X|   ",
	"   |XXXXX.XXX X XXX.XXXXX|   ",
	"   |     X X       X X   |   ",
	"   |    X.X XX XX X.X    |   ",
	"   |XXXXX.X X   X X.XXXXX|   ",
	"   |X    .  X   X  .    X|   ",
	"   |XXXXX.X XXXXX X.XXXXX|   ",
	"   |    X.X       X.X    |   ",
	"   |    X.X XXXXX X.X    |   ",
	"   |XXXXX.X XXXXX X.XXXXX|   ",
	"   |X.........X.........X|   ",
	"   |X.XXX.XXX.X.XXX.XXX.X|   ",
	"   |Xo..X..... .....X..oX|   ",
	"   |XXX.X.X.XXXXX.X.X.XXX|   ",
	"   |XXX.X.X.XXXXX.X.X.XXX|   ",
	"   |X.....X...X...X.....X|   ",
	"   |X.XXXXXXX.X.XXXXXXX.X|   ",
	"   |X...................X|   ",
	"   |XXXXXXXXXXXXXXXXXXXXX|   ",
    "   +---------------------+   "
};
static std::vector<std::string> CPY_MAP = PACMAN_MAP;

Pacman::Pacman() : _map(Map(55, 35))
{
    PACMAN_MAP = CPY_MAP;
    Map::pos pos = {0, 0};
    for (std::string line : PACMAN_MAP) {
        this->_map.fill_str(pos, line);
        pos.y++;
    }
    this->score = 0;
    this->_map.fill_str(Map::pos{14, 12}, "X");
    this->_pacman = {14, 21};
    this->_map.fill_str(_pacman, "P");

    for (int i = 0; i < 3; i++) {
        this->_ghost.push_back(Map::pos{13 + i, 14});
        this->_ghost_state.push_back(SLEEPING);
        this->algo.push_back(1); 
    }
    for (Map::pos g : this->_ghost)
        this->_map.fill_str(g, "g");

    this->start = std::chrono::steady_clock::now();
    this->time_pacman = std::chrono::steady_clock::now();
    this->time_ghost = std::chrono::steady_clock::now();
    this->speed_pacman = 500;
    this->speed_ghost = 500;
    srand(time(0));
}

Pacman::~Pacman()
{
}

IGames::return_value_t Pacman::reset(void)
{
    PACMAN_MAP = CPY_MAP;
    Map::pos pos = {0, 0};
    for (std::string line : PACMAN_MAP) {
        this->_map.fill_str(pos, line);
        pos.y++;
    }
    this->_map.fill_str(Map::pos{0, 30}, "score " + std::to_string(this->score));
    this->_map.fill_str(Map::pos{14, 12}, "X");
    this->_pacman = {14, 21};
    this->_map.fill_str(_pacman, "P");

    for (size_t i = 0; i < this->_ghost.size(); i++) {
        this->_ghost[i] = Map::pos{13 + int(i), 14};
        this->_ghost_state[i] = SLEEPING;
        this->algo[i] = 1; 
    }
    for (Map::pos g : this->_ghost)
        this->_map.fill_str(g, "g");

    this->start = std::chrono::steady_clock::now();
    this->time_pacman = std::chrono::steady_clock::now();
    this->time_ghost = std::chrono::steady_clock::now();
    this->speed_pacman /= 2;
    this->speed_ghost /= 2;
    srand(time(0));
    return (IGames::return_value_t{NOTHING, std::to_string(this->score)});
}

int Pacman::check_win(void)
{
    for (std::vector<MapChar> vec : this->_map.mapData) {
        for (MapChar elem : vec) {
            if (elem.c == '.')
                return 0;
        }
    }
    return 1;
}

std::string Pacman::recup_pos(Map::pos pos)
{
    std::string result(1, PACMAN_MAP.at(pos.y).at(pos.x));
    return result;
}

int Pacman::verif_pos(int b, int a)
{
    if (this->_map.mapData.at(a).at(b).c == 'X')
        return 0;
    else if (this->_map.mapData.at(a).at(b).c == 'G')
        return 1;
    else if (this->_map.mapData.at(a).at(b).c == 'g')
        return 2;
    else if (this->_map.mapData.at(a).at(b).c == ' ')
        return 3;
    else if (this->_map.mapData.at(a).at(b).c == '.')
        return 4;
    else if (this->_map.mapData.at(a).at(b).c == 'o')
        return 5;
    else
        return 6;
}

int Pacman::check_collision()
{
    for (size_t i = 0; i < this->_ghost.size(); i++) {
        if (this->_pacman.x == this->_ghost[i].x && this->_pacman.y == this->_ghost[i].y) {
            if (this->_ghost_state[i] == CHASING)
                return 1;
            if (this->_ghost_state[i] == RUNNING) {
                this->_ghost_state[i] = SLEEPING;
                this->_ghost[i].x = 13 + i;
                this->_ghost[i].y = 14;
                this->_map.fill_str(this->_ghost[i], "g");
            }
        }
    }
    return 0;
}

void Pacman::go_back(int nb)
{
    if (this->algo[nb] == 0) {
        if (verif_pos(this->_ghost[nb].x, this->_ghost[nb].y - 1) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].y--;
            this->algo[nb] = 1;
        }
    }
    else if (this->algo[nb] == 1) {
        if (verif_pos(this->_ghost[nb].x, this->_ghost[nb].y + 1) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].y++;
            this->algo[nb] = 0;
        }
    }
    else if (this->algo[nb] == 2) {
        if (verif_pos(this->_ghost[nb].x + 1, this->_ghost[nb].y) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].x++;
            this->algo[nb] = 3;
        }
    }
    else if (this->algo[nb] == 3) {
        if (verif_pos(this->_ghost[nb].x - 1, this->_ghost[nb].y) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].x--;
            this->algo[nb] = 2;
        }
    }
}

void Pacman::move_ghost(int nb, std::vector<int> move)
{
    int direction = rand() % 4;

    if (move == std::vector<int>{0, 0, 0, 0}) {
        go_back(nb);
        return;
    }

    while (!move[direction])
        direction = rand() % 4;

    if (direction == 0) {
        if (verif_pos(this->_ghost[nb].x, this->_ghost[nb].y - 1) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].y--;
            this->algo[nb] = 1;
            return;
        }
    }
    else if (direction == 1) {
        if (verif_pos(this->_ghost[nb].x, this->_ghost[nb].y + 1) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].y++;
            this->algo[nb] = 0;
            return;
        }
    }
    else if (direction == 2) {
        if (verif_pos(this->_ghost[nb].x + 1, this->_ghost[nb].y) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].x++;
            this->algo[nb] = 3;
            return;
        }
    }
    else if (direction == 3) {
        if (verif_pos(this->_ghost[nb].x - 1, this->_ghost[nb].y) >= 3) {
            this->_map.fill_str(this->_ghost[nb], recup_pos(_ghost[nb]));
            this->_ghost[nb].x--;
            this->algo[nb] = 2;
            return;
        }
    }
    move[direction] = 0;
    move_ghost(nb, move);
}

void Pacman::update_ghost(int nb)
{
    auto now = std::chrono::steady_clock::now();
	auto time_spawn = std::chrono::duration_cast<std::chrono::seconds>(now - this->start);
    std::vector<int> move{1, 1, 1, 1};

    if (time_spawn.count() > 10)
        this->_map.fill_str(Map::pos{14, 12}, " ");
    if (time_spawn.count() > 10 && this->speed_ghost != this->speed_pacman)
        this->speed_ghost = this->speed_pacman;
    if (this->_ghost_state[nb] == SLEEPING) {
        this->_ghost[nb].x = 13 + nb;
        this->_ghost[nb].y = 14;
		if (time_spawn.count() > 10)
			this->_ghost_state[nb] = CHASING;
    }
    if (this->_ghost_state[nb] == RUNNING) {
		if (time_spawn.count() > 10)
			this->_ghost_state[nb] = CHASING;
    }
    if (this->_ghost_state[nb] != SLEEPING) {
        move[this->algo[nb]] = 0;
        move_ghost(nb, move);
    }

    if (this->_ghost_state[nb] == CHASING)
        this->_map.fill_str(this->_ghost[nb], "G");
    if (this->_ghost_state[nb] == RUNNING || this->_ghost_state[nb] == SLEEPING)
        this->_map.fill_str(this->_ghost[nb], "g");
}

int Pacman::move_pacman(int a, int b)
{
    int result = verif_pos(a, b);

    if (!result)
        return 0;

    if (result > 0) {
        if (result >= 4)
            this->score++;
        if (result >= 5) {
            this->start = std::chrono::steady_clock::now();
            this->speed_ghost *= 2;
            for (size_t i = 0; i < this->_ghost_state.size(); i++)
                this->_ghost_state[i] = RUNNING;
        }
        PACMAN_MAP[this->_pacman.y][this->_pacman.x] = ' ';
        this->_map.fill_str(this->_pacman, " ");
        this->_pacman.x = a;
        this->_pacman.y = b;
    }
    _map.fill_str(this->_pacman, "P");
    this->direction = 0;
    if (check_collision())
        return 1;
    return 0;
}

int Pacman::update_pacman(void)
{
    if (this->direction == 1)
        return move_pacman(this->_pacman.x, this->_pacman.y - 1);
    
    if (this->direction == 2)
        return move_pacman(this->_pacman.x, this->_pacman.y + 1);
    
    if (this->direction == 3)
        return move_pacman(this->_pacman.x + 1, this->_pacman.y);
    
    if (this->direction == 4)
        return move_pacman(this->_pacman.x - 1, this->_pacman.y);
    
    return 0;
}

void Pacman::recup_direction(IGraph::key keyPressed)
{
    if (keyPressed == IGraph::UpArrow)
        this->direction = 1;
    
    if (keyPressed == IGraph::DownArrow)
        this->direction = 2;
    
    if (keyPressed == IGraph::RightArrow)
        this->direction = 3;
    
    if (keyPressed == IGraph::LeftArrow)
        this->direction = 4;
}

IGames::return_value_t Pacman::process(std::vector<IGraph::key> keyPressed)
{   
    auto now = std::chrono::steady_clock::now();
    auto time_move_ghost = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->time_ghost);
    auto time_move_pacman = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->time_pacman);
    //this->_map.fill_str(Map::pos{0, 30}, "score " + std::to_string(this->score));
    
    if (!keyPressed.empty())
        recup_direction(keyPressed[0]);

    if (time_move_ghost.count() > this->speed_ghost) {
        this->time_ghost = now;
        for (size_t i = 0; i < this->_ghost.size(); i++)
            update_ghost(i);
        if (check_collision())
            return (IGames::return_value_t{MENU, std::to_string(this->score)});
    }
    if (time_move_pacman.count() > this->speed_pacman) {
        this->time_pacman = now;
        if (update_pacman())
            return (IGames::return_value_t{MENU, std::to_string(this->score)});
        if (check_win())
            return reset();
    }

    return (IGames::return_value_t{NOTHING, std::to_string(this->score)});
}

Map &Pacman::get_map()
{
    return (_map);
}