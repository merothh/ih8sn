#include "config.h"
#include "properties.h"
#include <fstream>
#include <vector>

config_t load_config() {
    config_t config;

    if (std::ifstream file("/system/etc/ih8sn.conf"); file.good()) {
        std::string line;

        while (std::getline(file, line)) {
            if (line[0] == '#') {
                continue;
            }

            if (const auto separator = line.find('='); separator != std::string::npos) {
                config[line.substr(0, separator)] = line.substr(separator + 1);
            }
        }
    }

    return config;
}

void set_prop_from_config(config_t config, std::string key, std::string prop) {
    const auto value = config.find(key);
    if (value != config.end()) {
        property_override(prop, value->second);
    }
}

void set_props_from_config(config_t config, std::string key, std::vector<std::string> props) {
    const auto value = config.find(key);
    if (value != config.end()) {
        properties_override(props, value->second);
    }
}
