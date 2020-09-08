#include "Condition.h"

Condition::Condition( ) { };
Condition::~Condition( ) { };
Condition::Condition(xml_node<>* pNode) {
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"object") == 0)
        {
            this->object.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"status") == 0)
        {
            this->status.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"has") == 0)
        {
            this->has.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"owner") == 0)
        {
            this->owner.assign(cNode->value());
        }
    }
};