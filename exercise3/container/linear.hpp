//Vincenzo Capasso N86004259

#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
{

private:

  // ...

protected:

  // ...
  using Container::size;

public:
  LinearContainer() = default;
  LinearContainer(const LinearContainer&) =default;
  LinearContainer(LinearContainer &&) = default;

  // Destructor
  virtual  ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer & operator=(const  LinearContainer& ) = delete;

  // Move assignment
  LinearContainer & operator=( LinearContainer&&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const LinearContainer &) const noexcept;

  inline bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  virtual const Data & operator[](ulong) const = 0;

  virtual Data & operator[](ulong) = 0;

  inline virtual const Data & Front() const;

  inline virtual Data & Front();

  inline virtual const Data & Back() const;

  inline virtual Data & Back();

  /* ************************************************************************ */

  using typename TraversableContainer<Data>::TraverseFun;
  
  virtual inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  virtual inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  virtual inline  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  using typename MappableContainer<Data>::MapFun;


  virtual inline void Map(MapFun) override;

  /* ************************************************************************ */

  virtual inline void PreOrderMap(MapFun)  override;

  /* ************************************************************************ */

  virtual inline void PostOrderMap(MapFun) override;

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer: public virtual LinearContainer<Data> {


private:

  // ...

protected:

  using Container::size;
  using LinearContainer<Data>::operator[];

public:

  // Destructor

virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer & operator=(const  SortableLinearContainer& )= delete;

  // Move assignment
  SortableLinearContainer & operator=( SortableLinearContainer&&)= delete;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SortableLinearContainer &) const noexcept;

  inline bool operator!=(const SortableLinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() noexcept;

protected:

  // Auxiliary member functions
  void quicksort(ulong p, ulong r) noexcept;
  ulong partition(ulong p, ulong r) noexcept;
};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
