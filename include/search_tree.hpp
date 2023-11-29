#pragma once
#include <memory>
#include "node.hpp"
#include "tree_iterator.hpp"


namespace Search_Tree {

template<typename KeyT, typename comparator = std::less<KeyT>>
class Red_Black_tree {

public:
        using key_type = KeyT;
        using difference_type = std::ptrdiff_t;
        using key_compare = comparator;
        using node_type = detail::Node<key_type>;
        using pointer = node_type*;
        using const_pointer = const pointer;
        using iterator = Tree_iterator<key_type>; 
        using const_iterator = iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        const_iterator find(const key_type& key) const {
            pointer ptr = root_ptr_;
            while(ptr != nullptr && ptr->key_ != key) {
                if(key < ptr->key_) {
                    ptr = ptr->left_;
                } else {
                    ptr = ptr->right_;
                }
            }
            if(ptr != nullptr) {
                return const_iterator{ptr};
            } else {
                return const_iterator{end_ptr_};
            }
        }
private:
        void create_root_node(const key_type& key) {
            pointer root_ptr_ = new node_type{key};
            end_ptr_->left_ = root_ptr_;
            root_ptr_->parent_ = end_ptr_;
            root_ptr_->is_it_red_ = false;
            begin_ptr_ = root_ptr_;
        }

        pointer create_node(const key_type& key) {
            pointer ptr = new node_type{key};
            return ptr;
        }
public:
        pointer unbalanced_insertion(const key_type& key) {
            pointer par = nullptr;
            pointer ins = root_ptr_;
            while(ins) {
                par = ins;
                if(key < ins->key_) {
                    ins = ins->left_;
                } else {
                    ins = ins->right_;
                }
            }

            if(nullptr == par) { //Tree was empty
                this->create_root_node(key);
                return root_ptr_;
            }

            if(key < par->key_) {
                ins = new node_type{key};
                par->left_ = ins;
                ins->parent_ = par;
                return ins;
            } else {
                ins = new node_type{key};
                par->right_ = ins;
                ins->parent_ = par;
                return ins;
            }
        } 

        iterator begin() const {
            return iterator{root_ptr_->minimum(root_ptr_)};
        }

        iterator end() const {

            return iterator{end_ptr_};
        }


private:
        pointer root_ptr_;
        node_type end_node_{0};
        pointer end_ptr_ = std::addressof(end_node_);
        pointer begin_ptr_ = end_ptr_;
        key_compare comp_; 
};

} //  <-- namespace Search_Tree