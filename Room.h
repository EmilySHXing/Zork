#include <string>
#include <map>
#include "Item.h"
#include <vector>
#include "Container.h"
#include "rapidxml.hpp"
using namespace rapidxml;

#ifndef ROOM
#define ROOM
class Room{
    public:
    Room( );
    Room(xml_node<> *pNode);
    ~Room( );
    
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    
    std::vector<std::string> items;
    std::map<std::string, std::string> map_border;
    std::vector<std::string> containers;
    std::vector<Trigger> triggers;
    std::vector<std::string> creatures;

};
#endif