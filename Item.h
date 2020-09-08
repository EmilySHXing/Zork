#include <string>
#include <vector>
#include "rapidxml.hpp"
using namespace rapidxml;
#include "Turnon.h"
#include "Trigger.h"

#ifndef ITEM
#define ITEM
class Item{
    public:
    Item( );
    Item(xml_node<> *pNode);
    ~Item( );

    std::string name;
    std::string status;
    std::string description;
    std::string writing;

    Turnon turnon;
    std::vector<Trigger> triggers;
};
#endif