#include <string>
#include <vector>
#include "Behind.h"

std::vector<std::string> get_command();
bool trigger_cmd(bool &end, std::vector<std::string> command, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature);
bool trigger_cond(bool &end, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature);
void process_command(bool &end, std::vector<std::string> command, Room **current, std::map<std::string, Room> &map_room, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature);
void movement(std::string direction, Room **current, std::map<std::string, Room> &map_room);
void print_inventory(std::vector<std::string> inventory);
void take_item(std::vector<std::string> command, std::vector<std::string> &inventory, Room *current, std::map<std::string, Container> &map_container);
void open_container(std::vector<std::string> command, Room *current, std::map<std::string, Container> &map_container);
void read_item(std::vector<std::string> command, std::vector<std::string> inventory, std::map<std::string, Item> map_item);
void drop_item(std::vector<std::string> command, std::vector<std::string> &inventory, Room *current);
void put_item(std::vector<std::string> command, Room *current, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container);
void turn_on(bool &end, std::string item, Room ** current, std::vector<std::string> &inventory, std::map<std::string, Item> &map_item, std::map<std::string, Container> &map_container, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature);
void attack_creature(bool &end, std::string crt, std::string itm, std::vector<std::string> &inventory, std::map<std::string, Item> &map_item, Room **current, std::map<std::string, Creature> &map_creature, std::map<std::string, Container> &map_container, std::map<std::string, Room> &map_room);
bool check_cond(Condition cond, std::vector<std::string> inventory, std::map<std::string, Room> &map_room, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Creature> &map_creature);
void actions(bool &end, std::string action, Room **current, std::vector<std::string> &inventory, std::map<std::string, Container> &map_container, std::map<std::string, Item> &map_item, std::map<std::string, Room> &map_room, std::map<std::string, Creature> &map_creature);