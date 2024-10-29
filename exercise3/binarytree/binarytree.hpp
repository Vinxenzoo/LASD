//Vincenzo Capasso N86004259

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : public virtual PreOrderTraversableContainer<Data>,
public virtual PostOrderTraversableContainer<Data>,
public virtual InOrderTraversableContainer<Data>,
public virtual BreadthTraversableContainer<Data> 
{


private:


protected:
  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    bool operator!=(const Node & altro_nodo) const noexcept { return !((*this)==altro_nodo); }


  public:

    friend class BinaryTree;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator=(const Node &) = delete;

    // Move assignment
    Node & operator=(Node &) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions
    virtual const Data & Element() const noexcept = 0;

    virtual bool IsLeaf() const noexcept = 0;
    virtual bool HasLeftChild() const noexcept = 0;
    virtual bool HasRightChild() const noexcept = 0;

    virtual const Node& LeftChild() const = 0;
    virtual const Node& RightChild() const = 0;
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator=(const BinaryTree &) = delete;

  // Move assignment
  BinaryTree & operator=(BinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree & binariotr) const noexcept {

    if(size != binariotr.size) { return false; }
    if(size==0) { return true; }
    return (Root() == binariotr.Root());
}

  bool operator!=(const BinaryTree & binariotr) const noexcept { return !((*this)== binariotr); }; 

  /* ************************************************************************ */

  // Specific member functions
  virtual const Node & Root() const = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun fun) const override { PreOrderTraverse(fun); }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  inline void PreOrderTraverse(TraverseFun fun) const override { PreOrderTraverse(fun, &Root()); }

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  inline void PostOrderTraverse(TraverseFun fun) const override { PostOrderTraverse(fun, &Root()); }

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)
  inline void InOrderTraverse(TraverseFun fun) const override { InOrderTraverse(fun, &Root());}

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  inline void BreadthTraverse(TraverseFun fun) const override { BreadthTraverse(fun, &Root()); }

protected:

  // Auxiliary functions, if necessary!
  void PreOrderTraverse(TraverseFun, const Node *) const;
  void PostOrderTraverse(TraverseFun, const Node*) const;
  void InOrderTraverse(TraverseFun, const Node*) const;
  void BreadthTraverse(TraverseFun, const Node*) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : public virtual ClearableContainer,
public virtual BinaryTree<Data>,
public virtual PreOrderMappableContainer<Data>,
public virtual PostOrderMappableContainer<Data>,
public virtual InOrderMappableContainer<Data>,
public virtual BreadthMappableContainer<Data> 
{
                          

private:

protected:
  using Container::size;
  using typename BinaryTree<Data>::Node;


public:

  struct MutableNode : Node
  {

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator=(const MutableNode &) = delete;

    // Move assignment
    MutableNode & operator=(MutableNode &&) noexcept = delete;


    /* ********************************************************************** */

    // Specific member functions
    
    using Node::Element;
    using Node::LeftChild;
    using Node::RightChild;

    virtual Data & Element() noexcept = 0;

    virtual MutableNode& LeftChild() = 0;

    virtual MutableNode& RightChild() = 0;


  };


  // Destructor
  virtual ~MutableBinaryTree() = default; 

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree & operator=(const MutableBinaryTree &) = delete;

  // Move assignment
  MutableBinaryTree & operator=(MutableBinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  using BinaryTree<Data>::Root;

  virtual MutableNode & Root() = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member
  inline void Map(MapFun fun) override { PreOrderMap(fun);}

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  inline void PreOrderMap(MapFun fun) override { PreOrderMap(fun, &Root());}

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  inline void PostOrderMap(MapFun fun) override {PostOrderMap(fun, &Root());}

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  inline void InOrderMap(MapFun fun) override { InOrderMap(fun, &Root());}

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  inline void BreadthMap(MapFun fun) override { BreadthMap(fun, &Root()); }

protected:

  // Auxiliary functions, if necessary!
  void PreOrderMap(MapFun, MutableNode *);
  void PostOrderMap(MapFun, MutableNode *);
  void InOrderMap(MapFun, MutableNode *);
  void BreadthMap(MapFun, MutableNode *);
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : public virtual ForwardIterator<Data>,
public virtual ResettableIterator<Data>
{


private:


protected:
  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> & alberotr) {
    if(alberotr.Size() != 0) 
    {
      root = curr = &alberotr.Root();
    } 
   }

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator & pre_iter) : root(pre_iter.root), curr(pre_iter.curr), stk(pre_iter.stk) {} 

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator && pre_iter) noexcept 
  {
    std::swap(root, pre_iter.root);
    std::swap(curr, pre_iter.curr);
    std::swap(stk, pre_iter.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator=(const BTPreOrderIterator & pre_iter) 
  {

    root = pre_iter.root;
    curr = pre_iter.curr;
    stk = pre_iter.stk;

    return *this;
  }

  // Move assignment
  BTPreOrderIterator & operator=(BTPreOrderIterator && pre_iter) noexcept 
  {
    std::swap(root, pre_iter.root);
    std::swap(curr, pre_iter.curr);
    std::swap(stk, pre_iter.stk);

    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator &) const noexcept = default;
  bool operator!=(const BTPreOrderIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data & operator*() const override 
  {

    if(!(Terminated())) {
      return curr->Element();
    } 

    throw std::out_of_range("Iterator Terminated!");
    
  }


  inline bool Terminated() const noexcept override {
    return (curr==nullptr);
  }

  /* ************************************************************************ */

  BTPreOrderIterator & operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override 
  {
    stk.Clear();
    curr = root;
  }

};

template <typename Data>
class BTPreOrderMutableIterator : public virtual MutableIterator<Data>,
public virtual BTPreOrderIterator<Data>
{

private:


protected:
  using BTPreOrderIterator<Data>::curr;

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data> & mut_iter) : BTPreOrderIterator<Data>(mut_iter) {};

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator & mut_iter) : BTPreOrderIterator<Data>(mut_iter) {};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator && mut_iter) : BTPreOrderIterator<Data>(std::move(mut_iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator & mut_iter) { BTPreOrderIterator<Data>::operator=(mut_iter);}

  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator && mut_iter) noexcept { BTPreOrderIterator<Data>::operator=(std::move(mut_iter));}

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTPreOrderMutableIterator &) const noexcept = default;


  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override {

    if(curr != nullptr) {
      return const_cast<Data&>(curr->Element());
    } else {
      throw std::out_of_range("Iterator Terminated!");
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>,
public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> & alberbin) 
  {
    if(alberbin.Size()!= 0) {
        curr = root = &alberbin.Root();
      piu_a_sinistra();
    }
}

  /* ************************************************************************ */

  // Copy constructor
  // BTPostOrderIterator(argument) specifiers;
  BTPostOrderIterator(BTPostOrderIterator & post_iter) : root(post_iter.root), curr(post_iter.curr), stk(post_iter.stk) {};

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator && post_iter) noexcept 
  {
    std::swap(root, post_iter.root);
    std::swap(curr, post_iter.curr);
    std::swap(stk, post_iter.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator=(const BTPostOrderIterator & post_iter) 
  {
    root = post_iter.root;
    curr = post_iter.curr;
    stk = post_iter.stk;
    return *this;
  }

  // Move assignment
  // type operator=(argument) specifiers;
  BTPostOrderIterator & operator=(BTPostOrderIterator && post_iter) noexcept 
  {
    std::swap(root, post_iter.root);
    std::swap(curr, post_iter.curr);
    std::swap(stk, post_iter.stk);

    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator &) const noexcept = default; 
  bool operator!=(const BTPostOrderIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data& operator*() const override 
  {
    if(!Terminated()) 
    {
      return curr->Element();
    } 
    else 
    {
      throw std::out_of_range("Iteratore Terminato!");
    }
  }; 

  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override { return (curr==nullptr);}; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTPostOrderIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override 
  {
    stk.Clear();
    curr = root;
   piu_a_sinistra();
}

  protected:
   void piu_a_sinistra();

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : public virtual MutableIterator<Data>,
public virtual BTPostOrderIterator<Data>
{

private:

protected:

  using BTPostOrderIterator<Data>::curr;

public:

  // Specific constructors
  BTPostOrderMutableIterator(BinaryTree<Data> & alb_bin) : BTPostOrderIterator<Data>(alb_bin) {}; 

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator & mut_pst_iter) : BTPostOrderIterator<Data>(mut_pst_iter) {}; 

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator && mut_pst_iter) noexcept : BTPostOrderIterator<Data>(std::move(mut_pst_iter)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator=(const BTPostOrderMutableIterator & mut_pst_iter) { BTPostOrderIterator<Data>::operator=(mut_pst_iter); }

  // Move assignment
  // type operator=(argument) specifiers;
  BTPostOrderMutableIterator & operator=(BTPostOrderMutableIterator && mut_pst_iter) {BTPostOrderIterator<Data>::operator=(std::move(mut_pst_iter));}

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTPostOrderMutableIterator &) const noexcept = default;


  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override 
  {
    if(curr != nullptr) {
      return const_cast<Data&>(curr->Element());
    } else {
      throw std::out_of_range("Iterator Terminated!");
    }
  }

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : public virtual ForwardIterator<Data>,
public ResettableIterator<Data>
{

private:


protected:
  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stk;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> & alberbin) 
  {
    if(alberbin.Size()!=0) {
        curr = root = &alberbin.Root();
        piu_a_sinistra_n();
    }
}

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator & inord_it) : root(inord_it.root), curr(inord_it.curr), stk(inord_it.stk) {};

  // Move constructor
  BTInOrderIterator(BTInOrderIterator && inord_it) noexcept 
  {

    std::swap(root, inord_it.root);
    std::swap(curr, inord_it.curr);
    std::swap(stk, inord_it.stk);
  }

  /* ************************************************************************ */

  // Destructor
  // ~BTInOrderIterator() specifiers;
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator& inord_it) {
    root = inord_it.root;
    curr = inord_it.curr;
    stk = inord_it.stk;
    return *this;
  };

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&& inord_it) noexcept 
  {
    std::swap(root, inord_it.root);
    std::swap(curr, inord_it.curr);
    std::swap(stk, inord_it.stk);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator&) const noexcept = default;
  bool operator!=(const BTInOrderIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data& operator*() const override 
  {
    if(curr != nullptr) {
      return curr->Element();
    } else {
      throw std::out_of_range("Iterator terminated!");
    }
  };

  inline bool Terminated() const noexcept override { return (curr == nullptr);};

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTInOrderIterator& operator++() override;


  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  // type Reset() specifiers; // (should not throw exceptions)
  void Reset() noexcept override 
  {
    stk.Clear();
    curr = root;
     piu_a_sinistra_n();
}


  protected:
 void piu_a_sinistra_n();

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : public virtual MutableIterator<Data>,
public virtual BTInOrderIterator<Data>
{

private:

  using BTInOrderIterator<Data>::curr;

protected:


public:

  // Specific constructors
  BTInOrderMutableIterator(MutableBinaryTree<Data>& alb_mut) : BTInOrderIterator<Data>(alb_mut) {};

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator<Data>& inord_mut_it) : BTInOrderIterator<Data>(inord_mut_it) {};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator<Data>&& inord_mut_it) : BTInOrderIterator<Data>(std::move(inord_mut_it)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& inord_mut_it) { BTInOrderIterator<Data>::operator=(inord_mut_it);};

  // Move assignment
  BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& inord_mut_it) noexcept { BTInOrderIterator<Data>::operator=(std::move(inord_mut_it));};

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTInOrderMutableIterator &) const noexcept = default;


  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data & operator*() override {
    if(curr != nullptr) {
      return const_cast<Data&>(curr->Element());
    } else {
      throw std::out_of_range("Iterator terminated!");
    }
  }; 

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : public virtual ForwardIterator<Data>,
public virtual ResettableIterator<Data>
{


private:


protected:
  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node *> queue;


public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>& alberobin) 
  {
    if(alberobin.Size()!=0) {
      curr = root = &alberobin.Root();
    } 
  }; 

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& bbre_it) : root(bbre_it.root), curr(bbre_it.root), queue(bbre_it.queue) {};

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& bbre_it) noexcept {
    std::swap(root, bbre_it.root);
    std::swap(curr, bbre_it.curr);
    std::swap(queue, bbre_it.queue);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator& bbre_it) 
  {
    root = bbre_it.root;
    curr = bbre_it.curr;
    queue = bbre_it.que;
    return *this;
  };

  // Move assignmen
  BTBreadthIterator& operator=(BTBreadthIterator&& bbre_it) noexcept 
  {
    std::swap(root, bbre_it.root);
    std::swap(curr, bbre_it.curr);
    std::swap(queue, bbre_it.que);
    return *this;
  };

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator&) const noexcept = default;
  bool operator!=(const BTBreadthIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data& operator*() const override 
  {
    if(curr != nullptr) 
    {
      return curr->Element();
    } 
    else 
    {
      throw std::out_of_range("Iterator terminated!");
    }
  }; 

  // type Terminated() specifiers; // (should not throw exceptions)
  inline bool Terminated() const noexcept override {return (curr == nullptr);};

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTBreadthIterator& operator++() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override {
    curr = root;
    queue.Clear();
  }

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : public virtual MutableIterator<Data>,
public virtual BTBreadthIterator<Data> 
{

private:

protected:

  using BTBreadthIterator<Data>::curr;

public:

  // Specific constructors
  BTBreadthMutableIterator(MutableBinaryTree<Data>& mut_bin) : BTBreadthIterator<Data>(mut_bin) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator& bb_mut) : BTBreadthIterator<Data>(bb_mut) {};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator&& bb_mut) noexcept : BTBreadthIterator<Data>(std::move(bb_mut)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator& it) {
    BTBreadthIterator<Data>::operator=(it);
  }

  // Move assignment
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&& bb_mut) noexcept { BTBreadthIterator<Data>::operator=(std::move(bb_mut)); }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator&) const noexcept = default;
  bool operator!=(const BTBreadthMutableIterator&) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  // type operator*() specifiers; // (throw std::out_of_range when terminated)
  Data & operator*() override 
  {
    if (curr != nullptr) {
      return const_cast<Data&>(curr->Element());
    } else {
      throw std::out_of_range("Iterator terminated!");
    }
  }; 

};

}

#include "binarytree.cpp"

#endif