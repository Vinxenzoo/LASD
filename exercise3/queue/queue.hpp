//Vincenzo Capasso N86004259

#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd 
{

/* ************************************************************************** */

template <typename Data>
class Queue: public virtual  ClearableContainer
{
  
private:


protected:

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  Queue & operator= (const Queue &) = delete;

  // Move assignment
  Queue & operator= ( Queue &&) = delete;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const Queue & ) const noexcept = delete;
  inline bool operator!=(const Queue & ) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Head()const = 0;

  virtual Data & Head() = 0;

  virtual void Dequeue() = 0;

  virtual Data HeadNDequeue() = 0;

  virtual void Enqueue (const Data & ) = 0;

  virtual void Enqueue ( Data && ) = 0;

};

/* ************************************************************************** */

}

#endif
