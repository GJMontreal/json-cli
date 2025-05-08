#ifndef INCLUDE_COMMAND_HPP
#define INCLUDE_COMMAND_HPP

#include <any>
#include <string>
#include <iostream>

template<typename T>
class Command{
  public:
    virtual ~Command() = default;
    virtual std::string name() const = 0;
    virtual void execute(std::any arg) const = 0;
};

class HelpCommand : public Command {
  public:
      std::string name() const override { return "help"; }
      void execute(std::any arg) const override;
  };
#endif
