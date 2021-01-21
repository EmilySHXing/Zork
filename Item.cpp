#include "Item.h"

/*
Create item from corresponding xml_node
*/

Item::Item( ) { };
Item::~Item( ) { };
Item::Item(xml_node<> *pNode)
{
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
        else if (strcmp(cNode->name(),"writing") == 0)
        {
            this->writing.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"trigger") == 0)
        {
            this->triggers.push_back(Trigger(cNode));
        }
        else if (strcmp(cNode->name(),"turnon") == 0)
        {
            this->turnon = Turnon(cNode);
        }
    }
};
