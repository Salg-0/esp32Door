#ifndef CONF_H
#define CONF_H

#include <string>
#include <unordered_map>

#define only_local true // if true, only local database is used else sql database is used

// [wifi]
#define wifi_ssid "your_ssid"
#define wifi_password "your_password"

// [sql]
#define sql_ip {0, 0, 0, 0}
#define sql_user "sql_user"
#define sql_password "sql_password"
#define sql_database "sql_database"
#define sql_port sql_port

const std::unordered_map<std::string, std::string> local = 
{
{"card_uid",      	 "user_name"     },
};

#endif