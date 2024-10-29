//Vincenzo Capasso N86004259

#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

#define TABLE_MINSIZE 256
#define TABLE_MAXSIZE 1048576

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr: public virtual HashTable<Data> 
{

private:

protected:

  using HashTable<Data>::size;

  //two numbers that they'll be utilizate for the hashing
  using HashTable<Data>::one_p;
  using HashTable<Data>::two_p;

  //randomic generator, and randomic genetations
  using HashTable<Data>::first_num;
  using HashTable<Data>::second_num;
  using HashTable<Data>::num_gen;
  
  //hash and table size
  using HashTable<Data>::gradezza_tab;
  using HashTable<Data>::hash;

  //Functions
  using HashTable<Data>::HashKey;
  using HashTable<Data>::Insert;
  using HashTable<Data>::InsertAll;

  double grandezza = 0;
  Vector<Data> tab;
  Vector<char> vec_in;

  // ...

public:

  // Default constructor
  HashTableOpnAdr() 
  {
    one_p = 2*(first_num(num_gen))+1;
    two_p = 2*(second_num(num_gen));

    gradezza_tab = TABLE_MINSIZE;
    size = 0;

    tab.Resize(gradezza_tab);
    vec_in.Resize(gradezza_tab);

    for(ulong i=0; i<gradezza_tab; i++) 
    {
        vec_in[i] = 'E'; 
    }
    grandezza = (static_cast<double>(size)/static_cast<double>(gradezza_tab))*100;
  }

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(ulong nuova_s)
  {
    one_p = 2*(first_num(num_gen))+1;
    two_p = 2*(second_num(num_gen));

    size = 0;
    gradezza_tab = ProxPot2(nuova_s);

    tab.Resize(gradezza_tab);
    vec_in.Resize(gradezza_tab);

    for(ulong i=0; i<gradezza_tab; i++) 
    {
       vec_in[i] = 'E'; 
    }
    grandezza = (static_cast<double>(size)/static_cast<double>(gradezza_tab))*100;
  }

  /* ************************************************************************ */

  HashTableOpnAdr(const TraversableContainer<Data> & trav_con)  : HashTableOpnAdr() { InsertAll(trav_con);}
  HashTableOpnAdr(ulong nuova_s, const TraversableContainer<Data> & trav_con): HashTableOpnAdr(nuova_s) { InsertAll(trav_con);}
  HashTableOpnAdr(MappableContainer<Data> && map_con): HashTableOpnAdr() { InsertAll(std::move(map_con));}
  HashTableOpnAdr(ulong nuova_s, MappableContainer<Data> && map_con) : HashTableOpnAdr(nuova_s) { InsertAll(std::move(map_con));}

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data>&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr<Data> & table_hash)
  {
    HashTableOpnAdr<Data>* temporary = new HashTableOpnAdr(table_hash);
    std::swap(*this, *temporary);
    delete temporary;
    return *this;
  }

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data> & table_hash) const noexcept 
  {
    if(size != table_hash.size) 
    {
          return false;
    }
    else
    {
        for(ulong i = 0; i<gradezza_tab; i++) 
        {
            if(vec_in[i] == 'F')
            {
                if(!(table_hash.Exists(tab[i]))) 
                {
                    return false;
                }
            }
        }
        return true;
    }
}
  bool operator!=(const HashTableOpnAdr<Data> & table_hash) const noexcept { return !(*this == table_hash);}

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; 
  bool Insert(Data&&) noexcept override; 
  bool Remove(const Data & dat_of_h) override 
  {
    grandezza = (static_cast<double>(size)/static_cast<double>(gradezza_tab))*100;
  
    bool res = Remove(dat_of_h, 0);
    if(grandezza < 10) { Resize((gradezza_tab/2)-1);}
    return res;
   } 

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data & dat_of_h) const noexcept override 
  {
    if(size < 0) 
    {
      return false;
    }
    else
    {
        ulong index = Find(dat_of_h, 0);   
        if(index > gradezza_tab) 
        {
            return false;
        }
        else
        {
            ulong pos = HashKey(dat_of_h, index);
            if(vec_in[pos] == 'F' && tab[pos] == dat_of_h) 
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(ulong) override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override
  {
    gradezza_tab = TABLE_MINSIZE;
    size = 0;

    tab.Clear();
    tab.Resize(gradezza_tab);

    vec_in.Resize(gradezza_tab);

    for(ulong i = 0; i<gradezza_tab; i++) 
    {
        vec_in[i] = 'E';
    }
  }

protected:

  // Auxiliary member functions

  virtual ulong HashKey(const Data & data, ulong index) const noexcept
  {
    ulong key = hash(data);
    return ((HashKey(key)+((index*index)+index)/2)%gradezza_tab); 

    //Implemented with quadratic probing
}

  virtual ulong Find(const Data&, ulong) const noexcept;
  virtual ulong FindEmpty(const Data&, ulong) const noexcept;
  virtual bool Remove(const Data&, ulong);

  bool Poss_DiResize(ulong) const noexcept;

   ulong ProxPot2(ulong nuova_s) const noexcept
  {
    ulong new_S = TABLE_MINSIZE;

    while(new_S < nuova_s) 
    {
        if(new_S >= TABLE_MAXSIZE) 
        {
            break;   
        }
        new_S = new_S << 1;
    } 
    return new_S;
  }

};

}

#include "htopnadr.cpp"

#endif

//Vincenzo Capasso N86004259