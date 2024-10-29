//Vincenzo Capasso N86004259

#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd 
{

template <typename Data>
class HashTableClsAdr: public virtual HashTable<Data> 
{

private:

protected:

  using HashTable<Data>::size;

   //two numbers that they'll be utilizate for the hashing
  using HashTable<Data>::one_p;
  using HashTable<Data>::two_p;

  //two parameters of hash table
  using HashTable<Data>::gradezza_tab;
  using HashTable<Data>::hash;

  //functions of hash table
  using HashTable<Data>::HashKey;
  using HashTable<Data>::Insert;
  using HashTable<Data>::InsertAll;

  BST<Data>* cls_table = nullptr;

public:

  // Default constructor
  HashTableClsAdr() { cls_table = new BST<Data>[gradezza_tab]{}; }

  /* ************************************************************************ */

  // Specific constructors
   HashTableClsAdr(ulong new_s)
   {
    if(new_s < 251) { new_s = 251; }
    if(new_s >= 10000) { new_s = 9973; }
    if(new_s != 251 && new_s != 9973) { new_s = ProxPrime(new_s);}

    gradezza_tab = new_s;
    cls_table= new BST<Data>[gradezza_tab]{};
   }


   HashTableClsAdr(const TraversableContainer<Data> & trav_con) : HashTableClsAdr() { InsertAll(trav_con);}
   HashTableClsAdr(ulong nuova_s, const TraversableContainer<Data> & trav_con): HashTableClsAdr(nuova_s) { InsertAll(trav_con);}
   HashTableClsAdr(MappableContainer<Data>&& map_con) : HashTableClsAdr() { InsertAll(std::move(map_con)); }
   HashTableClsAdr(ulong nuova_s, MappableContainer<Data> && map_con) : HashTableClsAdr(nuova_s) { InsertAll(std::move(map_con)); }

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data> & table_hash) : HashTable<Data>(table_hash) { cls_table = new BST<Data>[gradezza_tab]{}; std::copy(table_hash.cls_table, table_hash.cls_table+gradezza_tab, cls_table); }

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data> && table_hash)  noexcept : HashTable<Data>(std::move(table_hash)) { std::swap(cls_table, table_hash.cls_table); }

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() { delete[] cls_table; }

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr<Data>&);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data> &) const noexcept;
  bool operator!=(const HashTableClsAdr<Data> & table_hash) const noexcept { return !(*this == table_hash); }

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data & dat_of_h) override 
  {
    ulong hash_key = HashKey(hash(dat_of_h));
    if(cls_table[hash_key].Insert(dat_of_h)) { size++; return true; } 

    return false;
  }

  bool Insert(Data && dat_of_h) noexcept override
  {
    ulong key = HashKey(hash(dat_of_h));
    if(cls_table[key].Insert(std::move(dat_of_h))) { size++; return true; } 

    return false;
  }

  bool Remove(const Data & dat_of_h) override
  {
    ulong hash_key = HashKey(hash(dat_of_h));
    if(cls_table[hash_key].Remove(dat_of_h)) { size--; return true;} 

    return false;
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data & dat_of_h) const noexcept override { ulong hash_key = HashKey(hash(dat_of_h)); return cls_table[hash_key].Exists(dat_of_h);}

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(ulong) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override 
  {
    delete[]cls_table;
    cls_table = new BST<Data>[gradezza_tab]{};
    size = 0;
  }

  protected:

  
  ulong ProxPrime(ulong search_v) const noexcept
  {
    for (ulong i = 2; i <= search_v/2; ++i) 
    {if (search_v % i == 0) { search_v+=1; i = 2;} }

    return search_v;
  }
  
  /*
  ulong ProxPrime(ulong search_v) const noexcept
  {
    if(search_v <= 1 ) return 2;

    ulong prime = search_v;
    bool found = false;

    while(!found)
    {
      if(isprime(prime)) { found = true;}
      else { prime++; }
    }

    return prime;
  }

   static bool isprime(ulong num)
   {
     if(num <= 1) return false;
     if(num <= 3) return true;

     if(num % 2 ==0 || num % 3 == 0) return false;

     for (ulong i = 5; i * i <= num; i+= 6)
     {
       if(num % i ==0 || num % (i+2) ==0) return false;
     }

     return true;
   }
   */

};

}

#include "htclsadr.cpp"

#endif

//Vincenzo Capasso N86004259


