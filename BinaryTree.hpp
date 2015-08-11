//
//  BinaryTree.hpp
//  test
//
//  Created by zhangnan on 15/8/11.
//  Copyright (c) 2015年 zhangnan. All rights reserved.
//

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>

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
            
            bool Search(T&);
            
            bool DeleteTree(TreeNode<T>*);
            bool DeleteTree(T&);
        };
        
        template <class T>
        Tree<T>::Tree() {
            node_ = NULL;
            root_ = NULL;
            total_elements_ = 0;
        }
        
        template <class T>
        Tree<T>::~Tree() {
            if (root_) {
                DeleteTree(root_);
                root_ = NULL;
            }
            
            total_elements_ = 0;
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
                }
                
                if (node_->data_ > obj && node_->left_ != NULL) {
                    node_ = node_->left_;
                    continue;
                } else if (node_->data_ < obj && node_->right_ != NULL) {
                    node_ = node_->right_;
                    continue;
                }
            }
            
            return false;
        }
        
    }
}






#endif
