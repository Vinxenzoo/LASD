//Vincenzo Capasso N86004259

#include "queuelst.hpp"

namespace lasd 
{
    //copy
template <typename Data>
QueueLst<Data> &  QueueLst<Data>::operator= (const QueueLst<Data> & q) 
{
     List<Data>:: operator =(q);
     return *this;
}

//move
template <typename Data>
QueueLst<Data> &  QueueLst<Data>::operator= (QueueLst<Data> && q) noexcept
{
     List<Data>:: operator =(std::move(q));
     return *this;
}

/* ************************************************************************** */

template <typename Data>
bool QueueLst<Data> :: operator == (const QueueLst<Data> & q) const noexcept
{
    return List<Data>:: operator ==(q);
}

template <typename Data>
bool QueueLst<Data> :: operator != (const QueueLst<Data> & q) const noexcept
{
    return List<Data>:: operator !=(q);
}

/* ************************************************************************** */

//metodi che consentono l'implementazione della queuelst

template <typename Data>
const Data & QueueLst<Data> :: Head() const
{
    return List<Data>:: Front();
}

template <typename Data>
Data & QueueLst<Data> :: Head ()
{
    return List<Data>:: Front();
}

template <typename Data>
void QueueLst<Data> :: Dequeue ()
{
    return List<Data>:: RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data> :: HeadNDequeue ()
{
    return List<Data>:: FrontNRemove();
}

template <typename Data>
void QueueLst<Data> :: Enqueue (const Data & d)
{
    return List<Data>:: InsertAtBack(d);
}

template <typename Data>
void QueueLst<Data> :: Enqueue (Data && d)
{
    return List<Data>:: InsertAtBack(d);
}

}


