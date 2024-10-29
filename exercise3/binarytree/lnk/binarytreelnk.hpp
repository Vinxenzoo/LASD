//Vincenzo Capasso N86004259

#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP


#include "../binarytree.hpp"

namespace lasd 
{

template <typename Data>
class BinaryTreeLnk : public virtual MutableBinaryTree<Data>
{

private:

protected:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;
  using Container::size;

  struct NodeLnk : virtual MutableNode 
  { 

  private:

  protected:

  public:

  Data info;
  NodeLnk* left = nullptr;
  NodeLnk* right = nullptr;

  NodeLnk() = default;

  NodeLnk(const Data & dat_i) { info = dat_i;}
  NodeLnk(Data && dat_i) noexcept { std::swap(info, dat_i);}


  NodeLnk(const NodeLnk&);
  NodeLnk(NodeLnk &&) noexcept;

  //Destructor
  virtual ~NodeLnk() 
  {
    delete left;
    delete right;
  }

  //Copy assignment
  NodeLnk& operator=(const NodeLnk&);

  //Move assignment
  NodeLnk& operator=(NodeLnk&&) noexcept;

  //Comparison operators
  bool operator==(const NodeLnk& node) const noexcept { return BinaryTree<Data>::Node::operator==(node);}
  bool operator!=(const NodeLnk& node) const noexcept {return BinaryTree<Data>::Node::operator!=(node);}

  //Functions
  const Data & Element() const noexcept override;
  Data & Element() noexcept override;

  bool IsLeaf() const noexcept override;
  bool HasRightChild() const noexcept override;
  bool HasLeftChild() const noexcept override;

  virtual const Node & RightChild() const override;
  virtual const Node & LeftChild() const override;

  virtual MutableNode & RightChild() override;
  virtual MutableNode & LeftChild() override;

  };

protected: 

public:
   NodeLnk* curr = nullptr;
   NodeLnk* root = nullptr;

  // Default constructor
  BinaryTreeLnk() = default;


  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &);
  BinaryTreeLnk(MappableContainer<Data> &&);


  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk &bin_lnk) { size = bin_lnk.Size(); 
  root = alb_same(bin_lnk.root);}

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() { Clear();}

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk &);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk& albero_lnk) const noexcept
  {
   if(size == albero_lnk.size) 
   {return (Root() == albero_lnk.Root()); }
   else return false;
  }

  bool operator!=(const BinaryTreeLnk & albero_lnk) const noexcept {return !(Root() == albero_lnk.Root());}

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  const Node & Root() const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  MutableNode & Root() override; 

  //NodeLnk & Root_lnk(); 

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override {
    delete root;
    size = 0;
    root = nullptr;
  } 

  protected:
  
  NodeLnk* alb_same(NodeLnk*);

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif