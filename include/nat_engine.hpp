#ifndef NAT_ENGINE_HPP
#define NAT_ENGINE_HPP

#include "connection_table.hpp"
#include "packet.hpp"

class NatEngine {
public:
    NatEngine(
        const std::string& externalIp,
        int startingPort
    );

    Packet translateOutgoing(const Packet& packet);

    Packet translateIncoming(const Packet& packet);

private:
    ConnectionTable connectionTable_;
    std::string externalIp_;
    int nextPort_;

    int allocatePort();
};

#endif
