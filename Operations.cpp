#include "Operations.h"
#include <iostream>
#include <sstream>

std::vector<std::string> get_command()
{
    std::string command;
    std::vector<std::string> vec;
    std::cout << "Enter command: ";
    std::getline(std::cin, command);

    std::istringstream comm(command);
    while (comm)
    {
        std::string tmp;
        comm >> tmp;
        vec.push_back(tmp);
    }

    return vec;
}

bool trigger_cmd(bool &end, std::vector<std::string> command, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature)
{
    command.pop_back();
    std::string comm = "";
    std::vector<std::string>::iterator j;
    bool trig = false;
    for (j = command.begin(); j != command.end(); ++j)
    {
        comm += (*j);
        if ((*j) != command.back()) comm += " ";
    }

    for (std::vector<Trigger>::iterator i = (*current)->triggers.begin(); i != (*current)->triggers.end(); ++i)
    {
        if ((*i).type == "used") continue;
        if (comm != (*i).command) continue;
        
        std::vector<Condition>::iterator k;
        for (k = (*i).conditions.begin(); k != (*i).conditions.end(); ++k)
        {
            bool check = check_cond((*k), inventory, map_room, map_container, map_item, map_creature);
            if (!check) break;
        }
        if (k == (*i).conditions.end())
        {
            trig = true;
            for (j = (*i).prints.begin(); j != (*i).prints.end(); ++j)
            {
                std::cout << (*j) << std::endl;
            }
            for (std::vector<std::string>::iterator l = (*i).actions.begin(); l != (*i).actions.end(); ++l)
            {
                actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
            }
            
            if ((*i).type == "single") (*i).type = "used";
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->containers.begin(); i != (*current)->containers.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_container[(*i)].triggers.begin(); m != map_container[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if (comm != (*m).command) continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }
                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }
                
                if ((*m).type == "single") (*m).type = "used";
            }
            
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->creatures.begin(); i != (*current)->creatures.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_creature[(*i)].triggers.begin(); m != map_creature[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if ((*m).command != comm) continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }
                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }

                if ((*m).type == "single") (*m).type = "used";
            }
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->items.begin(); i != (*current)->items.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_item[(*i)].triggers.begin(); m != map_item[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if ((*m).command != comm) continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }

                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }

                if ((*m).type == "single") (*m).type = "used";
            }
        }
    }
    return trig;
}

bool trigger_cond(bool &end, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature)
{
    bool trig = false;
    for (std::vector<Trigger>::iterator i = (*current)->triggers.begin(); i != (*current)->triggers.end(); ++i)
    {
        if ((*i).type == "used") continue;
        if ((*i).command != "") continue;
        
        std::vector<Condition>::iterator k;
        for (k = (*i).conditions.begin(); k != (*i).conditions.end(); ++k)
        {
            bool check = check_cond((*k), inventory, map_room, map_container, map_item, map_creature);
            if (!check) break;
        }
        if (k == (*i).conditions.end())
        {
            trig = true;
            
            for (std::vector<std::string>::iterator j = (*i).prints.begin(); j != (*i).prints.end(); ++j)
            {
                std::cout << (*j) << std::endl;
            }

            for (std::vector<std::string>::iterator l = (*i).actions.begin(); l != (*i).actions.end(); ++l)
            {
                actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
            }

            if ((*i).type == "single") (*i).type = "used";
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->containers.begin(); i != (*current)->containers.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_container[(*i)].triggers.begin(); m != map_container[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if ((*m).command != "") continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }

                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }
                if ((*m).type == "single") (*m).type = "used";
            }
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->creatures.begin(); i != (*current)->creatures.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_creature[(*i)].triggers.begin(); m != map_creature[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if ((*m).command != "") continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }

                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }

                if ((*m).type == "single") (*m).type = "used";
            }
        }
    }

    for (std::vector<std::string>::iterator i = (*current)->items.begin(); i != (*current)->items.end(); ++i)
    {
        for (std::vector<Trigger>::iterator m = map_item[(*i)].triggers.begin(); m != map_item[(*i)].triggers.end(); ++m)
        {
            if ((*m).type == "used") continue;
            if ((*m).command != "") continue;

            std::vector<Condition>::iterator n;
            for (n = (*m).conditions.begin(); n != (*m).conditions.end(); ++n)
            {
                bool check = check_cond((*n), inventory, map_room, map_container, map_item, map_creature);
                if (!check) break;
            }
            if (n == (*m).conditions.end())
            {
                trig = true;
                
                for (std::vector<std::string>::iterator l = (*m).prints.begin(); l != (*m).prints.end(); ++l)
                {
                    std::cout << (*l) << std::endl;
                }

                for (std::vector<std::string>::iterator l = (*m).actions.begin(); l != (*m).actions.end(); ++l)
                {
                    actions(end, (*l), current, inventory, map_container, map_item, map_room, map_creature);
                }

                if ((*m).type == "single") (*m).type = "used";
            }
        }
    }
    
    return trig;
}

void process_command(bool &end, std::vector<std::string> command, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature)
{
    if (command.size() <= 1)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    if (command.front() == "n" || command.front() == "s" || command.front() == "w" || command.front() == "e")
    {
        if (command.size() != 2)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        movement(command.front(), current, map_room);
        return;
    }

    if (command.front() == "i")
    {
        if (command.size() != 2)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        print_inventory(inventory);
        return;
    }

    if (command.front() == "take")
    {
        if (command.size() != 3)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        take_item(command, inventory, *current, map_container);
        return;
    }

    if (command.front() == "open")
    {
        if (command.size() != 3)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        std::vector<std::string>::iterator i = command.begin();
        i++;
        std::string cont = (*i);
        if (cont == "exit" && (*current)->type == "exit") 
        {
            std::cout << "Game Over" << std::endl;
            end = false;
            return;
        }
        open_container(command, *current, map_container);
        return;
    }

    if (command.front() == "read")
    {
        if (command.size() != 3)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        read_item(command, inventory, map_item);
        return;
    }

    if (command.front() == "drop")
    {
        if (command.size() != 3)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        drop_item(command, inventory, *current);
        return;
    }

    if (command.front() == "put")
    {
        if (command.size() != 5)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        put_item(command, *current, inventory, map_container);
        return;
    }

    if (command.front() == "turn")
    {
        if (command.size() != 4)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        std::vector<std::string>::iterator i = command.begin();
        i++;
        std::string tmp = (*i);
        if (tmp != "on")
        {
            std::cout << "Error" << std::endl;
            return;
        }
        i++;
        tmp = (*i);
        turn_on(end, tmp, current, inventory, map_item, map_container, map_room, map_creature);
        return;
    }

    if (command.front() == "attack")
    {
        if (command.size() != 5)
        {
            std::cout << "Error" << std::endl;
            return;
        }
        std::vector<std::string>::iterator i = command.begin();
        i++;
        i++;
        std::string tmp = (*i);
        if (tmp != "with")
        {
            std::cout << "Error" << std::endl;
            return;
        }
        i--;
        std::string crt = (*i);
        i++;
        i++;
        std::string itm = (*i);
        attack_creature(end, crt, itm, inventory, map_item, current, map_creature, map_container, map_room);
        return;
    }

    std::cout << "Error" << std::endl;
    return;
}

void movement(std::string direction, Room **current, std::map<std::string, Room> &map_room)
{
    std::string dir;
    if (direction == "n")  dir.assign("north");
    else if (direction == "w")  dir.assign("west");
    else if (direction == "s")  dir.assign("south");
    else dir.assign("east");

    if ((*current)->map_border[dir] == "")
    {
        std::cout << "Can’t go that way." << std::endl;
        return;
    }

    std::string next;
    next.assign((*current)->map_border[dir]);
    (*current) = &map_room[next];
    std::cout << (*current)->description << std::endl;
}

void print_inventory(std::vector<std::string> inventory)
{
    if (inventory.size() == 0)
    {
        std::cout << "Inventory: empty" << std::endl;
        return;
    }
    std::cout << "Inventory: " << inventory.front();

    std::vector<std::string>::iterator i;
    bool check = false;
    for (i = inventory.begin(); i != inventory.end(); i++)
    {
        if (check) std::cout << ", " << (*i);
        check = true;
    }
    std::cout << std::endl;
}

void take_item(std::vector<std::string> command, std::vector<std::string> &inventory, Room *current, std::map<std::string, Container> &map_container)
{
    std::vector<std::string>::iterator i = command.begin();
    i++;
    std::string item = (*i);
    
    std::vector<std::string>::iterator pos = std::find((*current).items.begin(), (*current).items.end(), item);
    if (pos != (*current).items.end())
    {
        (*current).items.erase(pos);
        inventory.push_back(item);
        std::cout << "Item " << item << " added to inventory." << std::endl;
        return;
    }

    std::vector<std::string>::iterator j;
    for (j = (*current).containers.begin(); j != (*current).containers.end(); ++j)
    {
        if (!map_container[(*j)].open) continue;
        pos = std::find(map_container[(*j)].items.begin(), map_container[(*j)].items.end(), item);
        if (pos != map_container[(*j)].items.end())
        {
            map_container[(*j)].items.erase(pos);
            inventory.push_back(item);
            std::cout << "Item " << item << " added to inventory" << std::endl;
            return;
        }
    }

    std::cout << "Error" << std::endl;
}

void open_container(std::vector<std::string> command, Room *current, std::map<std::string, Container> &map_container)
{
    std::vector<std::string>::iterator i = command.begin();
    i++;
    std::string cont = (*i);

    i = std::find((*current).containers.begin(), (*current).containers.end(), cont);
    if (i == (*current).containers.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }

    std::map<std::string, Container>::iterator j = map_container.find(cont);
    if (j == map_container.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }

    map_container[cont].open = true;

    if (map_container[cont].items.size() == 0)
    {
        std::cout << map_container[cont].name << " is empty." << std::endl;
        return;
    }

    std::cout << map_container[cont].name << " contains " << map_container[cont].items.front();
    bool check = false;
    for(i = map_container[cont].items.begin(); i != map_container[cont].items.end(); ++i)
    {
        if (check) std::cout << ", " << (*i);
        check = true;
    }
    std::cout << "." << std::endl;
}

void read_item(std::vector<std::string> command, std::vector<std::string> inventory, std::map<std::string, Item> map_item)
{
    std::vector<std::string>::iterator i = command.begin();
    i++;
    std::string item = (*i);
    std::vector<std::string>::iterator pos = std::find(inventory.begin(), inventory.end(), item);
    if (pos != inventory.end())
    {
        Item tmp = map_item[item];
        if (tmp.writing == "")
        {
            std::cout << "Nothing written." << std::endl;
        }
        else
        {
            std::cout << tmp.writing << std::endl;
        }
        return;
    }
    std::cout << "Error" << std::endl;
}

void drop_item(std::vector<std::string> command, std::vector<std::string> &inventory, Room *current)
{
    std::vector<std::string>::iterator i = command.begin();
    i++;
    std::string item = (*i);
    std::vector<std::string>::iterator pos = std::find(inventory.begin(), inventory.end(), item);
    if (pos != inventory.end())
    {
        std::cout << item << " dropped." << std::endl;
        inventory.erase(pos);
        (*current).items.push_back(item);
        return;
    }
    std::cout << "Error" << std::endl;
}

void put_item(std::vector<std::string> command, Room *current, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container)
{
    std::vector<std::string>::iterator i = command.begin();
    i++;
    i++;
    std::string tmp = (*i);
    if (tmp != "in")
    {
        std::cout << "Error" << std::endl;
        return;
    }
    i--;
    std::string item = (*i);
    std::vector<std::string>::iterator pos_i = std::find(inventory.begin(), inventory.end(), item);
    if (pos_i == inventory.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    i++;
    i++;
    std::string cont = (*i);
    std::vector<std::string>::iterator pos_c = std::find((*current).containers.begin(), (*current).containers.end(), cont);
    if (pos_c == (*current).containers.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    if (map_container[cont].accepts.empty())
    {
        std::cout << "Item " << item << " added to " << cont << "." << std::endl;
        inventory.erase(pos_i);
        map_container[cont].items.push_back(item);
        return;
    }
    pos_c = std::find(map_container[cont].accepts.begin(), map_container[cont].accepts.end(), item);
    if (pos_c == map_container[cont].accepts.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    std::cout << item << " added to " << cont << "." << std::endl;
    inventory.erase(pos_i);
    map_container[cont].items.push_back(item);
}

void turn_on(bool &end, std::string item, Room ** current, std::vector<std::string> &inventory, std::map<std::string, Item> &map_item, std::map<std::string, Container> &map_container, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    std::vector<std::string>::iterator pos = std::find(inventory.begin(), inventory.end(), item);
    if (pos == inventory.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    if (map_item[item].turnon.action == "" && map_item[item].turnon.print == "")
    {
        std::cout << "Error" << std::endl;
        return;
    }

    std::cout << "You activate the " << item << "." << std::endl;
    std::cout << map_item[item].turnon.print << std::endl;
    actions(end, map_item[item].turnon.action, current, inventory, map_container, map_item, map_room, map_creature);
}

void attack_creature(bool &end, std::string crt, std::string itm, std::vector<std::string> &inventory, std::map<std::string, Item> &map_item, Room **current, std::map<std::string, Creature> &map_creature, std::map<std::string, Container> &map_container, std::map<std::string, Room> &map_room)
{
    std::vector<std::string>::iterator i = std::find((*current)->creatures.begin(), (*current)->creatures.end(), crt);
    if (i == (*current)->creatures.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    std::vector<std::string>::iterator j = std::find(inventory.begin(), inventory.end(), itm);
    if (j == inventory.end())
    {
        std::cout << "Error" << std::endl;
        return;
    }
    std::vector<Condition> conds = map_creature[crt].attack.conditions;
    bool check = false;
    if (conds.empty()) check = true;
    for (std::vector<Condition>::iterator k = conds.begin(); k != conds.end(); ++k)
    {
        check = check_cond((*k), inventory, map_room, map_container, map_item, map_creature);
        if (check) break;
    }
    if (!check)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    check = false;
    std::vector<std::string> vuls = map_creature[crt].vulnerabilities;
    for (i = vuls.begin(); i != vuls.end(); ++i)
    {
        check = ((*i) == itm);
        if (check) break;
    }
    if (!check)
    {
        std::cout << "Error" << std::endl;
        return;
    }

    std::cout << "You assault the " << crt << " with the " << itm << "." << std::endl;
    if (map_creature[crt].attack.print != "") std::cout << map_creature[crt].attack.print << std::endl;
    for (std::vector<std::string>::iterator it = map_creature[crt].attack.actions.begin(); it != map_creature[crt].attack.actions.end(); ++it)
    {
        actions(end, *it, current, inventory, map_container, map_item, map_room, map_creature);
    }

}

bool check_cond(Condition cond, std::vector<std::string> inventory, std::map<std::string, Room> &map_room, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature)
{
    if (cond.owner == "")
    {
        std::map<std::string, Room>::iterator i_room = map_room.find(cond.object);
        if (i_room != map_room.end())
        {
            if (map_room[cond.object].status == cond.status) return true;
            return false;
        }
        std::map<std::string, Container>::iterator i_container = map_container.find(cond.object);
        if (i_container != map_container.end())
        {
            if (map_container[cond.object].status == cond.status) return true;
            return false;
        }
        std::map<std::string, Creature>::iterator i_creature = map_creature.find(cond.object);
        if (i_creature != map_creature.end())
        {
            if (map_creature[cond.object].status == cond.status) return true;
            return false;
        }
        std::map<std::string, Item>::iterator i_item = map_item.find(cond.object);
        if (i_item != map_item.end())
        {
            if (map_item[cond.object].status == cond.status) return true;
            return false;
        }
        return false;
    }
    else
    {
        if (cond.owner == "inventory")
        {
            std::vector<std::string>::iterator i = std::find(inventory.begin(), inventory.end(), cond.object);
            if (cond.has == "yes")
            {
                if (i == inventory.end()) return false;
                return true;
            }
            else
            {
                if (i == inventory.end()) return true;
                return false;
            }
        }
        std::map<std::string, Room>::iterator i_room = map_room.find(cond.owner);
        if (i_room != map_room.end())
        {
            Room tmp = map_room[cond.owner];
            std::vector<std::string>::iterator i_cont = std::find(tmp.containers.begin(), tmp.containers.end(), cond.object);
            std::vector<std::string>::iterator i_itms = std::find(tmp.items.begin(), tmp.items.end(), cond.object);
            std::vector<std::string>::iterator i_crt = std::find(tmp.creatures.begin(), tmp.creatures.end(), cond.object);
            if (i_cont == tmp.containers.end() && i_itms == tmp.items.end() && i_crt == tmp.creatures.end())
            {
                if (cond.has == "yes") return false;
                else return true;
            }
            if (cond.has == "yes") return true;
            else return false;
        }
        std::map<std::string, Container>::iterator i_container = map_container.find(cond.owner);
        if (i_container != map_container.end())
        {
            Container tmp2 = map_container[cond.owner];
            std::vector<std::string>::iterator i_itms = std::find(tmp2.items.begin(), tmp2.items.end(), cond.object);
            if (i_itms == tmp2.items.end())
            {
                if (cond.has == "yes") return false;
                else return true;
            }
            if (cond.has == "no") return false;
            else return true;
        }
    }
    
    return false;
}

void actions(bool &end, std::string action, Room ** current, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature)
{
    if (action == "Game Over")
    {
        std::cout << "Victory!" << std::endl;
        end = false;
        return;
    }

    std::istringstream iss(action);
    std::vector<std::string> act_vec;
    std::string tmp;
    while (iss)
    {
        iss >> tmp;
        act_vec.push_back(tmp);
    }

    if (act_vec.front() == "Add")
    {
        std::vector<std::string>::iterator i = act_vec.begin();
        i++;
        std::string obj = (*i);
        i++;
        i++;
        std::string dst = (*i);
        add_obj(obj, dst, map_container, map_item, map_room, map_creature);
        return;
    }

    if (act_vec.front() == "Delete")
    {
        std::vector<std::string>::iterator i = act_vec.begin();
        i++;
        std::string obj = (*i);
        delete_obj(obj, map_container, map_item, map_room, map_creature);
        return;
    }

    if (act_vec.front() == "Update")
    {
        std::vector<std::string>::iterator i = act_vec.begin();
        i++;
        std::string obj = (*i);
        i++;
        i++;
        std::string sta = (*i);
        update_obj(obj, sta, map_container, map_item, map_room, map_creature);
        return;
    }

    process_command(end, act_vec, current, map_room, inventory, map_container, map_item, map_creature);
    return;
}