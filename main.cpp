
#include "pico/stdlib.h"
#include <pico/error.h>
#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include "InputHandler.h"
#include "CommandDispatcher.hpp"

int main() {
    stdio_init_all();

    std::cout << "initializing cli" << std::endl;

    CommandDispatcher<GreetCommand,HelpCommand> dispatcher;
    nlohmann::json empty;
    dispatcher.dispatch("help",empty);
    InputHandler input_handler;

    while(1){
      char c = getchar_timeout_us(0);
      if(c != char(PICO_ERROR_TIMEOUT)){
        nlohmann::json json;

        if(input_handler.handle(c, json)){ 
          std::cout << json.dump(4) << std::endl;
          std::string top_command = json.begin().key();
          dispatcher.dispatch(top_command,json);
        }
      }
    }
    return 0;
}
