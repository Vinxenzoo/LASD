//Vincenzo Capasso N86004259

#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer:  public virtual TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~MappableContainer() specifiers
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer& operator=(const MappableContainer&) = delete;

  // Move assignment
  MappableContainer& operator=(MappableContainer&&) noexcept = delete;

  /* ************************************************************************ */


  bool operator==(const MappableContainer&) const noexcept =delete;

  bool operator!=(const MappableContainer&) const noexcept =delete;

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;
  virtual void Map(MapFun) =0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer: public virtual MappableContainer<Data>, public virtual PreOrderTraversableContainer<Data> 
{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;

  // Move assignment
  PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  
  bool operator==(const  PreOrderMappableContainer&) const noexcept =delete;

  bool operator!=(const  PreOrderMappableContainer&) const noexcept =delete;
  

  /* ************************************************************************ */

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) =0;
  /* ************************************************************************ */

  // type Map(argument) specifiers; // Override MappableContainer member
  virtual void Map(MapFun) override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data>,virtual public PostOrderTraversableContainer<Data>
{
  

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;

  // Move assignment
  PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) noexcept = delete;

  /* ************************************************************************ */


  bool operator==(const  PostOrderMappableContainer&) const noexcept =delete;

  bool operator!=(const  PostOrderMappableContainer&) const noexcept =delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) =0;

  /* ************************************************************************ */

  virtual void Map(MapFun) override;
   
};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data>, virtual public InOrderTraversableContainer<Data>  
{


private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  InOrderMappableContainer& operator=(const InOrderMappableContainer &) = delete;

  // Move assignment
   InOrderMappableContainer& operator=( InOrderMappableContainer&&) = delete;
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const  InOrderMappableContainer&) const noexcept =delete;

   bool operator!=(const  InOrderMappableContainer&) const noexcept =delete;

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void InOrderMap(MapFun)  =0;

  /* ************************************************************************ */

  virtual void Map(MapFun) override;

};

/* ************************************************************************** */


template <typename Data>
class BreadthMappableContainer:   public virtual MappableContainer<Data>, public virtual  BreadthTraversableContainer<Data>
 {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;
  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;

  // Move assignment
  BreadthMappableContainer& operator=( BreadthMappableContainer&&) noexcept= delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const  BreadthMappableContainer&) const noexcept =delete;

  bool operator!=(const  BreadthMappableContainer&) const noexcept =delete;
  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

   virtual void BreadthMap(MapFun) =0;
  
   virtual void Map(MapFun) override;
};


/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
