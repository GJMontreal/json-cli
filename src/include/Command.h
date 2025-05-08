#ifndef INCLUDE_COMMAND_HPP
#define INCLUDE_COMMAND_HPP


#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
template<typename Derived, typename T>
class Command{
  public:
    void operator()(const T& t) const{
      static_cast<const Derived&>(*this).execute(t);
    }
};

class HelpCommand : public Command<HelpCommand, nlohmann::json> {
  public:
    static constexpr const char* name = "help";
    void execute(const nlohmann::json json) const;
  };

  class GreetCommand : public Command<GreetCommand, std::string> {
    public:
        static constexpr const char* name = "greet";
    
        void execute(const std::string& arg) const {
            std::cout << "Hello, " << arg << "!\n";
        }
    };

#endif
