//Vincenzo Capasso N86004259

#include <stdexcept>
#include "linear.hpp"


namespace lasd
{

template <typename Data>
bool LinearContainer<Data>:: operator== (const LinearContainer<Data> & seq) const noexcept
{
    if(size != seq.size) return false;
    for(ulong i =0; i< seq.size; i++)
    {
        if(this->operator[](i) != seq.operator[](i)) return false;
    }
    return true;
}   

template <typename Data>
bool LinearContainer<Data>:: operator!= (const LinearContainer<Data> & seq) const noexcept
{
    return !(this->operator==(seq));
}

/* ********************************DATA ACCESS METHOD****************************************** */

template <typename Data>
const Data & LinearContainer<Data>:: Front() const 
{
    if(size == 0) throw std::length_error(" hai invocato  front() su un container vuoto. ");
    return operator[](0);
}

template <typename Data>
 Data & LinearContainer<Data>:: Front()
{ 
    if(size == 0) throw std::length_error(" hai invocato front() su un container vuoto. ");
    return operator[](0);
}

template <typename Data>
const Data & LinearContainer<Data>:: Back() const 
{
    if(size == 0) throw std::length_error(" hai invocato back() su un container vuoto. ");
    return operator[](size-1);
}

template <typename Data>
 Data & LinearContainer<Data>:: Back() 
{
    if(size == 0) throw std::length_error(" hai invocato back() font su un container vuoto. ");
    return operator[](size-1);
}



/* ************************************************************************** */

//funzione specifica 
template<typename Data>
inline void LinearContainer<Data>:: Traverse (TraverseFun fun) const
{
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

template <typename Data>
inline void LinearContainer<Data>:: PreOrderTraverse(TraverseFun fun) const
{
   for (ulong ind=0;  ind< size; ++ind)
   {
      fun(this->operator[](ind));
   }
}

template <typename Data>
inline void LinearContainer<Data>:: PostOrderTraverse(TraverseFun fun) const
{
   ulong i=size;
   while(i>0)
   {
      fun(this->operator[](--i));
   }
}

/* ************************************************************************** */

//funzione specifica map

template <typename Data>
inline void LinearContainer<Data>:: Map(MapFun fun) 
{
    PreOrderMap(fun);
}

template <typename Data>
inline void LinearContainer <Data>:: PreOrderMap(MapFun fun) 
{
    for(ulong i=0; i<size; ++i)
    {
        fun(this->operator[](i));
    }
}

template <typename Data>
inline void LinearContainer<Data>:: PostOrderMap(MapFun fun) 
{
   
   for( ulong i = size; i > 0; i--)
    {
        fun(this->operator[](i-1));
    }
}


/* ****************************SORTABLE CONTAINER********************************************** */

template<typename Data>
void SortableLinearContainer<Data>:: Sort() noexcept
{
    quicksort(0, size-1);
}

template<typename Data>
void SortableLinearContainer<Data>:: quicksort(ulong p, ulong r) noexcept
{
     if(p < r)
     {
        ulong q = partition (p,r);
        quicksort (p,q);
        quicksort (q+1, r);
     }
}

template<typename Data>
ulong SortableLinearContainer<Data>:: partition(ulong p, ulong r) noexcept
{
    Data x = operator[](p);
    ulong i = p -1;
    ulong j = r +1;

    do
    {
      do{j--;} 
      while ( x< operator[](j));

      do { i++; }
      while (x > operator[](i));
   
      if(i < j) { std::swap(operator[](i), operator[](j));}
    }
    while (i < j);
    return j;
}

}
