#include <iostream>
#include "appcli.hpp"
#include "colors.hpp"

int main() {
  std::cout << "Car Renting Manager:" << std::endl;
  std::string eqs(100, '=');
  std::cout << eqs << std::endl;
  std::string command;
  while(true){
    std::cout << GREEN BOLD ">> " RESET ;
    std::cout.flush();
    std::getline(std::cin, command);
    handle_command(command);
  }
  return 0;
}
