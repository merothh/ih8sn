#pragma once

#include <map>

typedef std::map<std::string, std::string> config_t;

config_t load_config(void);
void set_prop_from_config(config_t config, std::string key, std::string prop);
void set_props_from_config(config_t config, std::string key, std::vector<std::string> props);
