#ifndef INCLUDE_INPUT_HANDLER_H_
#define INCLUDE_INPUT_HANDLER_H_

#include <atomic>
#include <sstream>

class InputHandler {
  public:
    std::atomic<int>& brace_count() {
          return _brace_count;
        }
  
    void handle(char c);
    private:
      std::atomic<int> _brace_count = 0;
      bool started = false;
      std::stringstream json_stream;

};

#endif
