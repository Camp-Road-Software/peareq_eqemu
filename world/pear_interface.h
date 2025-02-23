#ifndef EQEMU_PEAR_INTERFACE_H
#define EQEMU_PEAR_INTERFACE_H

#include "../common/json/json.h"
#include "../common/http/curl.h"
#include <string>

class PearInterface {
public:
    static void SendZoneChange(const std::string& character_name, int from_zone_id, int to_zone_id, int level);
    static void Initialize(const std::string& api_key, const std::string& base_url);

private:
    static std::string s_api_key;
    static std::string s_base_url;
    static bool SendRequest(const std::string& endpoint, const Json::Value& payload);
};

#endif //EQEMU_PEAR_INTERFACE_H