#include "Command.h"

#include <iostream>

void HelpCommand::execute(const nlohmann::json json) const  {
    std::cout << "Help" << std::endl ;
}
