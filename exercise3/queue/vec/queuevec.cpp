//Vincenzo Capasso N86004259

#include "queuevec.hpp"

namespace lasd 
{

//Compariosn operator
template <typename Data>
inline bool QueueVec<Data>::operator==(const QueueVec<Data> & eq_qvec) const noexcept 
{

    if(head_ind == eq_qvec.head_ind) 
    {

        for(ulong i=0; i<head_ind; i++) 
        {

            if((elements[(head +1) % size]) != (eq_qvec.elements[(eq_qvec.head + 1) % eq_qvec.size])) 
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

//Resize queue
template <typename Data>
void QueueVec<Data>::Resize(ulong size_qvec) 
{
    if(size_qvec == size || size_qvec < INI_SIZE) {
        return;
    } 
    Data *new_data = new Data[size_qvec];

    for(ulong j = 0, i = head; j < head_ind; ++j, i = (i + 1) % size) 
    {
        new_data[j] = elements[i]; 
    }

    delete[] elements;
    elements = new_data;
    head = 0;
    tail = head_ind;
    size = size_qvec;
}

//Specific queue methods
template <typename Data>
inline void QueueVec<Data>::Dequeue() 
{
    if(head_ind == 0) 
    {
        throw std::length_error("Coda Vuota");
    }

    head = (head+1) % size;
    head_ind--;

    if(head_ind == size / 4) 
    {
        Resize(size / 2);
    }

}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() 
{
    if(head_ind == 0) { throw std::length_error("Coda Vuota");}

    Data head = Head(); 
    Dequeue();
    return head;
}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data & data) 
{
    if(head_ind == size) { Resize(size * 2);}
    
    (*this)[tail] = data;
    tail = (tail + 1) % size;
    head_ind++; 
}

template <typename Data>
void QueueVec<Data>::Enqueue(Data && data) 
{
    if(head_ind == size) { Resize(size * 2);}    

    (*this)[tail] = std::move(data);
    tail = (tail + 1) % size;
    head_ind++; 
}


}