
#include "pico/stdlib.h"
#include <pico/error.h>
#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include "InputHandler.h"

int main() {
    stdio_init_all();

    std::cout << "initializing cli" << std::endl;

    InputHandler input_handler;

    while(1){
      char c = getchar_timeout_us(0);
      if(c != char(PICO_ERROR_TIMEOUT)){
        nlohmann::json json;

        if(input_handler.handle(c, json)){ 
          std::cout << json.dump(4) << std::endl;
        }
      }
    }
    return 0;
}
