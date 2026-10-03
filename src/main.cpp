#include <iostream>

#include "nat_gateway.hpp"
#include "packet.hpp"

void displayPacket(
    const std::string& title,
    const Packet& packet
) {
    std::cout << "\n" << title << "\n";
    std::cout << "----------------------------------------\n";

    std::cout << "Source      : "
              << packet.getSourceIp()
              << ":"
              << packet.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << packet.getDestinationIp()
              << ":"
              << packet.getDestinationPort()
              << "\n";

    std::cout << "Payload     : "
              << packet.getPayload()
              << "\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "       VIRTUAL NAT GATEWAY\n";
    std::cout << "========================================\n";

    NatGateway gateway(
        "203.0.113.5",
        40001
    );

    // Configure port forwarding
    gateway.addPortForwardRule(
        8080,
        "192.168.1.100",
        80
    );

    gateway.displayStatus();

    // ------------------------------------------------
    // 1. Outgoing NAT
    // ------------------------------------------------

    Packet request(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "Hello Server"
    );

    displayPacket("Original Outgoing Packet", request);

    Packet translatedRequest =
        gateway.processOutgoing(request);

    displayPacket(
        "After Outgoing NAT",
        translatedRequest
    );

    // ------------------------------------------------
    // 2. Reverse NAT
    // ------------------------------------------------

    Packet response(
        "10.0.0.20",
        8080,
        "203.0.113.5",
        40001,
        Protocol::TCP,
        "Hello Client"
    );

    displayPacket(
        "Incoming Server Response",
        response
    );

    Packet translatedResponse =
        gateway.processIncoming(response);

    displayPacket(
        "After Reverse NAT",
        translatedResponse
    );

    // ------------------------------------------------
    // 3. Port Forwarding
    // ------------------------------------------------

    Packet externalRequest(
        "203.0.113.10",
        55000,
        "203.0.113.5",
        8080,
        Protocol::TCP,
        "Hello Internal Server"
    );

    displayPacket(
        "External Request",
        externalRequest
    );

    Packet forwardedRequest =
        gateway.processIncoming(externalRequest);

    displayPacket(
        "After Port Forwarding",
        forwardedRequest
    );

    return 0;
}
