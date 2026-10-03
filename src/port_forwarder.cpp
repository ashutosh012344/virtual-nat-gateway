#include "port_forwarder.hpp"

#include <iostream>

void PortForwarder::addRule(
    int externalPort,
    const std::string& internalIp,
    int internalPort
) {
    rules_.push_back({
        externalPort,
        internalIp,
        internalPort
    });
}

const PortForwardRule* PortForwarder::findRule(
    int externalPort
) const {
    for (const auto& rule : rules_) {
        if (rule.externalPort == externalPort) {
            return &rule;
        }
    }

    return nullptr;
}

Packet PortForwarder::forwardPacket(
    const Packet& packet
) const {
    Packet forwardedPacket = packet;

    const PortForwardRule* rule =
        findRule(packet.getDestinationPort());

    if (rule != nullptr) {
        forwardedPacket.setDestinationIp(rule->internalIp);
        forwardedPacket.setDestinationPort(rule->internalPort);
    }

    return forwardedPacket;
}

void PortForwarder::displayRules() const {
    std::cout << "\nPort Forwarding Rules\n";
    std::cout << "----------------------------------------\n";

    if (rules_.empty()) {
        std::cout << "No port forwarding rules\n";
        return;
    }

    for (const auto& rule : rules_) {
        std::cout
            << "External Port "
            << rule.externalPort
            << "  ->  "
            << rule.internalIp
            << ":"
            << rule.internalPort
            << '\n';
    }
}

std::size_t PortForwarder::size() const {
    return rules_.size();
}
