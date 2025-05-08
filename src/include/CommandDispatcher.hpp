#ifndef INCLUDE_COMMAND_DISPATCHER_HPP
#define INCLUDE_COMMAND_DISPATCHER_HPP


#include "Command.h"
#include <tuple>
#include <string>

template<typename... Commands>
class CommandDispatcher {
  public:
      CommandDispatcher(): commands_{} {}

      template<typename T>
      void dispatch(const std::string& cmd_name, const T& arg) const {
        std::apply([&](const auto&... commands){
        (..., try_execute(commands, cmd_name, arg));}, commands_);
    }
  
  private:
      std::tuple<Commands...> commands_;

      template <typename Cmd, typename Arg>
      static void try_execute(const Cmd& cmd, const std::string& name, const Arg& arg) {
          if (name == Cmd::name) {
              cmd(arg);  // uses operator()
          }
      }

  };

  #endif
