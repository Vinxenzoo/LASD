//Vincenzo Capasso N86004259

#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */
#include "string"
#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: virtual public ResizableContainer, public virtual LinearContainer<Data>
{

private:

  // ...

protected:


  using Container::size;

  Data * elements= nullptr;

public:

  // Default constructor
  Vector() noexcept = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector (const ulong siz); //{size = siz; }
  // Vector(argument) specifiers; // A vector obtained from a TraversableContainer
  Vector (const TraversableContainer<Data> &);
  // Vector(argument) specifiers; // A vector obtained from a MappableContainer
  Vector ( MappableContainer<Data> &&);
  /* ************************************************************************ */

  // Copy constructor
  Vector (const Vector<Data> &);

  // Move constructor
  Vector (Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  inline Vector & operator= (const Vector<Data> &);

  // Move assignment
    inline Vector & operator= (Vector<Data> &&) ;

  /* ************************************************************************ */

  // Comparison operators
  bool operator== (const Vector <Data> &) const noexcept;
  bool operator!= (const Vector <Data> &) const noexcept;
  

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  
  void Resize( ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong) const override;
  Data & operator[](const ulong) override;

  const Data & Front() const override;
  Data & Front() override;

  const Data & Back() const override;
  Data & Back() override;

protected:

    inline Data * din_alloc (ulong);

};

/* ************************************************************************** */

template <typename Data>
class SortableVector:  virtual public Vector<Data>, public virtual SortableLinearContainer<Data>
 {
  
private:


protected:

//using Container::size;
using Vector<Data>::size;
using Vector<Data> :: elements;

public:

  // Default constructor
  SortableVector() noexcept = default;
  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong); 
  SortableVector(const TraversableContainer<Data> &);
  SortableVector( MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  SortableVector  (const SortableVector<Data> &);

  // Move constructor
  SortableVector  (SortableVector<Data> &&);


  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;
  virtual ~SortableVector() = default;
  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator= (const SortableVector<Data> &);

  // Move assignment
   SortableVector & operator= (SortableVector<Data> &&);

  const Data & operator[](const ulong) const override;
  Data & operator[](const ulong) override;

  void Sort() noexcept override;

protected:

  void bubblesort();
  void quicksort(ulong p, ulong r) noexcept;
  ulong partition(ulong p, ulong r) noexcept;

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif

