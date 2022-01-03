#pragma once

#include <string>
#include <vector>

void property_override(std::string prop, std::string value, bool add = true);
void properties_override(std::vector<std::string> props, std::string value, bool add = true);
