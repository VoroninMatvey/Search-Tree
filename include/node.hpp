#pragma once
namespace Search_Tree {
namespace detail {    

template<typename KeyT>
struct Node {

    using pointer = Node*;

    explicit Node(const KeyT& key) :
    key_{key},
    parent_{nullptr}, left_{nullptr}, right_{nullptr},
    red_{true} {};
//----------------------------------------------------------------------------------------------
    const KeyT key_;
    pointer parent_, left_, right_;
    bool red_;
//----------------------------------------------------------------------------------------------
    pointer minimum(pointer val) const { //maybe private
        while(val->left_) {
            val = val->left_;
        }
        return val;
    }

    pointer maximum(pointer val) const { //maybe private
        while(val->right_) {
            val = val->right_;
        } 
        return val;
    }

    pointer successor() const { //next node in tree traversal
        auto ptr1 = this;
        if(ptr1->right_) {
            return ptr1->minimum(ptr1->right_); 
        }
        auto ptr2 = ptr1->parent_;
        while(ptr1 == ptr2->right_) {
            ptr1 = ptr2;
            ptr2 = ptr2->parent_;
        }
        return ptr2;
    }

    pointer predecessor() const { //previous node in tree traversal
        auto ptr1 = this;
        if(ptr1 -> left_) {
            return ptr1->maximum(ptr1->left_);
        }
        
        auto ptr2 = ptr1->parent_;
        while(ptr1 == ptr2->left_) {
            ptr1 = ptr2;
            ptr2 = ptr2->parent_;
        }
        return ptr2;
    }

}; // <--struct Node
}  // <-- namespace detail
}  // <-- namespace Search_Tree