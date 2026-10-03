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
    statistics_.recordOutgoingPacket();

    Packet translatedPacket =
        natEngine_.translateOutgoing(packet);

    statistics_.recordNatTranslation();

    return translatedPacket;
}

Packet NatGateway::processIncoming(
    const Packet& packet
) {
    statistics_.recordIncomingPacket();

    const PortForwardRule* rule =
        portForwarder_.findRule(
            packet.getDestinationPort()
        );

    if (rule != nullptr) {
        statistics_.recordPortForwarding();

        return portForwarder_.forwardPacket(packet);
    }

    Packet translatedPacket =
        natEngine_.translateIncoming(packet);

    if (translatedPacket.getDestinationIp() !=
            packet.getDestinationIp() ||
        translatedPacket.getDestinationPort() !=
            packet.getDestinationPort()) {

        statistics_.recordReverseNatTranslation();
    } else {
        statistics_.recordDroppedPacket();
    }

    return translatedPacket;
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
void NatGateway::displayStatistics() const {
    statistics_.display();
}

void NatGateway::syncKernelStatistics() const {
    kernelMonitor_.updateStatistics(
        statistics_.getTotalPackets(),
        statistics_.getOutgoingPackets(),
        statistics_.getIncomingPackets(),
        statistics_.getNatTranslations(),
        statistics_.getReverseNatTranslations(),
        statistics_.getPortForwardedPackets()
    );
}
