//Vincenzo Capasso N86004259

#include "./stackvec.hpp"

namespace lasd 
{

//StackVec specific costructor

template <typename Data>
StackVec<Data>::StackVec() 
{
    size = INIZ_SIZE;
    elements = new Data[size];
}


template<typename Data>
StackVec<Data>:: StackVec(const TraversableContainer<Data> & c)
{
    size = c.Size() ;

    elements = Vector<Data> ::din_alloc(size);
    c.Traverse(
        [this](const Data & d){
            this->Push(d); 
        }
    );

}

template<typename Data>
StackVec<Data>:: StackVec(MappableContainer<Data> && mp) 
{
    size = std::move(mp.Size());

    elements = Vector<Data> ::din_alloc(size);
    mp.Map(
        [this]( Data & d){
            this->Push(std::move(d)); 
        }
    );

}


    template <typename Data>
    inline bool StackVec<Data>::operator==(const StackVec & conf_sta) const noexcept
    {
        if(lunghezza_att!=conf_sta.lunghezza_att)
            return false;

        for(unsigned long i = 0; i < lunghezza_att; ++i)
        {
            if((*this)[i]!=conf_sta[i])
                return false;
        }
        return true;
    };

    template <typename Data>
    inline void StackVec<Data>::Resize(unsigned long new_siz)
    {
        if(new_siz >=INIZ_SIZE)
            Vector<Data>::Resize(new_siz);
        else
            Vector<Data>::Resize(INIZ_SIZE);
    }


    template <typename Data>
    inline const Data & StackVec<Data>::Top() const 
    {
        if(lunghezza_att == 0)
        {
            throw std::length_error("Lo stack e' vuoto.");
        }

        return (*this)[lunghezza_att-1];
    }

    template <typename Data>
    inline Data & StackVec<Data>::Top() 
    {
        if(lunghezza_att == 0)
        {
            throw std::length_error("Lo stack e' vuoto.");
        }

        return (*this)[lunghezza_att-1];
    }

    template <typename Data>
    inline void StackVec<Data>::Pop() 
    {
        if(lunghezza_att == 0)
            throw std::length_error("Lo stack e' vuoto.");
        else
        {
            lunghezza_att--;
            if(lunghezza_att < size / 4)
            {
                Resize(size / 2);
            }
        }
    }

    template <typename Data>
    Data StackVec<Data>::TopNPop() 
    {
        Data top = Top();
        Pop();
        return top;
    }

    template <typename Data>
    inline void StackVec<Data>::Push(const Data & dat_inser) 
    {
        if(lunghezza_att == size)
        {
            Resize(size * 2);
        }

        (*this)[lunghezza_att] = dat_inser;
        lunghezza_att++;
    }

    template <typename Data>
    inline void StackVec<Data>::Push(Data && dat_inser) 
    {
        if(lunghezza_att == size)
        {
            Resize(size * 2);
        }

        (*this)[lunghezza_att] = std::move(dat_inser);
        lunghezza_att++;
    }

}
