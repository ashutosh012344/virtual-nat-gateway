#include "nat_gateway.hpp"

#include <iostream>

NatGateway::NatGateway(
    const std::string& externalIp,
    int startingPort
)
    : natEngine_(externalIp, startingPort) {
}

Packet NatGateway::processOutgoing(
    const Packet& packet
) {
    return natEngine_.translateOutgoing(packet);
}

Packet NatGateway::processIncoming(
    const Packet& packet
) {
    const PortForwardRule* rule =
        portForwarder_.findRule(
            packet.getDestinationPort()
        );

    if (rule != nullptr) {
        return portForwarder_.forwardPacket(packet);
    }

    return natEngine_.translateIncoming(packet);
}

void NatGateway::addPortForwardRule(
    int externalPort,
    const std::string& internalIp,
    int internalPort
) {
    portForwarder_.addRule(
        externalPort,
        internalIp,
        internalPort
    );
}

void NatGateway::displayStatus() const {
    std::cout << "\nNAT Gateway Status\n";
    std::cout << "----------------------------------------\n";

    portForwarder_.displayRules();
}
