//Vincenzo Capasso N86004259

#include "htclsadr.hpp"

namespace lasd 
{
// method of class htclsadr and specific operator

//copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& table_hash) 
{
    HashTableClsAdr<Data>* temporary = new HashTableClsAdr<Data>(table_hash);
    std::swap(*this, *temporary);
    delete temporary;
    return *this;
}
//move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& table_hash) noexcept 
{
    std::swap(cls_table,table_hash.cls_table);
    std::swap(size, table_hash.size);
    std::swap(one_p, table_hash.one_p);
    std::swap(two_p, table_hash.two_p);
    std::swap(gradezza_tab, table_hash.gradezza_tab);
    return *this;
}

//comparison operators

//OP ==
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& table_hash) const noexcept 
{
    if(size != table_hash.size) 
    {
         return false;
    }
    else
    {
        for(ulong i = 0; i<gradezza_tab; i++) 
        {
            if(cls_table[i].Size()!=0) 
            {
                BTInOrderIterator<Data> in_it(cls_table[i]);
                while(!(in_it.Terminated())) 
                {
                    if(!(table_hash.Exists(in_it.operator*()))) {
                        return false;
                    }
                    in_it.operator++();
                }
            }
        }
        return true;
    }
}

//Resize
template <typename Data>
void HashTableClsAdr<Data>::Resize(ulong nuova_s) 
{
    HashTableClsAdr<Data>* temporary = new HashTableClsAdr<Data>(nuova_s);
    for(ulong i = 0; i<gradezza_tab; i++) 
    {
        if(cls_table[i].Size()!=0) 
        {
            BTInOrderIterator<Data> in_it(cls_table[i]);
            
            while(!(in_it.Terminated())) {
                Data dat_of_h = in_it.operator*();
                temporary->Insert(dat_of_h);
                in_it.operator++();
            }

        }        
    }
    std::swap(*this, *temporary);
    delete temporary;
}

}

//Vincenzo Capasso N86004259