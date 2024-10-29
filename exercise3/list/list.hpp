//Vincenzo Capasso N86004259

#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: 
virtual public ClearableContainer,
  virtual public LinearContainer<Data>, 
  virtual public DictionaryContainer<Data>
 {


private:

  // ...

protected:

   using Container::size;

  struct Node 
  {

    Data elem;
    Node * next = nullptr;

    /* ********************************************************************** */

    Node() = default;
    Node (const Data & d) : elem(d) {};
    Node (Data &&) noexcept;


    /* ********************************************************************** */

    // Copy constructor
    Node (const Node & n) : elem(n.elem) {};

    // Move constructor
    Node (Node && no) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

    virtual Node * Clone(Node *);

  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List (const TraversableContainer<Data> &);
  List (MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  List (const List<Data> &);

  // Move constructor
  List (List<Data> &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List & operator= (const List<Data> &);

  // Move assignment
   List & operator= (List<Data> && ) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const List<Data> &) const noexcept; 
  inline bool operator!=(const List<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &);
  void InsertAtFront( Data &&);
  void RemoveFromFront();
  Data FrontNRemove();

  void InsertAtBack(const Data &);
  void InsertAtBack( Data &&);

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override;

  using TestableContainer<Data>::Exists;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert (const Data &) override;
  bool Insert (Data &&) override;
  bool Remove (const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)


  const Data & operator[](const ulong) const override;
  Data & operator[](const ulong) override;

  const Data & Front() const override;
  Data & Front() override;

  const Data & Back() const override;
  Data & Back() override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  virtual void Traverse(TraverseFun) const override;
  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual inline  void PostOrderMap(MapFun) override;

protected:

  void PreOrderTraverse(TraverseFun, const Node *) const;

  void PostOrderTraverse(TraverseFun, const Node *) const;

  void PreOrderMap(MapFun, Node *);

  void PostOrderMap(MapFun, Node *);



};

/* ************************************************************************** */



}

#include "list.cpp"

#endif