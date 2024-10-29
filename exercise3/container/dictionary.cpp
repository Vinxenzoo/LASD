//Vincenzo Capasso N86004259
#include "dictionary.hpp"

namespace lasd 
{
    //Copy
    template<typename Data>
    inline bool DictionaryContainer<Data> :: InsertAll(const TraversableContainer<Data> & co )
    {
        bool all = true;
        co.Traverse(
            [this, &all](const Data & d) {
                all &= this->Insert(d);
            }
        );
        return all;
    }

    //Move
    template<typename Data>
    inline bool DictionaryContainer<Data> :: InsertAll(MappableContainer<Data> && co )
    {
        bool all = true;
        co.Map(
            [this, &all](const Data & d) {
                all &= this->Insert(std::move(d));
            }
        );
        return all;
    }


    //Rimozione
    template<typename Data>
    inline bool DictionaryContainer<Data> :: RemoveAll(const TraversableContainer<Data> & co )
    {
        bool all = true;
        co.Traverse(
            [this, &all](const Data & d)
             {
                all &= this->Remove(d);
            }
        );
        return all;
    }



/* ************************************************************************** */

//some
template<typename Data>
inline bool DictionaryContainer<Data> :: InsertSome(const TraversableContainer<Data> & co )
    {
        bool so = true;
        co.Traverse(
            [this, &so](const Data & d) {
                so |= this->Insert(d);
            }
        );
        return so;
    }

template<typename Data>
inline bool DictionaryContainer<Data> :: InsertSome(MappableContainer<Data> && co )
    {
        bool so = true;
        co.Map(
            [this, &so](const Data & d) {
                so |= this->Insert(std::move(d));
            }
        );
        return so;
    }

template<typename Data>
    inline bool DictionaryContainer<Data> :: RemoveSome(const TraversableContainer<Data> & co )
    {
        bool so = true;
        co.Traverse(
            [this, &so](const Data & d)
             {
                so |= this->Remove(d);
            }
        );
        return so;
    }


}


