#include <iostream>
#include "httplib.h"

static const char *host = "0.0.0.0";
static const int port = 3777;

int main() {
    std::cout << "Starting test server..." << std::endl;
    httplib::Server server;
    server.Get("/2018-06-01/runtime/invocation/next", [](const httplib::Request &request, httplib::Response &response) {
        response.set_content(
                "{\"version\": \"2.0\", \"routeKey\": \"GET /cpp/hello\", \"rawPath\": \"/cpp/hello\", \"rawQueryString\": \"\", \"headers\": {\"accept\": \"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\", \"accept-encoding\": \"gzip, deflate, br\", \"accept-language\": \"en\", \"content-length\": \"0\", \"host\": \"bv73zb23ob.execute-api.ap-southeast-2.amazonaws.com\", \"sec-ch-ua\": \"\\\"Chromium\\\";v=\\\"92\\\", \\\" Not A;Brand\\\";v=\\\"99\\\", \\\"Google Chrome\\\";v=\\\"92\\\"\", \"sec-ch-ua-mobile\": \"?0\", \"sec-fetch-dest\": \"document\", \"sec-fetch-mode\": \"navigate\", \"sec-fetch-site\": \"none\", \"sec-fetch-user\": \"?1\", \"upgrade-insecure-requests\": \"1\", \"user-agent\": \"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36\", \"x-amzn-trace-id\": \"Root=1-61282366-17c4021440bd4df61637122b\", \"x-forwarded-for\": \"127.0.0.1\", \"x-forwarded-port\": \"443\", \"x-forwarded-proto\": \"https\"}, \"requestContext\": {\"accountId\": \"204244381428\", \"apiId\": \"bv73zb23ob\", \"domainName\": \"bv73zb23ob.execute-api.ap-southeast-2.amazonaws.com\", \"domainPrefix\": \"bv73zb23ob\", \"http\": {\"method\": \"GET\", \"path\": \"/cpp/hello\", \"protocol\": \"HTTP/1.1\", \"sourceIp\": \"127.0.0.1\", \"userAgent\": \"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36\"}, \"requestId\": \"Esp3_hNOSwMEPNg=\", \"routeKey\": \"GET /cpp/hello\", \"stage\": \"$default\", \"time\": \"26/Aug/2021:23:27:34 +0000\", \"timeEpoch\": 1630020454104}, \"isBase64Encoded\": false}",
                "application/json");
    });
    server.Post("/2018-06-01/runtime/invocation/.*/response",
                [](const httplib::Request &request, httplib::Response &response) {
                    response.set_content("{\"status\":\"OK\"}", "application/json ");
                });

    printf("Listening for Lambda invocations on http://localhost:%d/2018-06-01/runtime/invocation/next\n", port);
    server.listen(host, port);
}
