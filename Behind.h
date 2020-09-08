#include "Room.h"
#include "Creature.h"


void add_obj(std::string obj, std::string dst, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature);
void delete_obj(std::string obj, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature);
void update_obj(std::string obj, std::string sta, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature);