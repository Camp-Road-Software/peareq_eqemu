#ifndef EQEMU_PEAREQ_INTERFACE_H
#define EQEMU_PEAREQ_INTERFACE_H

#include <string>
#include "../common/http/httplib.h"

class PearEQInterface {
public:
    static void notify_login(const std::string& username, const std::string& ip_address) {
        httplib::Client cli("https://www.perryb.ca");

        // Create JSON payload
        nlohmann::json payload = {
            {"username", username},
            {"ip_address", ip_address}
        };

        // Send POST request
        auto res = cli.Post("/api/login_event", payload.dump(), "application/json");

        // Log the result but don't block on failure
        if (res) {
            LogDebug("PearEQ login notification sent successfully for user [{}]", username);
        } else {
            LogDebug("PearEQ login notification failed for user [{}]", username);
        }
    }
};

#endif //EQEMU_PEAREQ_INTERFACE_H