#include <iostream>
#include <cstring>
#include <vector>



//acts as the "tree"
class Board{
    private:
        int value;
        std::vector<std::string> position_list;
        std::string get_moves(int row, int col);
        std::vector<std::vector<int>> find_all_moves();

    public:
        Board();
        void print_board();
        std::string consider_moves();
        void white_moves(std::string move);
        void black_moves();
};

//the "node" of the tree
class Position{
    private:
        int value;
        std::vector<Position> next;
        friend class Board;
    public:
        Position();
};