//Vincenzo Capasso N86004259

#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : public virtual MutableBinaryTree<Data>
{

private:


public:
  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;
  using typename TraversableContainer<Data>::TraverseFun; 
  using typename MappableContainer<Data>::MapFun;


protected:

  using MutableBinaryTree<Data>::size;

  struct NodeVec : virtual public MutableNode
  { 

  private:

    // ...

  protected:

public:
    
    Data info;
    ulong curr=0;
    Vector<NodeVec*> *albero = nullptr;

    NodeVec() = default;
    NodeVec(const Data & data, ulong index, Vector<NodeVec*>* v) : info(data), curr(index), albero(v) {};

    //Destructor 
    virtual ~NodeVec() = default;

    //Copy assignment
    NodeVec & operator=(const NodeVec &);

    //Move assignment
    NodeVec & operator=(NodeVec &&) noexcept;

    //Comparison operators
    bool operator==(const NodeVec& node) const noexcept { return BinaryTree<Data>::Node::operator==(node);};
    bool operator!=(const NodeVec& node) const noexcept { return BinaryTree<Data>::Node::operator!=(node); };

    //Specific member functions
    const Data& Element() const noexcept override;
    Data& Element() noexcept override;

    bool IsLeaf() const noexcept override;

    bool HasRightChild() const noexcept override;

    bool HasLeftChild() const noexcept override;

    virtual const Node & RightChild() const override;
    virtual const Node & LeftChild() const override;
    virtual MutableNode & RightChild() override;
    virtual MutableNode & LeftChild() override;
  };
 
  Vector<NodeVec*>* vec = nullptr;

public:

  
  
  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> &); 
  BinaryTreeVec(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data> && ) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() { 
    Clear(); 
    delete vec; 
    vec = nullptr; };

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>& btv) const noexcept { return BinaryTree<Data>::operator==(btv);};
  bool operator!=(const BinaryTreeVec<Data>& btv) const noexcept { return !(*this == btv);};
  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  const Node & Root() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  MutableNode & Root() override;
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
   void BreadthTraverse(TraverseFun trav_fun) const override
  {
    for(ulong i=0; i<size; i++) 
    {
        if(vec->operator[](i) != nullptr) 
        {
            trav_fun(vec->operator[](i)->Element());
        }
    }
  }

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  void BreadthMap(MapFun map_fun) override
  {
    for(ulong i=0; i<size; i++) 
    {
        if(vec->operator[](i) != nullptr) 
        {
            map_fun(vec->operator[](i)->Element());
        }
    }
  }

protected:


};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif