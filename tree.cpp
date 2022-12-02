#include "tree.h"

Tree::Tree(){
    this->root = nullptr;
}

void Tree::insert(Node* node){
    if(this->root == nullptr){
        this->root = node;
        return;
    }
    this->root->insert(node);
    
    return;
    //this->root->nexts.push_back(node);
}

std::vector<int> Tree::get_best_move(){
    std::vector<Node*> vec = this->root->nexts;
    std::vector<int> moveVec = vec[vec.size()-1]->vect;

    return moveVec;
}

void Tree::print(){
    if(!this->root){
        return;
    }
    std::vector<Node *> vecto = this->root->nexts;
    //std::cout << "This worked!\n";

    //while(current){
    //    std::cout << "Node: " << current->name << "\n";
    for(int i = 0; i < vecto.size(); i++){
        //std::cout << "This worked!2\n";
        vecto[i]->print();
    }
    //}
}

void Node::insert(Node * node){
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
    name = std::to_string(vec[0]) + std::to_string(vec[1]) + "-" = std::to_string(vec[2]) + std::to_string(vec[3]);
    vect = vec;
    score = vec[4];
    std::vector<Node*> nexts;
}

void Node::print(){
    //std::cout << "My Score: " << score << "|" << "\n";
}