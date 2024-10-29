//Vincenzo Capasso N86004259

#include "traversable.hpp"

namespace lasd 
{
    template <typename Data>
    template <typename Accumulator>
     inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun ,  Accumulator ac)  const  
    {
        Traverse ([fun, &ac](const Data & d)
         {
            ac = fun(d, ac);
         }
       );
       return ac;

    }

    template <typename Data>
    inline bool TraversableContainer<Data>::Exists (const Data & v) const noexcept
    {
       bool exist= false;
       Traverse 
       ([v, &exist](const Data & d)
         {
            exist |= (d == v);
         }
       );
       return exist;
    }




/* ************************************************************************** */

 template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>:: PreOrderFold(FoldFun<Accumulator> fun, Accumulator ac) const 
    {
        PreOrderTraverse ([fun, &ac](const Data & d)
         {
            ac = fun(d, ac);
         }
       );
       return ac;

    }

    template <typename Data>
    void PreOrderTraversableContainer<Data>:: Traverse(TraverseFun Fun) const
    {
        PreOrderTraverse(Fun);
    }

/* ************************************************************************** */

template <typename Data>
    template <typename Accumulator>
    inline Accumulator PostOrderTraversableContainer<Data>:: PostOrderFold(FoldFun<Accumulator> fun, Accumulator ac) const 
    {
        PostOrderTraverse ([fun, &ac](const Data & d)
         {
            ac = fun(d, ac);
         }
       );
       return ac;

    }

    template <typename Data>
    void PostOrderTraversableContainer<Data>:: Traverse(TraverseFun Fun) const
    {
        PostOrderTraverse(Fun);
    }

/* ************************************************************************* */

template <typename Data>
    template <typename Accumulator>
    inline Accumulator InOrderTraversableContainer<Data>:: InOrderFold(FoldFun<Accumulator> fun, Accumulator ac) const 
    {
        InOrderTraverse ([fun, &ac](const Data & d)
         {
            ac = fun(d, ac);
         }
       );
       return ac;

    }

    template <typename Data>
    void InOrderTraversableContainer<Data>:: Traverse(TraverseFun Fun) const
    {
        InOrderTraverse(Fun);
    }

  /* ************************************************************************* */

  template <typename Data>
    template <typename Accumulator>
    inline Accumulator BreadthTraversableContainer<Data>:: BreadthFold(FoldFun<Accumulator> fun, Accumulator ac) const 
    {
        BreadthTraverse ([fun, &ac](const Data & d)
         {
            ac = fun(d, ac);
         }
       );
       return ac;

    }

    template <typename Data>
    void BreadthTraversableContainer<Data>:: Traverse(TraverseFun Fun) const
    {
        BreadthTraverse(Fun);
    }



}
