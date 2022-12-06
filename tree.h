#include <string>
#include <iostream>
#include <vector>


//Each possible position is represented as a node to the AI
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
        void insert(Node *node);
        void find_all_moves(Node *node, int color);
        Node* add_position(int x, int y, int xx, int yy, int color);
        std::vector<int> get_best_move(Node* node,int color);
        std::vector<int> choose_good_move(Node* node);
};


class Tree{
    private:
        Node * root;
        friend class Node;
    public:
        Tree();
        void insert(Node *node);
        void print();
};