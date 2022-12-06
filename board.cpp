#include "board.h"
#include "tree.h"

//global variables
char board[8][8];
int depth = 3;


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
        case 'r': r = "\033[32mR" ;break;
        case 'n': r = "\033[32mN" ;break;
        case 'b': r = "\033[32mB" ;break;
        case 'q': r = "\033[32mQ" ;break;
        case 'k': r = "\033[32mK" ;break;
        case 'p': r = "\033[32mo" ;break;
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


    depth = 3;
    int color = 0;
    std::vector<int> tempVec = {0,0,0,0,0};

    Node *treeRoot = new Node(tempVec);
    
    treeRoot->find_all_moves(treeRoot, color);
    //move every single move based on depth number 
    //add it as a node.
    //then add nodes to that node.

    //Chooses the move to make, and makes it.
    std::vector<int> bestMove = treeRoot->choose_good_move(treeRoot);
    board[bestMove[2]][bestMove[3]] = board[bestMove[0]][bestMove[1]];
    board[bestMove[0]][bestMove[1]] = 0;
}

// Prints a visual of the board
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

//Checks if there is nothing on a square
bool is_free(int row, int col){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    if(board[row][col] == 0){
        return true;
    }
    return false;
}
//checks if there is an enemy piece on a square
bool is_takeable(int row, int col,int color){
    if(row < 0 || row > 7 || col < 0 || col > 7){
        return false;
    }
    char space = board[row][col];
    if(color == 0){
        if(space == 0 || space == 'p' || space == 'r' || space == 'n' || space == 'b' || space == 'q' || space == 'k'){
            return true;
        }
    }
    if(color == 1){
        if(space == 0 || space == 'P' || space == 'R' || space == 'B' || space == 'K' || space == 'N' || space == 'Q'){
            return true;
        }
    }
    return false;
}


int pos_eval(char piece, int color){
    int val = 0;
    switch(piece){
        case 'r': val = -5 ;break;
        case 'n': val = -3;break;
        case 'b': val = -3;break;
        case 'q': val = -9;break;
        case 'k': val = -50;break;
        case 'p': val = -1;break;
        case 'P': val = 1;break;
        case 'R': val = 5;break;
        case 'N': val = 3;break;
        case 'B': val = 3;break;
        case 'Q': val = 9;break;
        case 'K': val = 50;break;
    }
    if(color == 1){
        return val;
    }
    return val;
}
Node* Node::add_position(int x, int y, int xx, int yy, int color){
    std::vector<int> temp;

    char car = board[xx][yy];
    board[xx][yy] = board[x][y];
    board[x][y] = 0;
    int score = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            score += pos_eval(board[i][j],color);
        }
    }
    temp.push_back(x);
    temp.push_back(y);
    temp.push_back(xx);
    temp.push_back(yy);
    temp.push_back(score);

    depth -= 1;
    Node * node = new Node(temp);
    
    if(depth >= 0){
        find_all_moves(node,!color);
        
        std::vector<int> best_move = get_best_move(node,!color);
        node->score = best_move[4];
    }
    depth += 1;

    board[x][y] = board[xx][yy];
    board[xx][yy] = car;


    return node;
}

void Node::find_all_moves(Node* node, int color){

    //If we are calculating whites potential next moves, color = 1
    //color = 0 when we calculate blacks moves

    
    //Generate nodes for each possible move, store them in vector
    std::vector<std::vector<int>> moves;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != 0){
                switch(board[i][j]){
                    case 'P':
                        if(color == 1) break;

                        if(is_free(i+1,j)){
                            node->insert(add_position(i,j,i+1,j,color));
                        }
                        if(is_free(i+2,j) && is_free(i+1,j) && i==1){
                            node->insert(add_position(i,j,i+2,j,color));
                        }
                        if(!is_free(i+1,j+1) && is_takeable(i+1,j+1,color)){
                            node->insert(add_position(i,j,i+1,j+1,color));
                        }
                        if(!is_free(i+1,j-1) && is_takeable(i+1,j-1,color)){
                            node->insert(add_position(i,j,i+1,j-1,color));
                        }
                        break;
                    case 'p':
                        if(color == 0) break;

                        if(is_free(i-1,j)){
                            node->insert(add_position(i,j,i-1,j,color));
                        }
                        if(is_free(i-2,j) && is_free(i-1,j) && i == 6){
                            node->insert(add_position(i,j,i-2,j,color));
                        }
                        if(!is_free(i-1,j+1) && is_takeable(i-1,j+1,color)){
                            node->insert(add_position(i,j,i-1,j+1,color));
                        }
                        if(!is_free(i-1,j-1) && is_takeable(i-1,j-1,color)){
                            node->insert(add_position(i,j,i-1,j-1,color));
                        }
                        break;
                    case 'r': if(color == 0) break;
                    case 'R': //ROOK MOVES
                            if(color == 1 && board[i][j] == 'R') break;
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j,color)){
                                node->insert(add_position(i,j,i+dis,j,color));
                                if(!is_free(i+dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j,color)){
                                node->insert(add_position(i,j,i-dis,j,color));
                                if(!is_free(i-dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j-dis,color)){
                                node->insert(add_position(i,j,i,j-dis,color));
                                if(!is_free(i,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j+dis,color)){
                                node->insert(add_position(i,j,i,j+dis,color));
                                if(!is_free(i,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'b': if(color == 0) break;
                    case 'B':
                        if(color == 1 && board[i][j] == 'B') break;
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j+dis,color)){
                                node->insert(add_position(i,j,i+dis,j+dis,color));
                                if(!is_free(i+dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j+dis,color)){
                                node->insert(add_position(i,j,i-dis,j+dis,color));
                                if(!is_free(i-dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j-dis,color)){
                                node->insert(add_position(i,j,i+dis,j-dis,color));
                                if(!is_free(i+dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j-dis,color)){
                                node->insert(add_position(i,j,i-dis,j-dis,color));
                                if(!is_free(i-dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'q': if(color == 0) break;
                    case 'Q':
                        if(color == 1 && board[i][j] == 'Q') break;
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j+dis,color)){
                                node->insert(add_position(i,j,i+dis,j+dis,color));
                                if(!is_free(i+dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j+dis,color)){
                                node->insert(add_position(i,j,i-dis,j+dis,color));
                                if(!is_free(i-dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i+dis,j-dis,color)){
                                node->insert(add_position(i,j,i+dis,j-dis,color));
                                if(!is_free(i+dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j-dis,color)){
                                node->insert(add_position(i,j,i-dis,j-dis,color));
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
                            if(is_takeable(i+dis,j,color)){
                                node->insert(add_position(i,j,i+dis,j,color));
                                if(!is_free(i+dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i-dis,j,color)){
                                node->insert(add_position(i,j,i-dis,j,color));
                                if(!is_free(i-dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j-dis,color)){
                                node->insert(add_position(i,j,i,j-dis,color));
                                if(!is_free(i,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 8; dis++){
                            if(is_takeable(i,j+dis,color)){
                                node->insert(add_position(i,j,i,j+dis,color));
                                if(!is_free(i,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                    case 'n': if(color == 0) break;
                    case 'N':
                        if(color == 1 && board[i][j] == 'N') break;
                        if(is_takeable(i-2,j-1,color)){
                            node->insert(add_position(i,j,i-2,j-1,color));
                        }
                        if(is_takeable(i-1,j-2,color)){
                            node->insert(add_position(i,j,i-1,j-2,color));
                        }
                        if(is_takeable(i+1,j-2,color)){
                            node->insert(add_position(i,j,i+1,j-2,color));
                        }
                        if(is_takeable(i+2,j-1,color)){
                            node->insert(add_position(i,j,i+2,j-1,color));
                        }
                        if(is_takeable(i+2,j+1,color)){
                            node->insert(add_position(i,j,i+2,j+1,color));
                        }
                        if(is_takeable(i+1,j+2,color)){
                            node->insert(add_position(i,j,i+1,j+2,color));
                        }
                        if(is_takeable(i-1,j+2,color)){
                            node->insert(add_position(i,j,i-1,j+2,color));
                        }
                        if(is_takeable(i-2,j+1,color)){
                            node->insert(add_position(i,j,i-2,j+1,color));
                        }
                        ;break;
                    case 'k': if(color == 0) break;
                    case 'K':
                        if(color == 1 && board[i][j] == 'K') break;
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i+dis,j+dis,color)){
                                node->insert(add_position(i,j,i+dis,j+dis,color));
                                if(!is_free(i+dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i-dis,j+dis,color)){
                                node->insert(add_position(i,j,i-dis,j+dis,color));
                                if(!is_free(i-dis,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i+dis,j-dis,color)){
                                node->insert(add_position(i,j,i+dis,j-dis,color));
                                if(!is_free(i+dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i-dis,j-dis,color)){
                                node->insert(add_position(i,j,i-dis,j-dis,color));
                                if(!is_free(i-dis,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        //STRAIGHTS
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i+dis,j,color)){
                                node->insert(add_position(i,j,i+dis,j,color));
                                if(!is_free(i+dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i-dis,j,color)){
                                node->insert(add_position(i,j,i-dis,j,color));
                                if(!is_free(i-dis,j)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i,j-dis,color)){
                                node->insert(add_position(i,j,i,j-dis,color));
                                if(!is_free(i,j-dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        for(int dis = 1; dis < 2; dis++){
                            if(is_takeable(i,j+dis,color)){
                                node->insert(add_position(i,j,i,j+dis,color));
                                if(!is_free(i,j+dis)){
                                    break;
                                }
                            }
                            else{
                                break;
                            }
                        }
                        ;break;
                }
            }
        }
    }
}