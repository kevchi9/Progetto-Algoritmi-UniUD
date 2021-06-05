#ifndef _RBT_H
#define _RBT_H
#include "NodeRBT.hpp"

    enum RBTSide {
        RIGHT = 0,
        LEFT = 1,
    };

    class RBT {
        private:
            NodeRBT* root;

        public:
            RBT();
            void set_root(NodeRBT* root);
            NodeRBT* get_root();

            /**
             * Prints the representation of the tree.
             * 
             * @param x The root of each subtree
             */
            void RBT_Show(NodeRBT *x); //std::string& result

            /**
             * Adds a new NodeRBT to the tree with the given root and then returns the tree's root 
             * 
             * @param root That identifies the tree
             * @param k The key of the new NodeRBT
             * @param v The value of the new NodeRBT
             * @return The root
             */
            void RBT_Insert(int k, std::string v);

            /**
             * Handles the various cases of fixing the RBT after inserting a new node
             * 
             * @param new_node The node added to the RBT.ù 
             */
            void RBT_InsertFix(NodeRBT* new_node);

            NodeRBT* RBT_Insert_PRed_URed(NodeRBT* new_node);
            void RBT_Insert_PRed_UBlack(NodeRBT* new_node);
            void RBT_Insert_PRed_UBlack_LL(NodeRBT* new_node);
            void RBT_Insert_PRed_UBlack_RR(NodeRBT* new_node);

            void RBT_SwapColors(NodeRBT* node1, NodeRBT* node2);

            /**
             * Rotates from its right child towards himself all the subtrees (not recursively)
             * 
             * @param placeh The upper node. (ITS RIGHT CHILD MUST BE NOT NULL)
             */
            void RBT_LeftRotate(NodeRBT* placeh);

            /**
             * Rotates from its left child towards himself all the subtrees (not recursively) 
             * 
             * @param placeh The upper node. (ITS LEFT CHILD MUST BE NOT NULL)
             */
            void RBT_RightRotate(NodeRBT* placeh);

            /**
             * Finds the element specified by the key passed and
             * returns the string contained in that element, if found.
             * 
             * @param root The root of the RBT
             * @param key The key to find in the tree
             * @return  The node in which key is present or
             *          nullptr if key was not found
             */
            NodeRBT* RBT_Find(int key);

            void print_info(NodeRBT* x);

            void RBT_Clear(NodeRBT* x);
    };

#endif