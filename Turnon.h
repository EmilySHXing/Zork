#include <string>
#include "rapidxml.hpp"
using namespace rapidxml;

#ifndef TURNON
#define TURNON
class Turnon{
    public:
    Turnon( );
    Turnon(xml_node<> *node);
    ~Turnon( );

    std::string print;
    std::string action;
};
#endif