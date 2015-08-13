//
//  BinaryTree.hpp
//  test
//
//  Created by zhangnan on 15/8/11.
//  Copyright (c) 2015ƒÍ zhangnan. All rights reserved.
//

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
#include "Chain.hpp"

namespace data_structure {
    namespace binary_tree {

        template <typename T>
        class Tree;


        template <class T>
        class TreeNode {
            friend Tree<T>;
        private:
            T data_;
            TreeNode* left_;
            TreeNode* right_;
            TreeNode* parent_;
        public:
            TreeNode();
            TreeNode(T& obj);
            ~TreeNode();
        };

        template <class T>
        TreeNode<T>::TreeNode() {
            left_ = NULL;
            right_ = NULL;
            parent_ = NULL;
        }

        template <class T>
        TreeNode<T>::TreeNode(T& obj) {
            data_ = obj;
            left_ = NULL;
            right_ = NULL;
            parent_ = NULL;
        }

        template <class T>
        TreeNode<T>::~TreeNode() {

        }

        template <class T>
        class Tree {
        private:
            TreeNode<T>* node_;
            TreeNode<T>* root_;
            int total_elements_;

            chain::Chain<T>* lstInorder_;
            chain::Chain<T>* lstPreorder_;
            chain::Chain<T>* lstPostorder_;

        private:
            bool InorderTreeWalk(TreeNode<T>*);
            bool PreorderTreeWalk(TreeNode<T>*);
            bool PostorderTreeWalk(TreeNode<T>*);
            bool InorderTreeWalk(T&);
            bool PreorderTreeWalk(T&);
            bool PostorderTreeWalk(T&);

        public:
            Tree();
            ~Tree();

            bool AddRoot(T&);
            bool Insert(T&);

            bool Search(T&, TreeNode<T>** pOut);
            bool Search(T&);
            
            bool Minium(TreeNode<T>*, TreeNode<T>**);
            bool Minium(T&, T&);
            bool Maxium(TreeNode<T>*, TreeNode<T>**);
            bool Maxium(T&, T&);
            
            /*bool Successor(TreeNode<T>*, TreeNode<T>**);
            bool Successor(T&, T&);
            bool Predecessor(TreeNode<T>*, TreeNode<T>**);
            bool Predecessor(T&, T&);*/
            
            TreeNode<T>* Parent(TreeNode<T>*);
            TreeNode<T>* Left(TreeNode<T>*);
            TreeNode<T>* Right(TreeNode<T>*);
            bool Parent(T&, T&);
            bool Left(T&, T&);
            bool Right(T&, T&);
            

            bool DeleteTree(TreeNode<T>*);
            bool DeleteTree(T&);
        };

        template <class T>
        Tree<T>::Tree() {
            node_ = NULL;
            root_ = NULL;
            total_elements_ = 0;

            lstInorder_ = NULL;
            lstPreorder_ = NULL;
            lstPostorder_ = NULL;
        }

        template <class T>
        Tree<T>::~Tree() {
            if (root_) {
                DeleteTree(root_);
                root_ = NULL;
            }

            total_elements_ = 0;

            if (lstInorder_) {
                delete lstInorder_;
                lstInorder_ = NULL;
            }

            if (lstPreorder_) {
                delete lstPreorder_;
                lstPreorder_ = NULL;
            }

            if (lstPostorder_) {
                delete lstPostorder_;
                lstPostorder_ = NULL;
            }
        }


        template <class T>
        bool Tree<T>::AddRoot(T& obj) {
            node_ = new TreeNode<T>;
            if (!node_) {
                return false;
            }

            node_->data_ = obj;
            node_->parent_ = NULL;
            node_->left_ = NULL;
            node_->right_ = NULL;

            root_ = node_;
            total_elements_ = 1;

            return true;
        }

        template <class T>
        bool Tree<T>::Insert(T& obj) {
            if (total_elements_ == 0) {
                return AddRoot(obj);
            }

            node_ = root_;

            while (node_) {
                if (node_->data_ > obj && node_->left_ != NULL) {
                    node_ = node_->left;
                    continue;
                } else if (node_->data < obj && node_->right_ != NULL) {
                    node_ = node_->right;
                    continue;
                } else {
                    break;
                }
            }

            if (node_->data_ == obj) {
                return false;
            }

            TreeNode<T>* newNode = new TreeNode<T>;
            newNode->data_ = obj;
            newNode->left_ = NULL;
            newNode->right_ = NULL;
            newNode->parent_ = node_;

            if (node_->data > obj) {
                node_->left_ = newNode;
            } else {
                node_->right_ = newNode;
            }

            ++total_elements_;
            return true;
        }

        template <class T>
        bool Tree<T>::Search(T& obj) {
            node_ = root_;
            while (node_) {
                if (node_->data_ == obj) {
                    return true;
                } else if (node_->data_ > obj) {
                    node_ = node_->left_;
                    continue;
                } else if (node_->data_ < obj) {
                    node_ = node_->right_;
                    continue;
                }
            }

            return false;
        }
        
        template <class T>
        bool Tree<T>::Search(T& obj, TreeNode<T>** pOut) {
            node_ = root_;
            while (node_) {
                if (node_->data_ == obj) {
                    *pOut = node_;
                    return true;
                } else if (node_->data_ > obj) {
                    node_ = node_->left_;
                    continue;
                } else if (node_->data_ < obj) {
                    node_ = node_->right_;
                    continue;
                }
            }
            
            return false;
        }
        
        template <class T>
        bool Tree<T>::Minium(TreeNode<T>* pNode, TreeNode<T>** pMinNode) {
            if (!pNode || !pNode->left_) {
                return false;
            }
            while (!pNode->left_) {
                pNode = pNode->left_;
            }
            *pMinNode = pNode;
            return true;
        }
        
        template <class T>
        bool Tree<T>::Minium(T& obj, T& objMin) {
            TreeNode<T>* pNode, pMinNode = NULL;
            if (Search(obj, &pNode) == false) {
                return false;
            }
            Minium(pNode, &pMinNode);
            if (!pMinNode) {
                return false;
            } else {
                objMin = pMinNode->data_;
                return true;
            }
        }
        
        template <class T>
        bool Tree<T>::Maxium(TreeNode<T>* pNode, TreeNode<T>** pMaxNode) {
            if (!pNode || !pNode->right_) {
                return false;
            }
            while (!pNode->right_) {
                pNode = pNode->right_;
            }
            *pMaxNode = pNode;
            return true;
        }
        
        template <class T>
        bool Tree<T>::Maxium(T& obj, T& objMax) {
            TreeNode<T>* pNode, pMaxNode = NULL;
            if (Search(obj, &pNode) == false) {
                return false;
            }
            Maxium(pNode, &pMaxNode);
            if (!pMaxNode) {
                return false;
            } else {
                objMax = pMaxNode->data_;
                return true;
            }
        }
        
        /*template <class T>
        bool Tree<T>::Successor(TreeNode<T>* pNode, TreeNode<T>** pOut) {
            
        }*/
        
        template <class T>
        TreeNode<T>* Tree<T>::Parent(TreeNode<T>* pNode) {
            return pNode->parent_;
        }
        
        template <class T>
        TreeNode<T>* Tree<T>::Left(TreeNode<T>* pNode) {
            return pNode->left_;
        }
        
        template <class T>
        TreeNode<T>* Tree<T>::Right(TreeNode<T>* pNode) {
            return pNode->right_;
        }
        
        template <class T>
        bool Tree<T>::Parent(T& obj, T& objOut) {
            TreeNode<T>* pNode;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            pNode = Parent(pNode);
            if (!pNode) {
                return false;
            }
            objOut = pNode->data_;
            return true;
        }
        
        template <class T>
        bool Tree<T>::Left(T& obj, T& objOut) {
            TreeNode<T>* pNode;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            pNode = Left(pNode);
            if (!pNode) {
                return false;
            }
            objOut = pNode->data_;
            return true;
        }
        
        template <class T>
        bool Tree<T>::Right(T& obj, T& objOut) {
            TreeNode<T>* pNode;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            pNode = Right(pNode);
            if (!pNode) {
                return false;
            }
            objOut = pNode->data_;
            return true;
        }
        
        
        
        template <class T>
        bool Tree<T>::InorderTreeWalk(TreeNode<T>* pNodeI) {
            TreeNode<T>* pNode = pNodeI;
            if (!pNode) {
                InorderTreeWalk(pNode->left_);
                lstInorder_->Insert(lstInorder_->Lengh(), pNode->data_);
                InorderTreeWalk(pNode->right_);
            }
        }
        
        template <class T>
        bool Tree<T>::PreorderTreeWalk(TreeNode<T>* pNodePr) {
            TreeNode<T>* pNode = pNodePr;
            if (!pNode) {
                lstPreorder_->Insert(lstPreorder_->Lengh(), pNode->data_);
                PreorderTreeWalk(pNode->left_);
                PreorderTreeWalk(pNode->right_);
            }
        }
        
        template <class T>
        bool Tree<T>::PostorderTreeWalk(TreeNode<T>* pNodePo) {
            TreeNode<T>* pNode = pNodePo;
            if (!pNode) {
                PostorderTreeWalk(pNode->left_);
                PostorderTreeWalk(pNode->right_);
                lstPostorder_->Insert(lstPostorder_->Lengh(), pNode->data_);
            }
        }
        
        
        template <class T>
        bool Tree<T>::InorderTreeWalk(T& obj) {
            TreeNode<T>* pNode = NULL;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            return InorderTreeWalk(pNode);
        }
        
        template <class T>
        bool Tree<T>::PreorderTreeWalk(T& obj) {
            TreeNode<T>* pNode = NULL;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            return PreorderTreeWalk(pNode);
        }
        
        template <class T>
        bool Tree<T>::PostorderTreeWalk(T& obj) {
            TreeNode<T>* pNode = NULL;
            Search(obj, &pNode);
            if (!pNode) {
                return false;
            }
            return PostorderTreeWalk(pNode);
        }

    }
}






#endif
