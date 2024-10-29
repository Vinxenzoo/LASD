//Vincenzo Capasso N86004259

#include "htopnadr.hpp"

namespace lasd 
{

//Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& table_hash) 
{
    size = table_hash.size;
    gradezza_tab = table_hash.gradezza_tab;

    one_p = table_hash.one_p;
    two_p = table_hash.two_p;

    tab = table_hash.tab;
    vec_in = table_hash.vec_in;

    grandezza = table_hash.grandezza;
}

//Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& table_hash) noexcept 
{
    std::swap(size, table_hash.size);
    std::swap(gradezza_tab, table_hash.gradezza_tab);

    std::swap(one_p, table_hash.one_p);
    std::swap(two_p, table_hash.two_p);

    std::swap(tab, table_hash.tab);
    std::swap(vec_in, table_hash.vec_in);

    std::swap(grandezza, table_hash.grandezza);
}

//Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& table_hash) noexcept 
{
    std::swap(size, table_hash.size);
    std::swap(gradezza_tab, table_hash.gradezza_tab);

    std::swap(one_p, table_hash.one_p);
    std::swap(two_p, table_hash.two_p);

    std::swap(tab, table_hash.tab);
    std::swap(vec_in, table_hash.vec_in);

    std::swap(grandezza, table_hash.grandezza);
    return *this;
} 

//Insert
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat_of_h) 
{
    //se la grandezza della tabella supera il 75% allora ingrandiscila con la resize
    grandezza = (static_cast<double>(size)/static_cast<double>(gradezza_tab))*100;
    if((grandezza) > 75) { Resize(2*gradezza_tab+1); }

    if(Exists(dat_of_h)) 
    {
        return false;
    }
    else
    {
        ulong i = FindEmpty(dat_of_h, 0);
        if(i > gradezza_tab) 
        {
            return false;
        }
        else
        {
            ulong pos = HashKey(dat_of_h, i);
            if(vec_in[pos] == 'E' || vec_in[pos] == 'R') 
            {
                tab[pos] = dat_of_h;
                vec_in[pos] = 'F';
                size++;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

//Insert move
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat_of_h) noexcept 
{
grandezza = (static_cast<double>(size)/static_cast<double>(gradezza_tab))*100;
    if((grandezza) > 75) { Resize(2*gradezza_tab+1); }

    if(Exists(dat_of_h)) 
    {
        return false;
    }
    else
    {
        ulong i = FindEmpty(dat_of_h, 0);
        if(i > gradezza_tab) 
        {
            return false;
        }
        else
        {
            ulong pos = HashKey(dat_of_h, i);
            if(vec_in[pos] == 'E' || vec_in[pos] == 'R') 
            {
                tab[pos] = dat_of_h;
                vec_in[pos] = 'F';
                size++;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

//Resize
template <typename Data>
void HashTableOpnAdr<Data>::Resize(ulong nuova_s) 
{
    ulong new_s;
    if(!Poss_DiResize(nuova_s)) { return; }

    new_s = ProxPot2(nuova_s);
    if(new_s == gradezza_tab) { return;}

    HashTableOpnAdr<Data>* temporary = new HashTableOpnAdr<Data>(new_s);

    for(ulong i=0; i<gradezza_tab; i++) 
    {
        if(vec_in[i] == 'F') 
        {
            temporary->Insert(tab[i]);
        }
    }
    std::swap(*this, *temporary);
    delete temporary;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Poss_DiResize(ulong nuova_s) const noexcept 
{
    if(nuova_s > gradezza_tab) 
    {
         return true; 
    } 
    else 
    {
        if(nuova_s == gradezza_tab) { return false; }

        ulong new_cap = (static_cast<double>(size)/static_cast<double>(nuova_s))*100;
        if(new_cap < 75) { return true;}

        return false;
    } 

}

//Find
template <typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data& dat_of_h, ulong new_i) const noexcept 
{
    ulong inizio = HashKey(dat_of_h, new_i);
    ulong coll = 0;

    while(new_i < gradezza_tab) 
    {
        if(tab[inizio] == dat_of_h) { return new_i; }
        if(vec_in[inizio] =='E') { return gradezza_tab;}

        coll++;
        new_i++; 
        inizio = HashKey(dat_of_h, new_i);
    }
    return new_i;
}

//FindEmpty
template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data& dat_of_h, ulong new_i) const noexcept 
{
    ulong inizio = HashKey(dat_of_h, new_i);
    ulong coll = 0;

    while(new_i < gradezza_tab) 
    {
        if(vec_in[inizio] == 'E' || vec_in[inizio] == 'R') { return new_i;}

        coll++;
        new_i++;
        inizio = HashKey(dat_of_h, new_i);
    }
    return new_i;
}    

//Remove
template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dat_of_h, ulong new_i) 
{
    if(size > 0) 
    {
        ulong indice = Find(dat_of_h, new_i);
        
        if(indice < gradezza_tab) 
        {
            ulong pos = HashKey(dat_of_h, indice);  
            
            if(vec_in[pos] == 'F' && tab[pos] == dat_of_h) 
            {
                vec_in[pos] = 'R';
                size--;
                return true;
            }
        }
    }
    return false;
}



}

//Vincenzo Capasso N86004259