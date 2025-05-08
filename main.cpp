
#include "pico/stdlib.h"
#include <pico/error.h>
#include <stdio.h>
#include <iostream>

#include "InputHandler.h"

int main() {
    stdio_init_all();

    std::cout << "initializing cli" << std::endl;

    InputHandler input_handler;

    while(1){
      char c = getchar_timeout_us(0);
      if(c != char(PICO_ERROR_TIMEOUT)){
        input_handler.handle(c);  
      }
    }
    return 0;
}
