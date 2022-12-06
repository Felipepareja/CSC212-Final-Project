#include <iostream>
#include <cstring>
#include <vector>


//Facilitates the game
class Board{
    private:
        int value;
        std::vector<std::string> position_list;

    public:
        Board();
        void print_board();
        std::string consider_moves();
        void white_moves(std::string move);
        void black_moves();
};