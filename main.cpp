#include "board.h"
#include <iostream>

int main(){
    Board myBoard;
    std::string move;
    bool running = true;
    while(running){
        myBoard.print_board();
        std::cout << "Enter your move: ";
        std::cin >> move;
        std::cout << "\n";
        if(move == "quit"){
            running = false;
        }
        myBoard.white_moves(move);
        myBoard.black_moves();
        //myBoard.get_moves(1,1);
    }

}