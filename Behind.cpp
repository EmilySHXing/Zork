#include "Behind.h"
#include <sstream>
#include <vector>
#include <iostream>

/*
Object deletion, addition and updates in the background.
*/

void add_obj(std::string obj, std::string dst, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    // Check if obj is item
    std::map<std::string, Item>::iterator i_item = map_item.find(obj);
    if (i_item != map_item.end())
    {
        // Check if dst is container
        std::map<std::string, Container>::iterator i_container = map_container.find(dst);
        if (i_container != map_container.end())
        {
            map_container[dst].items.push_back(obj);
            return;
        }
        // Add obj in room
        map_room[dst].items.push_back(obj);
        return;
    }
    
    // Check if obj is creature
    std::map<std::string, Creature>::iterator i_creature = map_creature.find(obj);
    if (i_creature != map_creature.end())
    {
        // Add obj in room
        map_room[dst].creatures.push_back(obj);
        return;
    }
    
    // Add obj in room if neither creature nor item
    map_room[dst].containers.push_back(obj);
    return;
}

void delete_obj(std::string obj, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    /*
    Delete object obj from world
    */
    
    // Look for obj in room
    std::map<std::string, Room>::iterator i_room = map_room.find(obj);
    if (i_room != map_room.end())
    {
        for (i_room = map_room.begin(); i_room != map_room.end(); ++i_room)
        {
            if (i_room->second.map_border["east"] == obj) i_room->second.map_border["east"] = "";
            if (i_room->second.map_border["west"] == obj) i_room->second.map_border["west"] = "";
            if (i_room->second.map_border["north"] == obj) i_room->second.map_border["north"] = "";
            if (i_room->second.map_border["south"] == obj) i_room->second.map_border["south"] = "";
        }
        return;
    }

    // Look for obj in container
    std::map<std::string, Container>::iterator i_cont = map_container.find(obj);
    if (i_cont != map_container.end())
    {
        for (i_room = map_room.begin(); i_room != map_room.end(); ++i_room)
        {
            std::vector<std::string>::iterator it = std::find(i_room->second.containers.begin(), i_room->second.containers.end(), obj);
            if (it != i_room->second.containers.end())
            {
                i_room->second.containers.erase(it);
            }
        }
        return;
    }

    // Look for obj in creature
    std::map<std::string, Creature>::iterator i_crt = map_creature.find(obj);
    if (i_crt != map_creature.end())
    {
        for (i_room = map_room.begin(); i_room != map_room.end(); ++i_room)
        {
            std::vector<std::string>::iterator it = std::find(i_room->second.creatures.begin(), i_room->second.creatures.end(), obj);
            if (it != i_room->second.creatures.end())
            {
                i_room->second.creatures.erase(it);
            }
        }
        return;
    }

    // Look for obj in item
    std::map<std::string, Item>::iterator i_item = map_item.find(obj);
    if (i_item != map_item.end())
    {
        for (i_room = map_room.begin(); i_room != map_room.end(); ++i_room)
        {
            std::vector<std::string>::iterator it = std::find(i_room->second.items.begin(), i_room->second.items.end(), obj);
            if (it != i_room->second.items.end())
            {
                i_room->second.items.erase(it);
            }
        }

        for (i_cont = map_container.begin(); i_cont != map_container.end(); ++i_cont)
        {
            std::vector<std::string>::iterator it = std::find(i_cont->second.items.begin(), i_cont->second.items.end(), obj);
            if (it != i_cont->second.items.end())
            {
                i_cont->second.items.erase(it);
            }
        }
    }
}

void update_obj(std::string obj, std::string sta, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    /*
    Update status sta of object obj
    */
    
    // Look for obj in item
    std::map<std::string, Item>::iterator i_item = map_item.find(obj);
    if (i_item != map_item.end())
    {
        map_item[obj].status.assign(sta);
        return;
    }
    
    // Look for obj in container
    std::map<std::string, Container>::iterator i_container = map_container.find(obj);
    if (i_container != map_container.end())
    {
        map_container[obj].status.assign(sta);
        return;
    }
    
    // Look for obj in creature
    std::map<std::string, Creature>::iterator i_creature = map_creature.find(obj);
    if (i_creature != map_creature.end())
    {
        map_creature[obj].status.assign(sta);
        return;
    }
    map_room[obj].status.assign(sta);
}
