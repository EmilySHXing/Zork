#include "Trigger.h"

Trigger::Trigger( ) { };
Trigger::~Trigger( ) { };
Trigger::Trigger(xml_node<> *pNode)
{
    this->type.assign("single");
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"type") == 0)
        {
            this->type.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"command") == 0)
        {
            this->command.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"condition") == 0)
        {
            this->conditions.push_back(Condition(cNode));
        }
        else if (strcmp(cNode->name(),"action") == 0)
        {
            this->actions.push_back(cNode->value());
        }
        else if (strcmp(cNode->name(),"print") == 0)
        {
            this->prints.push_back(cNode->value());
        }
    }
};