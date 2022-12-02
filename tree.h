#include <string>
#include <iostream>
#include <vector>



class Node{
    private:
        std::string name;
        std::vector<int> vect;
        int score;
        std::vector<Node*> nexts;
        friend class Tree;
    public:
        Node(std::vector<int> vec);
        void print();
        void insert(Node * node);
};

class Tree{
    private:
        Node* root;
    public:
        Tree();
        void insert(Node* node);
        void print();
        std::vector<int> get_best_move();
};