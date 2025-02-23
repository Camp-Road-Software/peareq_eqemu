#include "pear_interface.h"
#include "../common/eqemu_logsys.h"

std::string PearInterface::s_api_key;
std::string PearInterface::s_base_url;

void PearInterface::Initialize(const std::string& api_key, const std::string& base_url) {
    s_api_key = api_key;
    s_base_url = base_url;
}

void PearInterface::SendZoneChange(const std::string& character_name, int from_zone_id, int to_zone_id, int level) {
    if (s_api_key.empty() || s_base_url.empty()) {
        return;
    }

    Json::Value payload;
    payload["character_name"] = character_name;
    payload["from_zone_id"] = from_zone_id;
    payload["to_zone_id"] = to_zone_id;
    payload["level"] = level;

    SendRequest("/api/v1/zone_change", payload);
}

bool PearInterface::SendRequest(const std::string& endpoint, const Json::Value& payload) {
    std::stringstream post_data;
    post_data << payload;

    std::string url = s_base_url + endpoint;

    auto curl = std::make_unique<Curl>();
    curl->SetUrl(url);
    curl->SetPostData(post_data.str());
    curl->AddHeader("Content-Type: application/json");
    curl->AddHeader("X-API-Key: " + s_api_key);

    bool success = curl->Perform();
    if (!success) {
        LogError("Failed to send request to Pear API endpoint [{}]", endpoint);
        return false;
    }

    return true;
}