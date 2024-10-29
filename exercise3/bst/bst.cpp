//Vincenzo Capasso N86004259

#include "bst.hpp"

namespace lasd 
{

//Comparison operators
template <typename Data>
bool BST<Data>::operator==(const BST<Data>& bin_ser) const noexcept 
{
    if(size != bin_ser.Size()) {
        return false;
    } else {
        if(size == 0) {
            return true;
        }
        BTInOrderIterator<Data> itera1(*this);
        BTInOrderIterator<Data> itera2(bin_ser);
        while(!itera1.Terminated() && !itera2.Terminated()) {
            if(*itera1 != *itera2) {
                return false;
            }
            ++itera1;
            ++itera2;
        }
        if(itera1.Terminated() && itera2.Terminated()) {
            return true;
        }
        return false;
    }
}


//Predecessor
template <typename Data>
const Data& BST<Data>::Predecessor(const Data& dat_i) const 
{
    NodeLnk* const * tempor = FindPointerToPredecessor(root, dat_i);
    if(tempor != nullptr) 
    {
        return (*tempor)->info;
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//PredecessorNRemove
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dat_i) 
{
    NodeLnk** tempor = FindPointerToPredecessor(root, dat_i);
    if(tempor != nullptr) 
    {
        return DataNDelete(Detach(*tempor));
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//RemovePredecessor
template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dat_i) 
{
    NodeLnk** tmp = FindPointerToPredecessor(root, dat_i);
    if(tmp != nullptr) 
    {
        delete Detach(*tmp);
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//Successor
template <typename Data>
const Data& BST<Data>::Successor(const Data& dat_i) const 
{
    NodeLnk* const * tempor = FindPointerToSuccessor(root, dat_i);
    if(tempor != nullptr) 
    {
        return (*tempor)->info;
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//SuccessorNRemove
template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dat_i) 
{
    NodeLnk** tempor = FindPointerToSuccessor(root, dat_i);
    if(tempor != nullptr) 
    {
        return DataNDelete(Detach(*tempor));
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//RemoveSuccessor
template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dat_i) 
{
    NodeLnk** tempor = FindPointerToSuccessor(root, dat_i);
    if(tempor != nullptr)
    {
        delete Detach(*tempor);
    } 
    else 
    {
        throw std::length_error("Not found!");
    }
}

//Insert
template <typename Data>
bool BST<Data>::Insert(const Data& dat_i) 
{
    NodeLnk*& tempor = FindPointerTo(root, dat_i);
    if(tempor == nullptr) 
    {
        tempor = new NodeLnk(dat_i);
        size++;
        return true;
    } else {
        return false;
    }
}

//Insert move
template <typename Data>
bool BST<Data>::Insert(Data && dat_i) noexcept 
{
    NodeLnk*& tempor = FindPointerTo(root, dat_i);
    if(tempor == nullptr) 
    {
        tempor = new NodeLnk(std::move(dat_i));
        size++;
        return true;
    } 
    else 
    {
        return false;
    }
}

//Remove
template <typename Data>
bool BST<Data>::Remove(const Data& dat_i) 
{
    NodeLnk*& tempor = FindPointerTo(root, dat_i);
    if(tempor != nullptr) 
    {
        delete Detach(tempor);
        return true;
    } 
    else 
    {
        return false;
    }
}

//Detach
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& binser_no) noexcept 
{
    if(binser_no != nullptr) 
    {
        if(binser_no->left == nullptr) 
        {
            return Skip2Right(binser_no);
        } 
        else 
        {
            if(binser_no->right == nullptr)
            {
              return Skip2Left(binser_no);
            }
            else 
            {
            NodeLnk* tempor = DetachMax(binser_no->left);
            std::swap(binser_no->info, tempor->info);
            return tempor;
             }
        }
    }
    return nullptr;
}

//FindPointerToMin 
template <typename Data>
typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMin(NodeLnk* const & binser_no) const noexcept 
{
    NodeLnk* const * tempor = &binser_no;
    NodeLnk* current = binser_no;
    if(current != nullptr) 
    {
        while(current->left != nullptr) 
        {
            tempor = &current->left;
            current = current->left;
        }
    }
    return *tempor;
}

//FindPointerToMax 
template <typename Data>
typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMax(NodeLnk* const & binser_no) const noexcept 
{
    NodeLnk* const * tempor = &binser_no;
    NodeLnk* current = binser_no;

    if(current != nullptr) 
    {
        while(current->right != nullptr) 
        {
            tempor = &current->right;
            current = current->right;
        }
    }
    return *tempor;
}

//FindPointerTo
template <typename Data>
typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerTo(NodeLnk* const & find_no, const Data& dat_find) const noexcept 
{
    NodeLnk* const * tempor = &find_no;
    if(*tempor != nullptr) 
    {
        if(find_no->info == dat_find) 
        {
            return *tempor;
        }
        else 
        {
            if(find_no->info < dat_find) 
            {
              tempor = &(FindPointerTo(find_no->right, dat_find));
            }
            else 
            {
              tempor = &(FindPointerTo(find_no->left, dat_find));
            }
        }
    }
    return *tempor;
}

//FindPointerToPredecessor
template <typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToPredecessor(NodeLnk* const & find_prenod, const Data& dat_prefind) const noexcept 
{
    NodeLnk* const * current = &find_prenod;
    NodeLnk* const * temporary = nullptr;

    while(*current != nullptr && (*current)->info != dat_prefind) 
    {
        if((*current)->info < dat_prefind) 
        {
            temporary = current;
            current = &((*current)->right);
        }
        else 
         {
            if((*current)->info > dat_prefind) 
            {
             current = &((*current)->left);
            }
         }
    }
    if(*current != nullptr && (*current)->HasLeftChild()) {
        return &FindPointerToMax((*current)->left);
    }
    return temporary;
}

//FindPointerToSuccessor
template <typename Data>
typename BST<Data>::NodeLnk* const * BST<Data>::FindPointerToSuccessor(NodeLnk* const & find_succnod, const Data& dat_succfind) const noexcept 
{
    NodeLnk* const * current = &find_succnod;
    NodeLnk* const * temporary = nullptr;

    while(*current != nullptr && (*current)->info != dat_succfind) 
    {
        if((*current)->info > dat_succfind) 
        {
            temporary = current;
            current = &((*current)->left);
        }
        else 
        {
           if((*current)->info < dat_succfind) {
            current = &((*current)->right);
           }
        }
    }

    if(*current != nullptr && (*current)->HasRightChild()) {
        return &FindPointerToMin((*current)->right);
    }
    return temporary;
}


}
