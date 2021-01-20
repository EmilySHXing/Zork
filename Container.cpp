#include "Container.h"

/*
Create container with corresponding xml node
*/

Container::Container( ) { };

Container::Container(xml_node<> *pNode)
{
    open = false;
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"name") == 0)
        {
            this->name.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"status") == 0)
        {
            this->status.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"description") == 0)
        {
            this->description.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"item") == 0)
        {
            this->items.push_back(cNode->value());
        }
        else if (strcmp(cNode->name(),"trigger") == 0)
        {
            this->triggers.push_back(Trigger(cNode));
        }
        else if (strcmp(cNode->name(),"accept") == 0)
        {
            this->accepts.push_back(cNode->value());
        }
    }
};

Container::~Container( ) { };
