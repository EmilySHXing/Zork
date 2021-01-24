#include "Turnon.h"

/*
Create turnon object with corresponding xml node
*/

Turnon::Turnon( ) { };
Turnon::~Turnon( ) { };
Turnon::Turnon(xml_node<> *pNode) {
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"print") == 0)
        {
            this->print.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"action") == 0)
        {
            this->action.assign(cNode->value());
        }
    }
};
