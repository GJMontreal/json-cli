#ifndef INCLUDE_COMMAND_HPP
#define INCLUDE_COMMAND_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
template <typename Derived, typename T> class Command {
public:
  using ArgType = T;
  void operator()(const T &t) const {
    static_cast<const Derived &>(*this).execute(t);
  }
};

class HelpCommand : public Command<HelpCommand, nlohmann::json> {
public:
  static constexpr const char *name = "help";
  void execute(const nlohmann::json json) const;
};

class GreetCommand : public Command<GreetCommand, nlohmann::json> {
public:
  static constexpr const char *name = "greet";

  void execute(const nlohmann::json arg) const;
};

class AnotherCommand : public Command<AnotherCommand, nlohmann::json> {
public:
  static constexpr const char *name = "test";

  void execute(const nlohmann::json arg) const { std::cout << "test, " << arg << "!\n"; }
};

#endif
