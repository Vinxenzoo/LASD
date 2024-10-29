//Vincenzo Capasso N86004259

#include "binarytreevec.hpp"

namespace lasd {

/* ************************************************************************** */

//Element
template <typename Data>
const Data & BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
    return info;
}

//Element mutable
template <typename Data>
Data & BinaryTreeVec<Data>::NodeVec::Element() noexcept {
    return info;
}

//IsLeaf
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
    return !(HasRightChild() && HasLeftChild());
}

//HasRightChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    return ((2*curr+2) < albero->Size());
}

//HasLeftChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
    return ((2*curr+1) < albero->Size());
}

//Node Vec operatior
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec& vec_no) 
{
    info = vec_no.info;
    curr = vec_no.curr;
    albero = vec_no.tree;
    return *this;
}


template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(NodeVec&& vec_no) noexcept 
{
    std::swap(info, vec_no.info);
    std::swap(curr, vec_no.curr);
    std::swap(albero, vec_no.tree);
    return *this;
}

//Node vec specific funtion on left child and right child
//NON MUTABLE
template <typename Data>
const BinaryTreeVec<Data>::Node & BinaryTreeVec<Data>::NodeVec::RightChild() const 
{
    if(!(HasRightChild())) 
    {
        throw std::out_of_range("Right child does not exists!");
    } 
    else 
    {
         return *(albero->operator[](2*curr+2));
    }
}

template <typename Data>
const BinaryTreeVec<Data>::Node & BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(!(HasLeftChild())) 
    {
        throw std::out_of_range("Left child does not exists!");
    } 
    else 
    {
        return *(albero->operator[](2*curr+1));
    }
}

//MUTABLE FUNCTIONS
template <typename Data>
BinaryTreeVec<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::RightChild() {
    if(!(HasRightChild())) 
    {
        throw std::out_of_range("Right child does not exists!");
    } 
    else 
    {
        return *(albero->operator[](2*curr+2));
    }
}

template <typename Data>
BinaryTreeVec<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if(!(HasLeftChild())) 
    {
        throw std::out_of_range("Left child does not exists!");
    } 
    else 
    {
        return *(albero->operator[](2*curr+1));
    }    
}

//Binary tree vec

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> & trav_con) {

    size = trav_con.Size();

    if(size>0) {
        vec = new Vector<NodeVec*>(size);
        ulong i = 0;

        trav_con.Traverse([this, &i](const Data & data)
        {
            NodeVec* n = new NodeVec(data, i, vec);
            vec->operator[](i) = n;
            i++;
        });

    }    
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && map_con) noexcept 
{
    size = map_con.Size();
    if(size > 0) 
    {
        vec = new Vector<NodeVec*>(size);
        ulong i=0;
        
        map_con.Map([this, &i](Data& data) 
        {
            NodeVec* n = new NodeVec(data, i, vec);
            vec->operator[](i) = n;
            i++;
        });
    } 
}

//COPY COSTRUCTOR
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> & albero_vec) 
{
    size = albero_vec.Size();

    if(size>0) {
        vec = new Vector<NodeVec*>(size);
        for(ulong i=0; i<size; i++) {
            NodeVec* n = new NodeVec(albero_vec.vec->operator[](i)->Element(), i, vec);
            vec->operator[](i) = n;
        }
    }
}

//Move Costructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> && albero_vec) noexcept 
{
    std::swap(size, albero_vec.size);
    std::swap(vec, albero_vec.vec);
}

//Operator of copy assignement
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> & albero_vec) 
{
    BinaryTreeVec<Data>* new_tr = new BinaryTreeVec<Data>(albero_vec);
    std::swap(*this, *new_tr);

    delete new_tr;
    return *this;
}

//operator of move assignement
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> && albero_vec) noexcept 
{
    std::swap(size, albero_vec.size);
    std::swap(vec, albero_vec.vec);

    return *this;
}

//Clear
template <typename Data>
void BinaryTreeVec<Data>::Clear() 
{
   
    for(ulong i=0; i<size; i++) {
        delete vec->operator[](i);   
    }
    delete vec;
    vec = nullptr;
    size = 0;
}

template <typename Data>
const BinaryTreeVec<Data>::Node & BinaryTreeVec<Data>::Root() const
{
     if(!(vec->Empty())) {
        return *(vec->operator[](0));
    } else {
        throw std::length_error("Empty tree");
    }
}

template <typename Data>
BinaryTreeVec<Data>::MutableNode & BinaryTreeVec<Data>::Root()
{
      if(!(vec->Empty())) 
    {
        return *(vec->operator[](0));
    } else {
        throw std::length_error("Empty tree");
    }
}



}
