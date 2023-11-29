#pragma once
#include "node.hpp"
namespace Search_Tree {

template<typename KeyT>
class Tree_iterator final {
public: 
        using difference_type = std::ptrdiff_t;
        using value_type = detail::Node<KeyT>;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit Tree_iterator(pointer ptr) : ptr_{ptr} {}; 

        Tree_iterator& operator ++ () {
                ptr_ = ptr_->successor();
                return *this;
        }

        Tree_iterator operator ++ (int) {
                Tree_iterator old = *this;
                ++(*this);
                return old;
        }

        Tree_iterator& operator -- () {
                ptr_ = ptr_->predecessor();
                return *this;
        }

        Tree_iterator operator -- (int) {
                Tree_iterator old = *this;
                --(*this);
                return old;
        }

        bool operator ==  (const Tree_iterator& rhs) const {return this->ptr_ == rhs.ptr_; }
        bool operator !=  (const Tree_iterator& rhs) const {return !(rhs == *this); }

        const KeyT& operator * () const {return ptr_->key_; }
        const KeyT* operator -> () const {return std::addressof(ptr_->key_); }

private:
        pointer ptr_{nullptr};

}; // <--  class Tree_iterator


} // <-- namespace Search_Tree