#include "Command.h"

#include <iostream>

void HelpCommand::execute(const nlohmann::json json) const  {
    std::cout << "Help" << std::endl ;
}

void GreetCommand::execute(const nlohmann::json arg) const {
  std::cout << "Hello, " << arg << "!\n";
}
