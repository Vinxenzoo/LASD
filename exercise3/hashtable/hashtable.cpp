//Vincenzo Capasso N86004259

#include "hashtable.hpp"

namespace lasd 
{

#include <string>

/*
template <>
class Hashable<int> 
{
    public:
    ulong operator()(const int & dat_of_h) const noexcept 
    {
        return (dat_of_h *dat_of_h);
    }
};
*/

template <>
class Hashable<int> 
{
    public:
    ulong operator()(const int & dat_of_h) const noexcept 
    {
        ulong on_hashing = 5381;
            on_hashing = ((on_hashing << 5)+ on_hashing) + dat_of_h;
        
        return on_hashing;
    }
};

template <>
class Hashable<double> 
{
    public:
    ulong operator()(const double & dat_of_h) const noexcept 
    {
        long pie_int = floor(dat_of_h);
        long pie_f = pow(2, 24) * (dat_of_h-pie_int);
        return (pie_int* pie_f );
    }
};

template <>
class Hashable<std::string> 
{
    public:
    ulong operator()(const std::string& dat_of_h) const noexcept 
    {
        ulong on_hashing = 0;
        for(char c: dat_of_h) 
        {
            on_hashing = c +(on_hashing << 6) + (on_hashing << 16) - on_hashing;
        }
        return on_hashing;
    }
};


}

//Vincenzo Capasso N86004259
