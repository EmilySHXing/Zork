#include "Attack.h"

Attack::Attack( ) { };
Attack::~Attack( ) { };
Attack::Attack(xml_node<> *pNode)
{
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"print") == 0)
        {
            this->print.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"condition") == 0)
        {
            this->conditions.push_back(Condition(cNode));
        }
        else if (strcmp(cNode->name(),"action") == 0)
        {
            this->actions.push_back(cNode->value());
        }
    }
};