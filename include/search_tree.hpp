#pragma once
#include <memory>
#include "node.hpp"
#include "tree_iterator.hpp"


namespace Search_Tree {

template<typename KeyT>
class Red_Black_tree {

public:
        using key_type = KeyT;
        using difference_type = std::ptrdiff_t;
        using node_type = detail::Node<key_type>;
        using pointer = node_type*;
        using const_pointer = const pointer;
        using iterator = Tree_iterator<key_type>; 
        using const_iterator = iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        /*const_*/pointer find(const key_type& key) const {
            pointer ptr = root_ptr_;
            while(ptr && ptr->key_ != key) {
                if(key < ptr->key_) {
                    ptr = ptr->left_;
                } else {
                    ptr = ptr->right_;
                }
            }
            if(ptr) {
                return /*const_*/ptr;
            } else {
                return /*const_*/end_ptr_;
            }
        }
private:
        void create_root_node(const key_type& key) {
            root_ptr_ = new node_type{key};
            end_ptr_->left_ = root_ptr_;
            end_ptr_->red_ = false;
            root_ptr_->parent_ = end_ptr_;
            root_ptr_->red_ = false;
            begin_ptr_ = root_ptr_;
        }

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

            if(!par) { //Tree was empty
                create_root_node(key);
                return root_ptr_; //will need to be removed after the function is created RB_INSERT_FIXUP
            } else if(key < par->key_) {
                ins = new node_type{key};
                par->left_ = ins;
                ins->parent_ = par;
                return ins; //will need to be removed after the function is created RB_INSERT_FIXUP
            } else {
                ins = new node_type{key};
                par->right_ = ins;
                ins->parent_ = par;
                return ins; //will need to be removed after the function is created  RB_INSERT_FIXUP
            }
        } 
public:
        pointer insert(const key_type& key) {
            std::cout<<"("<<key<<"):"<<std::endl<<std::endl;
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

            if(!par) { //Tree was empty
                create_root_node(key);
                ins = root_ptr_; //will need to be removed after the function is created RB_INSERT_FIXUP
            } else if(key < par->key_) {
                ins = new node_type{key};
                par->left_ = ins;
                ins->parent_ = par;
            } else {
                ins = new node_type{key};
                par->right_ = ins;
                ins->parent_ = par;
            }
            RB_insert_fixup(ins);
            return ins;
        }

        void left_rotate(pointer x_ptr) {
            pointer y_ptr = x_ptr->right_;
            if(!y_ptr) {
                return;
            }
            x_ptr->right_ = y_ptr->left_;

            if(y_ptr->left_) {
                y_ptr->left_->parent_ = x_ptr;
            }
            y_ptr->parent_ = x_ptr->parent_;

            if(x_ptr->parent_ == end_ptr_) {
                root_ptr_ = y_ptr;
                end_ptr_->left_ = y_ptr;
            } else if(x_ptr == x_ptr->parent_->left_) {
                x_ptr->parent_->left_ = y_ptr;
            } else {
                x_ptr->parent_->right_ = y_ptr;
            }

            y_ptr->left_ = x_ptr;
            x_ptr->parent_ = y_ptr;
        }

        void right_rotate(pointer y_ptr) {
            pointer x_ptr = y_ptr->left_;
            if(!x_ptr) {
                return;
            } 
            y_ptr->left_ = x_ptr->right_;

            if(x_ptr->right_) {
                x_ptr->right_->parent_ = y_ptr;
            }
            x_ptr->parent_ = y_ptr->parent_;

            if(y_ptr->parent_ == end_ptr_) {
                root_ptr_ = x_ptr;
                end_ptr_->left_ = x_ptr;
            } else if(y_ptr == y_ptr->parent_->left_) {
                y_ptr->parent_->left_ = x_ptr;
            } else {
                y_ptr->parent_->right_= x_ptr;
            }

            x_ptr->right_ = y_ptr;
            y_ptr->parent_ = x_ptr;
        } 

        pointer my_uncle_is_red(pointer gr_son_ptr) { //execution part of the algorithm without checks
            pointer gr_fath_ptr = gr_son_ptr->parent_->parent_;
            gr_fath_ptr->red_ = true;
            gr_fath_ptr->left_->red_ = false;
            gr_fath_ptr->right_->red_ = false;
            return gr_fath_ptr;
        }

        void my_uncle_is_black(pointer gr_son_ptr) {
            pointer gr_fath_ptr = gr_son_ptr->parent_->parent_;
            pointer dad_ptr = gr_son_ptr->parent_;
            bool cond1 = gr_fath_ptr->left_ == dad_ptr && dad_ptr->right_ == gr_son_ptr;
            bool cond2 = gr_fath_ptr->right_ == dad_ptr && dad_ptr->left_ == gr_son_ptr;

            if(cond1 || cond2) {
                black_uncle_with_two_rotations(gr_son_ptr);
            } else {
                black_uncle_with_one_rotation(gr_son_ptr);
            }
        }

        void black_uncle_with_one_rotation(pointer gr_son_ptr) {
            pointer gr_fath_ptr = gr_son_ptr->parent_->parent_;
            if(gr_fath_ptr->right_ == nullptr || gr_son_ptr->parent_ == gr_fath_ptr->left_) {
                right_rotate(gr_fath_ptr);
            } else {
                left_rotate(gr_fath_ptr);
            }

            gr_fath_ptr->red_ = true;
            gr_son_ptr->red_ = true;
            gr_fath_ptr->parent_->red_ = false;
        }

        void black_uncle_with_two_rotations(pointer gr_son_ptr) {
            pointer gr_fath_ptr = gr_son_ptr->parent_->parent_;
            if(gr_fath_ptr->right_ == nullptr || gr_fath_ptr->left_ == gr_son_ptr->parent_) {
                left_rotate(gr_son_ptr->parent_);
                black_uncle_with_one_rotation(gr_son_ptr->left_);   
            } else {
                right_rotate(gr_son_ptr->parent_);
                black_uncle_with_one_rotation(gr_son_ptr->right_);
            } 
        }

        void RB_insert_fixup(pointer gr_son_ptr) {
            if(gr_son_ptr->key_ < begin_ptr_->key_) {
                begin_ptr_ = gr_son_ptr;
            }
            //---------------------------------------------------------------------------
            int key = gr_son_ptr->key_;
            if(gr_son_ptr->parent_ != root_ptr_ && gr_son_ptr != root_ptr_) {
                std::cout<<"vnuk - "<<gr_son_ptr->key_ <<"; red: "<<gr_son_ptr->red_<<std::endl;
                std::cout<<"otec - "<<gr_son_ptr->parent_->key_ <<"; red: "<<gr_son_ptr->parent_->red_<<std::endl;
                std::cout<<"ded - "<<gr_son_ptr->parent_->parent_->key_ <<"; red: "<<gr_son_ptr->parent_->parent_->red_<<std::endl<<std::endl;
            }
            //----------------------------------------------------------------------------
            while(gr_son_ptr->parent_->red_ == true) {

                bool uncle_color_red;
                pointer gr_fath_ptr = gr_son_ptr->parent_->parent_;

                if(gr_fath_ptr->left_ == gr_son_ptr->parent_) {
                    if(gr_fath_ptr->right_ != nullptr) {
                        uncle_color_red = gr_fath_ptr->right_->red_;
                    } else {
                        uncle_color_red =false;
                    }
                } else {
                    if(gr_fath_ptr->left_ != nullptr) {
                        uncle_color_red = gr_fath_ptr->left_->red_;
                    } else {
                        uncle_color_red = false;
                    }
                }

                if(uncle_color_red == true) {
                    gr_son_ptr = my_uncle_is_red(gr_son_ptr);
                    std::cout<<"red"<<std::endl<<std::endl;
                } else {
                    my_uncle_is_black(gr_son_ptr);
                    gr_son_ptr = root_ptr_;
                    std::cout<<"black"<<std::endl<<std::endl;
                }
            }

            root_ptr_->red_ = false;

            //-------------------------------------------------------------------------
            pointer extr_gr_son_ptr = find(key);
            if(extr_gr_son_ptr->parent_ != root_ptr_ && extr_gr_son_ptr != root_ptr_) {
                std::cout<<"vnuk - "<<extr_gr_son_ptr->key_ <<"; red: "<<extr_gr_son_ptr->red_<<std::endl;
                std::cout<<"otec - "<<extr_gr_son_ptr->parent_->key_ <<"; red: "<<extr_gr_son_ptr->parent_->red_<<std::endl;
                std::cout<<"ded - "<<extr_gr_son_ptr->parent_->parent_->key_ <<"; red: "<<extr_gr_son_ptr->parent_->parent_->red_<<std::endl<<std::endl;
            }
            //-------------------------------------------------------------------------
            

        }

        iterator begin() const {
            return iterator{root_ptr_->minimum(root_ptr_)};
        }

        iterator end() const {

            return iterator{end_ptr_};
        }
        iterator root() const {
            return iterator{root_ptr_};
        } 


private:
        pointer root_ptr_;
        node_type end_node_{0};
        pointer end_ptr_ = std::addressof(end_node_);
        pointer begin_ptr_ = end_ptr_;
};

} //  <-- namespace Search_Tree