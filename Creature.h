#include <string>
#include <vector>
#include "rapidxml.hpp"
#include "Trigger.h"
#include "Attack.h"
using namespace rapidxml;

#ifndef CREATURE
#define CREATURE
class Creature{
    public:
    Creature( );
    Creature(xml_node<> *node);
    ~Creature( );

    std::string name;
    std::string status;
    std::string description;
    std::vector<std::string> vulnerabilities;
    Attack attack;
    std::vector<Trigger> triggers;
};
#endif