//Vincenzo Capasso N86004259

#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst: virtual public List<Data>, virtual public Queue<Data>
{


private:



protected:

  // using List<Data>::???;


public:

  // Default constructor
  QueueLst()= default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst (const TraversableContainer<Data> & c) : List<Data>(c) {};
  QueueLst (MappableContainer<Data> && c) : List<Data>(std::move(c)) {};

  /* ************************************************************************ */

  // Copy constructor
  inline QueueLst(const QueueLst<Data> & q) : List<Data> (q) {};

  // Move constructor
  inline QueueLst(QueueLst<Data> && q) : List<Data> (std::move(q)) {};
  

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst()= default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst & operator= (const QueueLst<Data> &);

  // Move assignment
  QueueLst & operator= (QueueLst<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator ==(const QueueLst<Data> &) const noexcept;
  inline bool operator !=(const QueueLst<Data> &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override;
  Data & Head() override;
  void Dequeue() override;
  Data HeadNDequeue() override;
  void Enqueue (const Data &) override;
  void Enqueue (Data &&) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

   using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif