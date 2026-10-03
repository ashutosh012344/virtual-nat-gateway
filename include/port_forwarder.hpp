#ifndef PORT_FORWARDER_HPP
#define PORT_FORWARDER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "packet.hpp"

struct PortForwardRule {
    int externalPort;
    std::string internalIp;
    int internalPort;
};

class PortForwarder {
public:
    void addRule(
        int externalPort,
        const std::string& internalIp,
        int internalPort
    );

    const PortForwardRule* findRule(int externalPort) const;

    Packet forwardPacket(const Packet& packet) const;

    void displayRules() const;

    std::size_t size() const;

private:
    std::vector<PortForwardRule> rules_;
};

#endif
