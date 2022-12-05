#include "board.h"
int main(){
    Board myBoard;
    std::string move;
    bool running = true;
    while(running){
        myBoard.print_board();
        std::cout << "Enter your move: ";
        std::cin >> move;
        if (islower(move[0])) {
            move[0] = toupper(move[0]);
        }
        if (islower(move[3])) {
            move[3] = toupper(move[3]);
        }
        std::cout << "\n";
        if(move == "quit"){
            running = false;
        }
        myBoard.white_moves(move);
        myBoard.black_moves();
        //myBoard.get_moves(1,1);
    }

}