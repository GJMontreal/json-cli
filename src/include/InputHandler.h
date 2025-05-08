#ifndef INCLUDE_INPUT_HANDLER_H_
#define INCLUDE_INPUT_HANDLER_H_

#include <atomic>
#include <sstream>
#include <nlohmann/json.hpp>

class InputHandler {
  public:
    std::atomic<int>& brace_count() {
          return _brace_count;
        }
  
        bool handle(char c, nlohmann::json &json );

    private:
      std::atomic<int> _brace_count = 0;
      bool started = false;
      std::stringstream json_stream;

};

#endif
