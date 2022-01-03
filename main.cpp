#include "config.h"
#include "properties.h"
#include "utils.h"
#include <string>
#include <vector>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

static const std::vector<std::string> BUILD_FINGERPRINT_PROPS = {
    "ro.bootimage.build.fingerprint",
    "ro.build.fingerprint",
    "ro.odm.build.fingerprint",
    "ro.product.build.fingerprint",
    "ro.system.build.fingerprint",
    "ro.system_ext.build.fingerprint",
    "ro.vendor.build.fingerprint",
};

static const std::vector<std::string> BUILD_VERSION_RELEASE_PROPS = {
    "ro.build.version.release",
    "ro.odm.build.version.release",
    "ro.product.build.version.release",
    "ro.system.build.version.release",
    "ro.system_ext.build.version.release",
    "ro.vendor.build.version.release",
    "ro.build.version.release_or_codename",
    "ro.odm.build.version.release_or_codename",
    "ro.product.build.version.release_or_codename",
    "ro.system.build.version.release_or_codename",
    "ro.system_ext.build.version.release_or_codename",
    "ro.vendor.build.version.release_or_codename",
};

static const std::vector<std::string> PRODUCT_NAME_PROPS = {
    "ro.product.name",
    "ro.product.odm.name",
    "ro.product.product.name",
    "ro.product.system.name",
    "ro.product.system_ext.name",
    "ro.product.vendor.name",
};

static const std::vector<std::string> BUILD_TAGS_PROPS = {
    "ro.build.tags",
    "ro.odm.build.tags",
    "ro.product.build.tags",
    "ro.system.build.tags",
    "ro.system_ext.build.tags",
    "ro.vendor.build.tags",
};

static const std::vector<std::string> BUILD_TYPE_PROPS = {
    "ro.build.type",
    "ro.odm.build.type",
    "ro.product.build.type",
    "ro.system.build.type",
    "ro.system_ext.build.type",
    "ro.vendor.build.type",
};

int main(int argc, char *argv[]) {
    if (__system_properties_init()) {
        return -1;
    }

    if (argc != 2) {
        return -1;
    }

    const auto is_init_stage = strcmp(argv[1], "init") == 0;
    const auto is_boot_completed_stage = strcmp(argv[1], "boot_completed") == 0;

    const auto config = load_config();

    if (is_init_stage) {
        const auto build_fingerprint = config.find("BUILD_FINGERPRINT");
        if (build_fingerprint != config.end()) {
            properties_override(BUILD_FINGERPRINT_PROPS, build_fingerprint->second);
            property_override("ro.build.description",
                    fingerprint_to_description(build_fingerprint->second));
        }

        set_props_from_config(config, "BUILD_TAGS", BUILD_TAGS_PROPS);
        set_props_from_config(config, "BUILD_TYPE", BUILD_TYPE_PROPS);
        set_prop_from_config(config, "DEBUGGABLE", "ro.debuggable");
    }

    if (is_boot_completed_stage) {
        set_prop_from_config(config, "BUILD_SECURITY_PATCH_DATE", "ro.build.version.security_patch");
        set_props_from_config(config, "BUILD_VERSION_RELEASE", BUILD_VERSION_RELEASE_PROPS);
    }

    set_props_from_config(config, "PRODUCT_NAME", PRODUCT_NAME_PROPS);

    property_override("ro.boot.flash.locked", "1");
    property_override("ro.boot.vbmeta.device_state", "locked");
    property_override("ro.boot.verifiedbootstate", "green");
    property_override("ro.boot.veritymode", "enforcing");
    property_override("ro.boot.warranty_bit", "0");
    property_override("ro.warranty_bit", "0");

    return 0;
}
