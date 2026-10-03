#include <iostream>

#include "packet.hpp"
#include "port_forwarder.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << "       VIRTUAL NAT GATEWAY\n";
    std::cout << "========================================\n";

    PortForwarder forwarder;

    // Configure port forwarding:
    // 203.0.113.5:8080 -> 192.168.1.100:80
    forwarder.addRule(
        8080,
        "192.168.1.100",
        80
    );

    forwarder.displayRules();

    // Incoming packet from an external client
    Packet incomingPacket(
        "203.0.113.10",
        55000,
        "203.0.113.5",
        8080,
        Protocol::TCP,
        "Hello Internal Server"
    );

    std::cout << "\nIncoming Packet\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << incomingPacket.getSourceIp()
              << ":"
              << incomingPacket.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << incomingPacket.getDestinationIp()
              << ":"
              << incomingPacket.getDestinationPort()
              << "\n";

    // Apply port forwarding
    Packet forwardedPacket =
        forwarder.forwardPacket(incomingPacket);

    std::cout << "\nAfter Port Forwarding\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Source      : "
              << forwardedPacket.getSourceIp()
              << ":"
              << forwardedPacket.getSourcePort()
              << "\n";

    std::cout << "Destination : "
              << forwardedPacket.getDestinationIp()
              << ":"
              << forwardedPacket.getDestinationPort()
              << "\n";

    return 0;
}
