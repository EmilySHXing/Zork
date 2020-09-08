#include "rapidxml.hpp"
#include <string>
#include <vector>
using namespace rapidxml;

#ifndef CD
#define CD
class Condition{
    public:
    Condition( );
    ~Condition( );
    Condition(xml_node<> *pNode);

    std::string status;
    std::string has;
    std::string object;
    std::string owner;
};
#endif