namespace Search_Tree {
namespace detail {    

template<typename KeyT>
struct Node {

    using pointer = Node*;
    //using const_pointer = const pointer; 

    Node(const KeyT& key, pointer ptr = nullptr, bool is_it_red = true) :
    key_{key},
    parent_{ptr}, left_{ptr}, right_{ptr},
    is_it_red_{is_it_red} {};

    const KeyT key_;
    pointer parent_, left_, right_;
    bool is_it_red_;

    pointer Tree_minimum(pointer val) const { //maybe private
        while(val->left_) {
            val = val->left_;
        }
        return val;
    }

    pointer Tree_maximum(pointer val) const { //maybe private
        while(val->right_) {
            val = val->right_;
        } 
        return val;
    }

    pointer Tree_successor() const { //next node in tree traversal
        auto ptr1 = this;
        if(ptr1 -> right_) 
            return ptr1->Tree_minimum(ptr1->right_); 

        auto ptr2 = ptr1->parent_;
        while(ptr2 && ptr1 == ptr2->right_) {
            ptr1 = ptr2;
            ptr2 = ptr2->parent_;
        }
        return ptr2;
    }

    pointer Tree_predecessor() const { //previous node in tree traversal
        auto ptr1 = this;
        if(ptr1 -> left_)
            return ptr1->Tree_maximum(ptr1->left_);
        
        auto ptr2 = ptr1->parent_;
        while(ptr2 && ptr1 == ptr2->left_) {
            ptr1 = ptr2;
            ptr2 = ptr2->parent_;
        }
        return ptr2;
    }

}; // <--struct Node
}  // <-- namespace detail
}  // <-- namespace Search_Tree