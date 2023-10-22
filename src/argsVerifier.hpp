#ifndef _ARGSVERIFIER_HPP
#define _ARGSVERIFIER_HPP

#include <cstring>
#include <string>
#include <iostream>

class ArgsVerifier{
  public:
    ArgsVerifier();
    ~ArgsVerifier();
    bool verify_arguments_delivery(int argc, char const *argv[]);
    bool verify_arguments_node(std::string args, std::string* strings,
                                std::string* u, std::string* b, std::string* p);
};
#endif // ARGSVERIFIER_HPP