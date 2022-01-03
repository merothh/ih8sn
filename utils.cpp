#include "utils.h"

#define FIND_AND_REMOVE(s, delimiter, variable_name) \
    std::string variable_name = s.substr(0, s.find(delimiter)); \
    s.erase(0, s.find(delimiter) + delimiter.length());

#define APPEND_STRING(s, to_append) \
    s.append(" "); \
    s.append(to_append);

std::string fingerprint_to_description(std::string fingerprint) {
    std::string delimiter = "/";
    std::string delimiter2 = ":";
    std::string build_fingerprint_copy = fingerprint;

    FIND_AND_REMOVE(build_fingerprint_copy, delimiter, brand)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter, product)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter2, device)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter, platform_version)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter, build_id)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter2, build_number)
    FIND_AND_REMOVE(build_fingerprint_copy, delimiter, build_variant)
    std::string build_version_tags = build_fingerprint_copy;

    std::string description = product + "-" + build_variant;
    APPEND_STRING(description, platform_version)
    APPEND_STRING(description, build_id)
    APPEND_STRING(description, build_number)
    APPEND_STRING(description, build_version_tags)

    return description;
}
