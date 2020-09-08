#include "Room.h"
#include <iostream>

Room::Room( ) { };
Room::~Room( ) { };

Room::Room(xml_node<> *pNode)
{
    this->type.assign("regular");
    for(xml_node<> *cNode = pNode->first_node(); cNode; cNode=cNode->next_sibling())
    {
        if (strcmp(cNode->name(),"description") == 0)
        {
            this->description.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"name") == 0)
        {
            this->name.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"item") == 0)
        {
            this->items.push_back(cNode->value());
        }
        else if (strcmp(cNode->name(),"status") == 0)
        {
            this->status.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"type") == 0)
        {
            this->type.assign(cNode->value());
        }
        else if (strcmp(cNode->name(),"border") == 0)
        {
            xml_node<> *temp = cNode->first_node();
            if (strcmp(temp->name(), "direction") == 0)
            {
                this->map_border.insert(std::make_pair(temp->value(), temp->next_sibling()->value()));
            }
            else
            {
                this->map_border.insert(std::make_pair(temp->next_sibling()->value(), temp->value()));
            }
        }
        else if (strcmp(cNode->name(),"container") == 0)
        {
            this->containers.push_back(cNode->value());
        }
        else if (strcmp(cNode->name(),"trigger") == 0)
        {
            Trigger tmp = Trigger(cNode);
            this->triggers.push_back(tmp);
        }
        else if (strcmp(cNode->name(),"creature") == 0)
        {
            this->creatures.push_back(cNode->value());
        }
    }
};