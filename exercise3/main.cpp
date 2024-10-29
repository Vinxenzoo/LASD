//Vincenzo Capasso N86004259
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

#include <string>
#include <chrono>
#include <thread>

void PrintCentered(const std::string& message) {
    int width = 100; 
    int padding = (width - message.length()) / 2;
    std::cout << std::string(padding, ' ') << message << std::endl;
}

void DisplayWelcomeMessage() {
    std::string line = "*********************************************************************";
    std::string message = "Benvenuto ai test di lasd 2024";

    PrintCentered(line);
    PrintCentered(message);
    PrintCentered(line);

    // Pause for a short duration for better visualization
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() 
{
    DisplayWelcomeMessage();


     unsigned int sc_test=0;

   do
   {
     std::cout<<"\n               si scelga di eseguire i test: test alunno(1) test professore(2): ";
     std::cin>>sc_test;
     std::cout<<"\n Vincenzo Capasso N86004259"<<std::endl;
    switch(sc_test) 
      {
        case 1: mytest(); break;
        case 2: lasdtest(); break;
           break;
      }
   }
   while (sc_test ==1 || sc_test ==2);

    return 0;
}