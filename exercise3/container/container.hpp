//Vincenzo Capasso N86004259

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

namespace lasd {
/* ************************************************************************** */

class Container {

private:

// ...

protected:

  ulong size;

  /* ************************************************************************ */

  // Default constructor
  Container() noexcept {size = 0;}

  // Container() specifiers;
  Container(ulong s) {size = s;}

public:

  // Destructor
  // ~Container() specifiers
  virtual ~Container() noexcept= default;
  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) = delete; 
  // Move assignment
  Container& operator=(Container&&) = delete; 

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator==(const Container&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const noexcept = delete; 
  /* ************************************************************************ */

  // Specific member functions

  virtual bool Empty() const noexcept  {return (size==0);}

  virtual ulong Size() const noexcept {return size;}
};

/* ************************************************************************** */

class ClearableContainer: virtual public Container
{
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~ClearableContainer() specifiers
  virtual ~ClearableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) = delete;

  // Move assignment
  ClearableContainer& operator=( ClearableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) const noexcept = delete;

  bool operator!=(const ClearableContainer&) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member functions

  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer
{


private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer& operator=(const ResizableContainer&) = delete;

  // Move assignment
  ResizableContainer& operator= (ResizableContainer&& ) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer& ) const noexcept = delete;

  bool operator!=(const ResizableContainer& ) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual void Resize(const ulong) =0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
virtual  void Clear() { Resize(0);}

};

/* ************************************************************************** */

}

#endif
