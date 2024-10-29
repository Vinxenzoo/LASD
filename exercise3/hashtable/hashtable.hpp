//Vincenzo Capasso N86004259

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include "../container/dictionary.hpp"

namespace lasd 
{

/* ************************************************************************** */

template <typename Data>
class Hashable 
{

public:
  
  //Calcola un valore hash per un oggetto di tipo data    
  ulong operator()(const Data&) const noexcept = 0;

};

/* ************************************************************************** */

template <typename Data>
class HashTable: public virtual ResizableContainer, public virtual DictionaryContainer<Data>
{

private:

protected:  

  using DictionaryContainer<Data>::size;

  /*
  std::random_device è un generatore di numeri casuali non deterministico che viene utilizzato per ottenere un seme casuale per il generatore di numeri pseudo-casuali L'uso delle doppie parentesi {} crea un'istanza temporanea di std::random_device std::default_random_engine è un tipo di generatore di numeri pseudo-casuali fornito dalla libreria standard di C++ Questa parte del codice crea un'istanza di std::default_random_engine chiamata num_gen e la inizializza con il seme ottenuto da std::random_device.
  */
  std::default_random_engine num_gen = std::default_random_engine(std::random_device{}());

  static const ulong num_pri = 10000003;
  ulong one_p = 1;
  ulong two_p = 0;

  /*
  std::uniform_int_distribution è una classe template della libreria standard di C++ che genera numeri interi casuali distribuiti uniformemente.
Il template unsigned long specifica che i numeri generati saranno di tipo unsigned long.
  Questa riga crea un oggetto first_num della classe std::uniform_int_distribution<unsigned long>.
std::uniform_int_distribution<unsigned long>(1, num_pri-1) è il costruttore che definisce la distribuzione uniforme per generare numeri casuali tra 1 e num_pri-1 (inclusi)
  */
  std::uniform_int_distribution<unsigned long> first_num = std::uniform_int_distribution<unsigned long>(1, num_pri-1);
  std::uniform_int_distribution<unsigned long> second_num = std::uniform_int_distribution<unsigned long>(0, num_pri-1);

  static const Hashable<Data> hash;
  ulong gradezza_tab = 251;

  // Default constructor
  HashTable() { one_p = first_num(num_gen); two_p= second_num(num_gen); }

  //copy constructor
  HashTable(const HashTable& tabhash) 
  {
    size = tabhash.size;
    one_p = tabhash.one_p;
    two_p= tabhash.two_p;
    gradezza_tab = tabhash.gradezza_tab;
  }

  //move constructor
  HashTable(HashTable&& tabhash) 
  {
    std::swap(size, tabhash.size);
    std::swap(one_p, tabhash.one_p);
    std::swap(two_p, tabhash.two_p);
    std::swap(gradezza_tab, tabhash.gradezza_tab);
  }

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable & operator= (const HashTable &) = delete;

  // Move assignment
  HashTable & operator= (HashTable &&) noexcept= delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator== (const HashTable &) const noexcept = delete;
  bool operator!= (const HashTable &) const noexcept = delete;

protected:

  // funtion key k( ulong key) = ((a* key+ b) mod primo) mod tablesize
  virtual ulong HashKey (const ulong on_key) const noexcept { return (((one_p *on_key+ two_p)% num_pri)%gradezza_tab);}

};

}

#include "hashtable.cpp"

#endif


//Vincenzo Capasso N86004259