//Vincenzo Capasso N86004259

#include "mappable.hpp"
#include "traversable.hpp"

namespace lasd 
{

//funzione specifica PreOrderMappableContainer

template <typename Data>
inline void PreOrderMappableContainer<Data>:: Map(MapFun fun) 
{
    PreOrderMap(fun);
}


/* ************************************************************************** */

//funzione specifica PostOrderMappableContainer

template <typename Data>
inline void PostOrderMappableContainer<Data>:: Map(MapFun fun) 
{
    PostOrderMap(fun);
}

/* ************************************************************************** */

//funzione specifica InOrderMappableContainer

template <typename Data>
inline void InOrderMappableContainer<Data>:: Map(MapFun fun) 
{
    InOrderMap(fun);
}

/* ************************************************************************** */

//funzione specifica InOrderMappableContainer

template <typename Data>
inline void  BreadthMappableContainer<Data>:: Map(MapFun fun) 
{
    BreadthMap(fun);
}


}