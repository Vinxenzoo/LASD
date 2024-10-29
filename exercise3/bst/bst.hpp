//Vincenzo Capasso N86004259

#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual public ClearableContainer, virtual public DictionaryContainer<Data>, virtual public BinaryTree<Data>, virtual public BinaryTreeLnk<Data>
{

private:

protected:

  using typename BinaryTree<Data>::Node;
  using typename MutableBinaryTree<Data>::MutableNode;

  using typename BinaryTreeLnk<Data>::NodeLnk;
  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> & trav_con)
  {
    trav_con.Traverse([this](const Data& dat_i) {
        Insert(dat_i);
    });
 }
  BST(MappableContainer<Data> && map_con) noexcept
  {
    map_con.Map([this](Data& dat_i) {
        Insert(std::move(dat_i));
    });
  }
  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data> & bst) : BinaryTreeLnk<Data>(bst) {};

  // Move constructor
  BST(BST<Data> && bst) noexcept : BinaryTreeLnk<Data>(std::move(bst)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST & operator=(const BST & bst) 
  {
    BinaryTreeLnk<Data>::operator=(bst);
    return *this;
  };


  // Move assignment
  BST & operator=(BST && bst) noexcept 
  {
    BinaryTreeLnk<Data>::operator=(std::move(bst));
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST &) const noexcept;
  bool operator!=(const BST & bin_ser) const noexcept { return !(*this == bin_ser);}


  /* ************************************************************************ */

  // Specific member functions
  virtual const Data & Min() const 
  {   
    if(root == nullptr) { throw std::length_error("Empty BST!");} 
    else { return FindPointerToMin(root)->info;}
  }

  virtual Data MinNRemove()
  {
    if(root ==nullptr) { throw std::length_error("Empty BST!");} 
    else { return DataNDelete(DetachMin(root));}
  }

  virtual void RemoveMin()
  {
    if(root == nullptr) { throw std::length_error("Empty BST!");} 
    else { delete DetachMin(root);}
  }

  virtual const Data & Max() const
  {
    if(root != nullptr) 
    { return FindPointerToMax(root)->info;
    } 
    else { throw std::length_error("Empty BST!");}
  }
  
  virtual Data MaxNRemove()
  {
    if(root != nullptr) { return DataNDelete(DetachMax(root));} 
    else { throw std::length_error("Empty BST!");}
  }
  
  virtual void RemoveMax()
  {
    if(root != nullptr) { delete DetachMax(root);} 
    else { throw std::length_error("Empty BST!");}
   }

  virtual const Data& Predecessor(const Data &) const;
  virtual Data PredecessorNRemove(const Data &);
  virtual void RemovePredecessor(const Data &);

  virtual const Data& Successor(const Data &) const;
  virtual Data SuccessorNRemove(const Data &);
  virtual void RemoveSuccessor(const Data &);

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const Node & Root() const 
  {
    if(root == nullptr) { throw std::length_error("Empty Tree!");} 
    else { return *root;}
  }

  MutableNode & Root() 
  {
    if(root == nullptr) { throw std::length_error("Empty Tree!");} 
    else { return *root;}
  }


  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data &) override;
  bool Insert(Data &&) noexcept override;
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data& dat_s) const noexcept override { return (FindPointerTo(root, dat_s) != nullptr);}

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  virtual void Clear() override 
  {
    BinaryTreeLnk<Data>::Clear();
  }; 

  /* ************************************************************************ */

/*
  void TestDetach(const Data & d)
    {
      NodeLnk *& no = FindPointerTo(root, d);
      if(no != nullptr)
      {
        delete Detach(no);
      }
    }

  void TestDetachMax() { if(root != nullptr) { delete DetachMax(root);}}

  void TestDetachMin() { if(root != nullptr) { delete DetachMin(root);}}

  void Testskip2left (const Data & d)
  {
    NodeLnk *& no = FindPointerTo(root, d);
    if(no != nullptr)
    {
      delete Skip2Left(no);
    }
  }

  void Testskip2right (const Data & d)
  {
    NodeLnk *& no = FindPointerTo(root, d);
    if(no != nullptr)
    {
      delete Skip2Right(no);
    }
  }
  */

/*
  NodeLnk * const * TestFindPointerToSuccessor( const Data & d) const { return FindPointerToSuccessor(root, d);}

  NodeLnk * const * TestFindPointerToPredecessor( const Data & d) const { return FindPointerToPredecessor(root, d);}
*/
protected:

  // Auxiliary functions, if necessary!
  virtual Data DataNDelete(NodeLnk* lnk_no)
  {
    Data dat_i {};
    std::swap(dat_i, lnk_no->info);
    delete lnk_no;
    return dat_i;
  }

  // type Detach(argument) specifiers;
  virtual NodeLnk* Detach(NodeLnk* &) noexcept;
  virtual NodeLnk* DetachMin(NodeLnk* & det_no) noexcept { return Skip2Right(FindPointerToMin(det_no));}
  virtual NodeLnk* DetachMax(NodeLnk* & det_no) noexcept { return Skip2Left(FindPointerToMax(det_no));}


  // type Skip2Left(argument) specifiers;
  virtual NodeLnk* Skip2Left(NodeLnk* & skip_no) noexcept
  {
    NodeLnk* tempor = nullptr;
    if(skip_no != nullptr) 
    {
        std::swap(tempor, skip_no->left);
        std::swap(tempor, skip_no);
        size--;
    }
    return tempor;
  }
  // type Skip2Right(argument) specifiers;
  virtual NodeLnk* Skip2Right(NodeLnk* & skip_no) noexcept
  {
    NodeLnk* tempor = nullptr;
    if(skip_no != nullptr) 
    {
        std::swap(tempor, skip_no->right);
        std::swap(tempor, skip_no);
        size--;
    }
    return tempor;
  }

  // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
  virtual NodeLnk* & FindPointerToMin(NodeLnk*& find_no) noexcept { return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToMin(find_no));}
  virtual NodeLnk* const & FindPointerToMin(NodeLnk* const &) const noexcept; 

  // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions
  virtual NodeLnk* & FindPointerToMax(NodeLnk*& find_no) noexcept { return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToMax(find_no)); }
  virtual NodeLnk* const & FindPointerToMax(NodeLnk* const &) const noexcept;

  // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions
  virtual NodeLnk*& FindPointerTo(NodeLnk*& find_no, const Data& dat_i) noexcept { return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerTo(find_no, dat_i)); }
  virtual NodeLnk* const & FindPointerTo(NodeLnk* const &, const Data &) const noexcept;

  // type FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
  virtual NodeLnk** FindPointerToPredecessor(NodeLnk* & find_no, const Data & dat_i) noexcept { return const_cast<NodeLnk* *>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(find_no, dat_i)); }
  virtual NodeLnk* const * FindPointerToPredecessor(NodeLnk* const &, const Data &) const noexcept;

  // type FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions
  virtual NodeLnk** FindPointerToSuccessor(NodeLnk* & find_no, const Data & dat_i) noexcept { return const_cast<NodeLnk* *>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(find_no, dat_i));}
  virtual NodeLnk* const * FindPointerToSuccessor(NodeLnk* const &, const Data &) const noexcept;

};

}

#include "bst.cpp"

#endif