#include "nat_engine.hpp"

NatEngine::NatEngine(
    const std::string& externalIp,
    int startingPort
)
    : externalIp_(externalIp),
      nextPort_(startingPort) {
}

int NatEngine::allocatePort() {
    return nextPort_++;
}

Packet NatEngine::translateOutgoing(const Packet& packet) {
    const NATMapping* existingMapping =
        connectionTable_.findByInternal(
            packet.getSourceIp(),
            packet.getSourcePort()
        );

    Packet translatedPacket = packet;

    if (existingMapping != nullptr) {
        translatedPacket.setSourceIp(existingMapping->externalIp);
        translatedPacket.setSourcePort(existingMapping->externalPort);

        return translatedPacket;
    }

    int translatedPort = allocatePort();

    connectionTable_.addMapping(
        packet.getSourceIp(),
        packet.getSourcePort(),
        externalIp_,
        translatedPort
    );

    translatedPacket.setSourceIp(externalIp_);
    translatedPacket.setSourcePort(translatedPort);

    return translatedPacket;
}

Packet NatEngine::translateIncoming(const Packet& packet) {
    const NATMapping* mapping =
        connectionTable_.findByExternal(
            packet.getDestinationIp(),
            packet.getDestinationPort()
        );

    Packet translatedPacket = packet;

    if (mapping != nullptr) {
        translatedPacket.setDestinationIp(mapping->internalIp);
        translatedPacket.setDestinationPort(mapping->internalPort);
    }

    return translatedPacket;
}
