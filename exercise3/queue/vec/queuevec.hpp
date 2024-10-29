//Vincenzo Capasso N86004259

#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

#define INI_SIZE 12


namespace lasd 
{


template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data> 
{

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;

  ulong head = 0;
  ulong tail = 0;
  ulong head_ind = 0;

public:

  // Default constructor
  QueueVec() { size = INI_SIZE; elements = new Data [INI_SIZE];}


  /* ************************************************************************ */

  // Specific constructor
  // QueueVec(argument) specifiers; // A stack obtained from a TraversableContainer
  inline QueueVec(const TraversableContainer<Data> &cont_travers) : Vector<Data>::Vector(cont_travers), head(0), tail(cont_travers.Size()), head_ind(cont_travers.Size()) { if(size < INI_SIZE) Resize(INI_SIZE);}

  // QueueVec(argument) specifiers; // A stack obtained from a MappableContainer
  inline QueueVec(MappableContainer<Data> & cont_mappabl) : Vector<Data>::Vector(cont_mappabl), head(0), tail(cont_mappabl.Size()), head_ind(cont_mappabl.Size()) { if(size < INI_SIZE) Resize(INI_SIZE);}

  /* ************************************************************************ */

  // Copy constructor
  // QueueVec(argument);
  QueueVec(const QueueVec & cop_que) : Vector<Data>::Vector(cop_que), head(cop_que.head), tail(cop_que.tail), head_ind(cop_que.head_ind) {};

  // Move constructor
  // QueueVec(argument);
   QueueVec(QueueVec && mov_que) noexcept : Vector<Data>::Vector(std::move(mov_que)) 
   {
    std::swap(head, mov_que.head);
    std::swap(tail, mov_que.tail);
    std::swap(head_ind, mov_que.head_ind);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueVec & operator=(const QueueVec & cpy_qvec)
  {

    Vector<Data>::operator=(cpy_qvec);
    head = cpy_qvec.head;
    tail = cpy_qvec.tail;
    head_ind = cpy_qvec.head_ind;
    return (*this); 
} 

  // Move assignment
  inline QueueVec & operator=(QueueVec && mv_qvec) noexcept
  {
    Vector<Data>::operator=(std::move(mv_qvec));
    std::swap(head, mv_qvec.head);
    std::swap(tail, mv_qvec.tail);
    std::swap(head_ind, mv_qvec.head_ind);
    return (*this);
  }
  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const QueueVec&) const noexcept;
  inline bool operator!=(const QueueVec & dis_qvec) const noexcept { return !((*this)== dis_qvec); }

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override { if(head_ind == 0) { throw std::length_error("Coda Vuota!");} return (*this)[head];} 
  Data & Head() override { if(head_ind == 0) { throw std::length_error("Coda Vuota!");} return (*this)[head]; }

  inline void Dequeue() override;
  Data HeadNDequeue() override;
  void Enqueue(const Data &) override; 
  void Enqueue(Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  inline bool Empty() const noexcept override { return (head_ind==0);}

  inline ulong Size() const noexcept override { return head_ind; }
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  inline void Clear() override { Resize(INI_SIZE); head = tail = head_ind = 0;}

  void Resize(ulong) override;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuevec.cpp"
#endif