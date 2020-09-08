#include "rapidxml.hpp"
using namespace rapidxml;
#include <string>
#include <vector>
#include "Trigger.h"

#ifndef CT
#define CT
class Container{
    public:
    Container( );
    Container(xml_node<> *pNode);
    ~Container( );

    std::string name;
    std::string status;
    std::string description;

    std::vector<std::string> items;
    std::vector<std::string> accepts;
    std::vector<Trigger> triggers;

    bool open;
};
#endif