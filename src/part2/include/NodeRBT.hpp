#ifndef _NODERBT_H
#define _NODERBT_H

#include <string>

enum class NodeRBTColor {
    BLACK = 0,
    RED = 1,
};

class NodeRBT{

    private:
        NodeRBT *parent{nullptr};
        NodeRBT *left{nullptr};     
        NodeRBT *right{nullptr};
        int key;
        std::string value;
        NodeRBTColor color{NodeRBTColor::BLACK};

    public:
        NodeRBT(int k, std::string v);
        NodeRBT();
        void set_parent(NodeRBT* x);
        void set_left(NodeRBT* x);
        void set_right(NodeRBT* x);
        void set_color(NodeRBTColor color);
        int get_key();
        std::string get_value();
        NodeRBT* get_parent();
        NodeRBT* get_uncle();
        NodeRBT* get_left();
        NodeRBT* get_right();
        NodeRBTColor get_color();
        bool is_red_child_red();
};

#endif