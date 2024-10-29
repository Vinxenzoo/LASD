//Vincenzo Capasso N86004259

#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

#define INIZ_SIZE 5


namespace lasd 
{

/* ************************************************************************** */

template <typename Data>
class StackVec: virtual public Stack<Data>, virtual public Vector<Data>
{

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;
  unsigned long lunghezza_att = 0;
  // ...

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
   StackVec(const TraversableContainer<Data> & ); 
   StackVec(MappableContainer<Data> && ); 

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data> & stk_cop) noexcept{ this->operator=(stk_cop);}

  // Move constructor
  StackVec(StackVec<Data> && stk_mov) noexcept { this->operator=(std::move(stk_mov)); }

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline StackVec & operator=(const StackVec & stk_cop) 
  {
        Vector<Data>::operator=(stk_cop);
        lunghezza_att = stk_cop.lunghezza_att;
        return *this;
    }

  // Move assignment
  inline StackVec & operator=(StackVec && stk_mov) noexcept
  {
        Vector<Data>::operator=(std::move(stk_mov));
        std::swap(lunghezza_att, stk_mov.lunghezza_att);
        return *this;
    }


  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackVec & ) const noexcept;
  inline bool operator!=(const StackVec & stk_diff) const noexcept { return !((*this)==stk_diff);};

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override; 
   Data & Top() override; 
   void Pop() override; 
  Data TopNPop() override; 
   void Push(const Data &) override; 
   void Push(Data &&) override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept{ return lunghezza_att == 0;}; 

  inline unsigned long Size() const noexcept override { return lunghezza_att; };

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override  { Resize(INIZ_SIZE); lunghezza_att = 0; };

  void Resize(unsigned long) override; 

protected:

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif