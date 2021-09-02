#include <cstdlib>
#include <iostream>
#include <string>
#include "./httplib.h"

static const int DOTS = 1;
static const int FULL = 2;

std::string getEnvironmentVariable(const char *name, bool mandatory = false);

int getDebugLevel();

int main() {
    std::string lambdaApi = getEnvironmentVariable("AWS_LAMBDA_RUNTIME_API", true);
    int debugLevel = getDebugLevel();
    int count = 0;
    bool longDots = false;

    httplib::Client cli("http://" + lambdaApi);
    while (true) {
        auto res = cli.Get("/2018-06-01/runtime/invocation/next");
        if (res) {
            if (debugLevel == DOTS) {
                count++;
                std::cout << (count % 3 == 0 ? ">" : "-");
                if (longDots) {
                    if (count % 80 == 0) {
                        std::cout << std::endl;
                        longDots = !longDots;
                    }
                } else {
                    if (count % 40 == 0) {
                        std::cout << std::endl;
                        longDots = !longDots;
                        count += 40;
                    }
                }

            } else if (debugLevel == FULL) {
                std::cout << "Recieved event from " << lambdaApi << std::endl;
                std::cout << "Status: " << res->status << std::endl;
                std::cout << "Body:" << std::endl
                          << res->body << std::endl;
            }

            std::string responseId = res->get_header_value("Lambda-Runtime-Aws-Request-Id");
            std::string response = "{\"result\": \"If you see this then the mongodb lambda works!\"}";
            cli.Post(("/2018-06-01/runtime/invocation/" + responseId + "/response").c_str(), response,
                     "application/json");
        } else {
            std::cerr << "error: " << res.error() << std::endl;
        }
    }
}

int getDebugLevel() {
    std::string debug = getEnvironmentVariable("DEBUG");
    int debugLevel = 0;
    if (debug == "DOTS") {
        debugLevel = DOTS;
    } else if (debug == "FULL") {
        debugLevel = FULL;
    }
    return debugLevel;
}

std::string getEnvironmentVariable(const char *name, bool mandatory) {
    std::string result;
    const char *rawValue = getenv(name);
    if (rawValue) {
        std::cout << name << ":" << rawValue << std::endl;
        result = std::string(rawValue);
    } else {
        mandatory ? std::cerr : std::cout << "Could not find environment variable '" << name << "'" << std::endl;
        if (mandatory) {
            abort();
        }
    }
    return result;
}
