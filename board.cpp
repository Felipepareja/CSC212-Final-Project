#include "board.h"
#include "tree.h"

//#include <iostream>

char board[8][8];




Board::Board(){
    //initialize the blank 8x8 board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = 0;
        }
    }

    //set up the pieces!

    //1 == white pawn, P == black pawn
    //2 == white knight, N == black knight
    //3 == white bishop, B == black bishop
    //5 == white rook, R == black rook
    //9 == white queen, Q == black queen
    //0 == white king, K == black king
    
    //pawns
    for(int i = 0; i < 8; i++){
        board[1][i] = 'P';
        board[6][i] = 'p';
    }
    //back rows
    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';

    board[7][0] = 'r';
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'q';
    board[7][4] = 'k';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';
}
//takes a piece, then returns what the visual for that piece should be
std::string pieceConversion(char c){
    std::string r = " ";
    switch(c){
        case 'R': r = "\033[31mR" ;break;
        case 'N': r = "\033[31mN" ;break;
        case 'B': r = "\033[31mB" ;break;
        case 'Q': r = "\033[31mQ" ;break;
        case 'K': r = "\033[31mK" ;break;
        case 'P': r = "\033[31mo" ;break;
        case 'r': r = "\033[37mR" ;break;
        case 'n': r = "\033[37mN" ;break;
        case 'b': r = "\033[37mB" ;break;
        case 'q': r = "\033[37mQ" ;break;
        case 'k': r = "\033[37mK" ;break;
        case 'p': r = "\033[37mo" ;break;
    }
    return r;
}

//Helps with conversion of a lettered Column, "A", to its proper vector index.
int alphToNum(char c){
    int num = 0;
    switch(c){
        case 'A': num = 0 ;break;
        case 'B': num = 1 ;break;
        case 'C': num = 2 ;break;
        case 'D': num = 3 ;break;
        case 'E': num = 4 ;break;
        case 'F': num = 5 ;break;
        case 'G': num = 6 ;break;
        case 'H': num = 7 ;break;
    }
    return num;
}
//Helps to convert an input number into its correct vector index.
int convertRow(int r){
    r -= 1;
    r = 7 - r;
    return r;
}

void Board::white_moves(std::string move){
    //Break down the users moves into sections.

    //First find the piece being moved, make sure it exists at the
    //specified location, and then move it to the desired square.
    //D6-E4
    int col = alphToNum(move[0]);// = //colChar - 17;
    int row = convertRow(move[1] - '0');
    
    int destCol = alphToNum(move[3]);
    int destRow = convertRow(move[4] - '0');


    char temp = board[row][col];
    board[row][col] = 0;
    board[destRow][destCol] = temp;
    
    //std::cout << col << row << "-" << destCol << destRow << "\n";
}

//the logic behind black's moves.
void Board::black_moves(){
    //a vector or list that will hold all possible moves IN NODE FORM.
    
    //Position pos;


    
    std::vector<std::vector<int>> moves = find_all_moves();
    //move every single move based on depth number, prolly 2. 
    //add it as a node.
    //then add nodes to that node.

    //replace something to be recursive eventually
    
    Tree moveTree;

    for(int i = 0; i < moves.size(); i++){
        Node * node = new Node(moves[i]);
        moveTree.insert(node);
    }

    int maxScore = -1000;
    int maxIndex = rand() % moves.size();

    moveTree.print();

    std::vector<int> bestMove = moveTree.get_best_move();
    board[bestMove[2]][bestMove[3]] = board[bestMove[0]][bestMove[1]];
    board[bestMove[0]][bestMove[1]] = 0;
    //std::cout << "Node: " << moveTree.root;
    //moveTree.print();
    /*
    int randoMove = rand() % moves.size();
    board[moves[randoMove][2]][moves[randoMove][3]] = board[moves[randoMove][0]][moves[randoMove][1]];
    board[moves[randoMove][0]][moves[randoMove][1]] = 0;
    */
}

//gets all possible moves for a piece at a position
std::string Board::get_moves(int row, int col){
    char piece = board[row][col];
    std::cout << "the piece: " << piece;
    piece = tolower(piece);
    std::cout << "the new piece: " << piece << "\n";

    switch(piece){
        case 'P':
            if(board[col+1][row] == 'O'){
                
            }
            ;break;
    }
    return "yes";
}

void Board::print_board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i+j)%2==0){
                std::cout << "\033[47m";
            }
            else{
                std::cout << "\033[40m";
            }
            std::cout << " " << pieceConversion(board[i][j]) << "\033[37m"  << " ";
        }
        std::cout << "\033[40m";
        std::cout << "\n";
    }
}

bool is_free(int row, int col){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    if(board[row][col] == 0){
        return true;
    }
    return false;
}

bool is_takeable(int row, int col){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    char space = board[row][col];
    if(space == 0 || space == 'p' || space == 'r' || space == 'n' || space == 'b' || space == 'q' || space == 'k'){
        return true;
    }
    return false;
}




Position::Position(){

}
int pos_eval(char piece){
    switch(piece){
        case 'r': return -5;
        case 'n': return -3;
        case 'b': return -3;
        case 'q': return -9;
        case 'k': return -50;
        case 'p': return -1;
        case 'P': return 1;
        case 'R': return 5;
        case 'N': return 3;
        case 'B': return 3;
        case 'Q': return 9;
        case 'K': return 50;
    }
    return 0;
}
std::vector<int> add_position(int x, int y, int xx, int yy){
    std::vector<int> temp;

    char car = board[xx][yy];
    board[xx][yy] = board[x][y];
    board[x][y] = 0;
    int score = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            score += pos_eval(board[i][j]);
        }
    }
    temp.push_back(x);
    temp.push_back(y);
    temp.push_back(xx);
    temp.push_back(yy);
    
    temp.push_back(score);

    board[x][y] = board[xx][yy];
    board[xx][yy] = car;

    return temp;
}

std::vector<std::vector<int>> Board::find_all_moves(){
    //positional score:

    //std::cout << "Score: " << score << "\n";
    //Generate nodes for each possible move, store them in vector
    std::vector<std::vector<int>> moves;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != 0){
                switch(board[i][j]){
                    case 'P':
                        if(is_free(i+1,j)){
                            //std::vector<int> temp = ;
                            moves.push_back(add_position(i,j,i+1,j));
                        }
                        if(!is_free(i+1,j+1) && is_takeable(i+1,j+1)){
                            moves.push_back(add_position(i,j,i+1,j+1));
                        }
                        if(!is_free(i+1,j-1) && is_takeable(i+1,j-1)){
                            moves.push_back(add_position(i,j,i+1,j-1));
                        }
                        break;
                    case 'R': //ROOK MOVES
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j)){
                                moves.push_back(add_position(i,j,i+dis,j));
                                if(!is_free(i+dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j)){
                                moves.push_back(add_position(i,j,i-dis,j));
                                if(!is_free(i-dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j-dis)){
                                moves.push_back(add_position(i,j,i,j-dis));
                                if(!is_free(i,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j+dis)){
                                moves.push_back(add_position(i,j,i,j+dis));
                                if(!is_free(i,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'B':
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j+dis)){
                                moves.push_back(add_position(i,j,i+dis,j+dis));
                                if(!is_free(i+dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j+dis)){
                                moves.push_back(add_position(i,j,i-dis,j+dis));
                                if(!is_free(i-dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j-dis)){
                                moves.push_back(add_position(i,j,i+dis,j-dis));
                                if(!is_free(i+dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j-dis)){
                                moves.push_back(add_position(i,j,i-dis,j-dis));
                                if(!is_free(i-dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'Q':
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j+dis)){
                                moves.push_back(add_position(i,j,i+dis,j+dis));
                                if(!is_free(i+dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j+dis)){
                                moves.push_back(add_position(i,j,i-dis,j+dis));
                                if(!is_free(i-dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j-dis)){
                                moves.push_back(add_position(i,j,i+dis,j-dis));
                                if(!is_free(i+dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j-dis)){
                                moves.push_back(add_position(i,j,i-dis,j-dis));
                                if(!is_free(i-dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        //STRAIGHTS
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j)){
                                moves.push_back(add_position(i,j,i+dis,j));
                                if(!is_free(i+dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j)){
                                moves.push_back(add_position(i,j,i-dis,j));
                                if(!is_free(i-dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j-dis)){
                                moves.push_back(add_position(i,j,i,j-dis));
                                if(!is_free(i,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j+dis)){
                                moves.push_back(add_position(i,j,i,j+dis));
                                if(!is_free(i,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'N':
                        if(is_takeable(i-2,j-1)){
                            moves.push_back(add_position(i,j,i-2,j-1));
                        }
                        if(is_takeable(i-1,j-2)){
                            moves.push_back(add_position(i,j,i-1,j-2));
                        }
                        if(is_takeable(i+1,j-2)){
                            moves.push_back(add_position(i,j,i+1,j-2));
                        }
                        if(is_takeable(i+2,j-1)){
                            moves.push_back(add_position(i,j,i+2,j-1));
                        }
                        if(is_takeable(i+2,j+1)){
                            moves.push_back(add_position(i,j,i+2,j+1));
                        }
                        if(is_takeable(i+1,j+2)){
                            moves.push_back(add_position(i,j,i+1,j+2));
                        }
                        if(is_takeable(i-1,j+2)){
                            moves.push_back(add_position(i,j,i-1,j+2));
                        }
                        if(is_takeable(i-2,j+1)){
                            moves.push_back(add_position(i,j,i-2,j+1));
                        }
                        ;break;
                    case 'K':

                        break;
                }
            }
        }
    }
    /*
    for(int i = 0; i < moves.size(); i++){
    for(int j = 0; j < moves[i].size(); j ++){
        std::cout << moves[i][j] << " ";
    }
    std::cout << "\n";
    }
    */
    return moves;

    //int randoMove = rand() % moves.size();
    //board[moves[randoMove][2]][moves[randoMove][3]] = board[moves[randoMove][0]][moves[randoMove][1]];
    //board[moves[randoMove][0]][moves[randoMove][1]] = 0;
    //char temp = board[moves[randoMove][0]][moves[randoMove][1]]
}