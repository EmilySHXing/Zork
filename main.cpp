#include "rapidxml.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Creature.h"
#include "Operations.h"
using namespace rapidxml;

int main(int argc, char** argv)
{
    std::cout << "Welcome to ZORK" << std::endl;
    xml_document<> doc;
    std::string input;
    std::string line;

    std::ifstream myfile (argv[1]);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            input += line;
        }
        myfile.close();
    }
    std::vector<char> input_xml (input.begin( ), input.end( ));
    input_xml.push_back('\0');

    doc.parse<0>(&input_xml[0]);
    xml_node<> *node = doc.first_node("map");
    
    std::map<std::string, Room> map_room;
    std::map<std::string, Container> map_container;
    std::map<std::string, Item> map_item;
    std::map<std::string, Creature> map_creature;

    for(xml_node<> *pNode = node->first_node(); pNode; pNode=pNode->next_sibling())
    {
        if (strcmp(pNode->name(),"room") == 0)
        {
            Room rm = Room(pNode);
            map_room.insert(std::make_pair(rm.name, rm));
        }

        else if (strcmp(pNode->name(),"container") == 0)
        {
            Container ct = Container(pNode);
            map_container.insert(std::make_pair(ct.name, ct));
        }
        else if (strcmp(pNode->name(),"item") == 0)
        {
            Item item = Item(pNode);
            map_item.insert(std::make_pair(item.name, item));
        }
        else if (strcmp(pNode->name(),"creature") == 0)
        {
            Creature cr = Creature(pNode);
            map_creature.insert(std::make_pair(cr.name, cr));
        }
    }

    Room *current = &map_room["Entrance"];
    std::cout << current->description << std::endl;
    
    std::vector<std::string> inventory;
    std::vector<std::string> command;
    int i = 1;
    bool end = true;

    while (end)
    {
        command = get_command();
        bool trg = trigger_cmd(end, command, &current, map_room, inventory, map_container, map_item, map_creature);
        if (!end) break;
        if (!trg) process_command(end, command, &current, map_room, inventory, map_container, map_item, map_creature);
        if (!end) break;
        do
        {
            trg = trigger_cond(end, &current, map_room, inventory, map_container, map_item, map_creature);
        } while (trg && end);
        
        
    }
    return EXIT_SUCCESS;
}
