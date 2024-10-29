//Vincenzo Capasso N86004259

#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual public List<Data> 
{

private:


protected:


public:

  // Default constructor
   StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst (const TraversableContainer<Data> & c) : List<Data>(c) {};
  StackLst (MappableContainer<Data> && c) : List<Data>(std::move(c)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline StackLst(const StackLst<Data> & st) : List<Data> (st) {};

  // Move constructor
  inline StackLst(StackLst<Data> && st) : List<Data> (std::move(st)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst & operator= (const StackLst<Data> &);

  // Move assignment
  StackLst & operator= (StackLst<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator ==(const StackLst<Data> &) const noexcept;
  inline bool operator !=(const StackLst<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override;
  Data & Top() override;
  void Pop() override;
  Data TopNPop() override;
  void Push (const Data &) override;
  void Push (Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif