//Vincenzo Capasso N86004259

#include <iostream>

#include "vector.hpp"
#include <string>


namespace lasd 
{

template <typename Data>
Vector<Data>:: Vector(const ulong newsiz)
{
    size =newsiz;
    elements = new Data[size];
}

template <typename Data>
Vector<Data>:: Vector(const TraversableContainer<Data> & c)
{
    this->Resize(c.Size());
    ulong index =0;
    c.Traverse( 
        [this, &index] (const Data & d) {
            (this->elements)[index] = d;
            index++;
        }
    );
}

template <typename Data>
Vector<Data>:: Vector(MappableContainer<Data> && c) 
{
    this->Resize(c.Size());
    ulong index =0;
    c.Map( 
        [this, &index] (Data & d) {
            (this->elements)[index] = std::move(d);
            index++;
        }
    );
}

/* ********************************COPY AND MOVE CONSTRUCTOR****************************************** */

//copy
template <typename Data>
Vector<Data> :: Vector(const Vector<Data> & ve)
{   
    size = ve.size;
    elements = new Data[size];
    std::copy(ve.elements, ve.elements + size, elements);
}

//move
template <typename Data>
Vector<Data> :: Vector(Vector<Data> && ve) noexcept
{
   this->operator=(std::move(ve));
  
}

/* *********************************Distruttore***************************************** */

template <typename Data>
Vector<Data>:: ~Vector()
{ delete[] elements;}

/* *********************************Assignement***************************************** */

//Copy assignement
template <typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & ve)
{
    /*
    Resize(ve.size);
    std::copy(ve.elements, ve.elements + size, elements);

    return *this;
    */
   Vector<Data> tm {ve};
   std::swap(tm, *this);
   return *this;
    
}

//move assignement
template <typename Data>
Vector<Data> & Vector<Data>::operator=( Vector<Data> && ve) 
{
   
      std:: swap (size, ve.size);
      std:: swap (elements, ve.elements);
      return *this;

    
}


/* *********************************operatori di comparazione***************************************** */

template <typename Data>
bool Vector<Data>:: operator== (const Vector<Data> & ve) const noexcept
{
    if(size != ve.size)
    {
        return false;
    }
    else
    {
       for(ulong i=0; i < size; ++i)
        {
            
            if(elements[i] != ve[i])
            {
                return false;
            }
        }
     
         return true;
    }

 
}

template <typename Data>
inline bool Vector<Data>:: operator!= (const Vector<Data> & ve) const noexcept
{
    return  !(*this == ve);
}

/* *********************************funzioni specifiche***************************************** */

template <typename Data>
void Vector<Data>:: Clear()
{
   delete[] elements;
   elements = nullptr;
   size =0;
}

template <typename Data>
void Vector<Data>:: Resize(const ulong nsize)
{
    if(nsize == 0 )
    {
        Clear();
    }
    else
    {
        if(size != nsize)
        {
            Data *Tmelements = new Data[nsize] {};
            ulong msize = (size < nsize) ? size : nsize;
            for (ulong i=0; i < msize; ++i)
            {
                std::swap(elements[i], Tmelements[i]);
            }
        

        size = nsize;
        std::swap (elements, Tmelements);
        delete[] Tmelements;
        }
    }
}

/* ************************************************************************** */

//funzioni specifiche della classe vettore

template <typename Data>
const Data & Vector<Data>:: operator[] (const ulong i) const
{
    if(i < size)
    {
        return elements[i];
    }
    else
    { 
       throw std::out_of_range("indice immesso troppo grande per la taglia del vettore");
    }
}

template <typename Data>
Data & Vector<Data>:: operator[] (const ulong i)
{
    if(i < size)
    {
        return elements[i];
    }
    else
    { 
       throw std::out_of_range("indice immesso troppo grande per la taglia del vettore");
    }
}

template <typename Data>
const Data & Vector<Data>:: Front () const
{
    if(size != 0)
    {
        return elements[0];
    }
    else
    { 
       throw std::length_error("Stai provando ad accedere ad un vettore vuoto");
    }
}

template <typename Data>
 Data & Vector<Data>:: Front () 
{
    if(size != 0)
    {
        return elements[0];
    }
    else
    { 
       throw std::length_error("Stai provando ad accedere ad un vettore vuoto");
    }
}

template <typename Data>
const Data & Vector<Data>:: Back () const 
{
    if(size != 0)
    {
        return elements[size - 1];
    }
    else
    { 
       throw std::length_error("Stai provando ad accedere ad un vettore vuoto");
    }
}

template <typename Data>
Data & Vector<Data>:: Back ()
{
    if(size != 0)
    {
        return elements[size - 1];
    }
    else
    { 
       throw std::length_error("Stai provando ad accedere ad un vettore vuoto");
    }
}

template<typename Data>
inline Data * Vector<Data>:: din_alloc(ulong nsize)
{
    return (nsize) ? new Data[nsize] : nullptr;
}

/* **********************************Classe Sotable Vector**************************************** */

//costruttori specifici
template <typename Data>
SortableVector<Data>:: SortableVector (const ulong news) :Vector<Data>::Vector (news) {};

template <typename Data>
SortableVector<Data>:: SortableVector(const TraversableContainer<Data> & co) : Vector<Data>::Vector(co) {};

template <typename Data>
SortableVector<Data>:: SortableVector(MappableContainer<Data> && co) : Vector<Data>::Vector(std::move(co)) {};


/* **********************************Classe Sotable Vector**************************************** */

//Copy costructor
template <typename Data>
SortableVector<Data>:: SortableVector (const SortableVector<Data> & ve): Vector<Data>::Vector(ve) {};

//Move
template <typename Data>
SortableVector<Data>:: SortableVector (SortableVector<Data> && ve): Vector<Data>::Vector(std::move(ve))
 {}

/* **********************************Classe Sotable Vector**************************************** */

template <typename Data>
SortableVector<Data> & SortableVector<Data>:: operator= (const SortableVector<Data> & ve)
{
    Vector<Data>::operator=(ve);
    return *this;
}

template <typename Data>
SortableVector<Data> & SortableVector<Data>:: operator= (SortableVector<Data> && ve)
{
    Vector<Data>::operator=(std::move(ve));
    return *this;
}

template <typename Data>
Data & SortableVector<Data>:: operator[] (const ulong i)
{
    if(i < size)
    {
        return elements[i];
    }
    else
    { 
       throw std::out_of_range("indice immesso troppo grande per la taglia del vettore");
    }
}

template <typename Data>
const Data & SortableVector<Data>:: operator[] (const ulong i) const
{
    if(i < size)
    {
        return elements[i];
    }
    else
    { 
       throw std::out_of_range("indice immesso troppo grande per la taglia del vettore");
    }
}
/* **********************************Classe Sotable Vector**************************************** */


//ordinamento
template <typename Data>
void SortableVector<Data> :: Sort() noexcept
{
    if(size ==0 || size ==1) return;
    bubblesort();
}


template <typename Data>
void SortableVector<Data> :: bubblesort()
{
    for (uint i=0; i < size-1; ++i)
    {
        for (uint j=0; j < size-1; ++j)
        {
            if(elements[j] > elements [j+1])
            {
                std::swap (elements[j], elements[j+1]);
            }
        }
    }
}

template<typename Data>
void SortableVector<Data>:: quicksort(ulong p, ulong r) noexcept
{
     if(p < r)
     {
        ulong q = partition (p,r);
        quicksort (p,q);
        quicksort (q+1, r);
     }
}

template<typename Data>
ulong SortableVector<Data>:: partition(ulong p, ulong r) noexcept
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
