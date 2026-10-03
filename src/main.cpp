#include <iostream>

#include "nat_engine.hpp"
#include "packet.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << "       VIRTUAL NAT GATEWAY\n";
    std::cout << "========================================\n\n";

    NatEngine nat(
        "203.0.113.5",
        40001
    );

    // ------------------------------------------------
    // 1. Internal client sends request
    // ------------------------------------------------

    Packet request(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "Hello Server"
    );

    std::cout << "Outgoing Packet\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << request.getSourceIp()
              << ":"
              << request.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << request.getDestinationIp()
              << ":"
              << request.getDestinationPort()
              << "\n";

    // NAT translation
    Packet translatedRequest =
        nat.translateOutgoing(request);

    std::cout << "\nAfter Outgoing NAT\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << translatedRequest.getSourceIp()
              << ":"
              << translatedRequest.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << translatedRequest.getDestinationIp()
              << ":"
              << translatedRequest.getDestinationPort()
              << "\n";

    // ------------------------------------------------
    // 2. External server sends response
    // ------------------------------------------------

    Packet response(
        "10.0.0.20",
        8080,
        "203.0.113.5",
        40001,
        Protocol::TCP,
        "Hello Client"
    );

    std::cout << "\nIncoming Response\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << response.getSourceIp()
              << ":"
              << response.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << response.getDestinationIp()
              << ":"
              << response.getDestinationPort()
              << "\n";

    // Reverse NAT translation
    Packet translatedResponse =
        nat.translateIncoming(response);

    std::cout << "\nAfter Reverse NAT\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << translatedResponse.getSourceIp()
              << ":"
              << translatedResponse.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << translatedResponse.getDestinationIp()
              << ":"
              << translatedResponse.getDestinationPort()
              << "\n";

    return 0;
}
