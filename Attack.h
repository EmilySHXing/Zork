#include <string>
#include <vector> 
#include "rapidxml.hpp"
#include "Condition.h"
using namespace rapidxml;

#ifndef ATTACK
#define ATTACK
class Attack{
    public:
    Attack( );
    ~Attack( );
    Attack(xml_node<> *pNode);

    std::vector<std::string> actions;
    std::vector<Condition> conditions;
    std::string print;
};
#endif