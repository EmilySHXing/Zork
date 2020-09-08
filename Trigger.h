#include "rapidxml.hpp"
#include <string>
#include <vector>
#include "Condition.h"
using namespace rapidxml;

#ifndef TG
#define TG
class Trigger{
    public:
    Trigger( );
    Trigger(xml_node<> *node);
    ~Trigger( );

    std::string type;
    std::string command;
    std::vector<Condition> conditions;
    std::vector<std::string> actions;
    std::vector<std::string> prints;
};
#endif