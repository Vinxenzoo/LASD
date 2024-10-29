//Vincenzo Capasso N86004259

#include "stacklst.hpp"

namespace lasd 
{

//copy
template <typename Data>
StackLst<Data> &  StackLst<Data>::operator= (const StackLst<Data> & st) 
{
     List<Data>:: operator =(st);
     return *this;
}

//move
template <typename Data>
StackLst<Data> &  StackLst<Data>::operator= (StackLst<Data> && st) noexcept
{
     List<Data>:: operator =(std::move(st));
     return *this;
}

/* *********************************Comparison Operator***************************************** */

//operatori per la comparazione
template <typename Data>
bool StackLst<Data> :: operator == (const StackLst<Data> & st) const noexcept
{
    return List<Data>:: operator ==(st);
}

template <typename Data>
bool StackLst<Data> :: operator != (const StackLst<Data> & st) const noexcept
{
    return List<Data>:: operator !=(st);
}

/* ************************************************************************** */

//inserimenti e cancellazioni

template <typename Data>
const Data & StackLst<Data> :: Top () const
{
    return List<Data>:: Front();
}

template <typename Data>
Data & StackLst<Data> :: Top ()
{
    return List<Data>:: Front();
}

template <typename Data>
void StackLst<Data> :: Pop ()
{
    return List<Data>:: RemoveFromFront();
}

template <typename Data>
Data StackLst<Data> :: TopNPop ()
{
    return List<Data>:: FrontNRemove();
}

template <typename Data>
void StackLst<Data> :: Push (const Data & d)
{
    return List<Data>:: InsertAtFront(d);
}

template <typename Data>
void StackLst<Data> :: Push (Data && d)
{
    return List<Data>:: InsertAtFront(d);
}

}

