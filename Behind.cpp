#include "Behind.h"
#include <sstream>
#include <vector>
#include <iostream>

void add_obj(std::string obj, std::string dst, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    std::map<std::string, Item>::iterator i_item = map_item.find(obj);
    if (i_item != map_item.end())
    {
        std::map<std::string, Container>::iterator i_container = map_container.find(dst);
        if (i_container != map_container.end())
        {
            map_container[dst].items.push_back(obj);
            return;
        }
        map_room[dst].items.push_back(obj);
        return;
    }
    std::map<std::string, Creature>::iterator i_creature = map_creature.find(obj);
    if (i_creature != map_creature.end())
    {
        map_room[dst].creatures.push_back(obj);
        return;
    }
    map_room[dst].containers.push_back(obj);
    return;
}

void delete_obj(std::string obj, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
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
    std::map<std::string, Item>::iterator i_item = map_item.find(obj);
    if (i_item != map_item.end())
    {
        map_item[obj].status.assign(sta);
        return;
    }
    std::map<std::string, Container>::iterator i_container = map_container.find(obj);
    if (i_container != map_container.end())
    {
        map_container[obj].status.assign(sta);
        return;
    }
    std::map<std::string, Creature>::iterator i_creature = map_creature.find(obj);
    if (i_creature != map_creature.end())
    {
        map_creature[obj].status.assign(sta);
        return;
    }
    map_room[obj].status.assign(sta);
}