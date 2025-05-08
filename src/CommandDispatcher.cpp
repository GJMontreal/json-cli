#include "CommandDispatcher.hpp"
#include "Command.h"

template <typename... Commands>
template <typename Cmd>
void CommandDispatcher<Commands...>::try_execute(const Cmd& cmd, const std::string& name, const CommandArg& arg) {
    using ExpectedType = typename Cmd::ArgType;

    if (name != Cmd::name) {
      return;
    }
    if (auto* actual = std::get_if<ExpectedType>(&arg)) {
      cmd(*actual);  // Safe
  } else {
      std::cerr << "Type mismatch for command '" << name << "'\n";
  }
}
