#include <iostream>

#include "Automata.h"

int main()
{
  Automata automata{std::cout};
  automata.on();
  automata.logMenu();
  automata.coin(30);
  automata.choice("Tea");
  automata.coin(10);
  automata.choice("Tea");
  return 0;
}