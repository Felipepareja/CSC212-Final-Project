#include "tree.h"

Tree::Tree(){
    this->root = nullptr;
}

void Tree::insert(Node*node){
    if(this->root == nullptr){
        this->root = node;
        return;
    }
    this->root->insert(node);
    
    return;
    //this->root->nexts.push_back(node);
}

//function to choose blacks final decision move. Randomizes for variety!
std::vector<int> Node::choose_good_move(Node * node){
    std::vector<Node*> vec = node->nexts;
    Node* finalNode;
    finalNode = vec[vec.size()-1];
    int current = vec.size()-1;
    while(finalNode->score == vec[current-1]->score){
        if(current == 1) break;
        current -= 1;
        if(rand()%5 == 1){
            break;
        }
    }

    
    finalNode = vec[current];

    std::vector<int> moveVec = finalNode->vect;
    return moveVec;
}

//Gets the best move from a Node's leaves.
std::vector<int> Node::get_best_move(Node * node, int color){
    std::vector<Node*> vec = node->nexts;
    Node* finalNode;
    if(color == 0){
        finalNode = vec[vec.size()-1];
    }
    else{
        finalNode = vec[0];
    }
    std::vector<int> moveVec = finalNode->vect;
    return moveVec;
}

void Tree::print(){
    if(!this->root){
        return;
    }
    std::vector<Node*> vecto = this->root->nexts;

    //}
}

void Node::insert(Node *node){
    if(nexts.size() == 0){
        nexts.push_back(node);
        return;
    }
    if(node->score < nexts[0]->score){
        nexts.insert(nexts.begin(),1,node);
        return;
    }
    if(node->score > nexts[nexts.size()-1]->score){
        nexts.push_back(node);
        return;
    }
    
    nexts.insert(nexts.begin() + nexts.size() / 2,1,node);
    return;
}

Node::Node(std::vector<int> vec){
    this->name = std::to_string(vec[0]) + std::to_string(vec[1]) + "-" + std::to_string(vec[2]) + std::to_string(vec[3]);
    this->vect = vec;
    this->score = vec[4];
    //std::cout << vec[4] << "\n";
    std::vector<Node*> nexts;
}

void Node::print(){
    //std::cout << "My Score: " << this->score << "|" << "\n";
    for(int i = 0; i < this->nexts.size(); i++){
        Node * current = this->nexts[i];
        std::cout << current->score << " Name: " <<current->name << ": ";
        for(int j = 0; j < this->nexts[i]->vect.size()-1; j++){
            std::cout << this->nexts[i]->vect[j];
            if(j==1) std::cout<<"-";
        }
        std::cout <<"\n";
    }
}