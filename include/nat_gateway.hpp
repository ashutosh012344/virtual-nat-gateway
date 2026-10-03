#ifndef NAT_GATEWAY_HPP
#define NAT_GATEWAY_HPP

#include "nat_engine.hpp"
#include "port_forwarder.hpp"

class NatGateway {
public:
    NatGateway(
        const std::string& externalIp,
        int startingPort
    );

    Packet processOutgoing(const Packet& packet);

    Packet processIncoming(const Packet& packet);

    void addPortForwardRule(
        int externalPort,
        const std::string& internalIp,
        int internalPort
    );

    void displayStatus() const;

private:
    NatEngine natEngine_;
    PortForwarder portForwarder_;
};

#endif
