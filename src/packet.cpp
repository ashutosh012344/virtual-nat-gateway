#include "packet.hpp"

Packet::Packet(
    const std::string& sourceIp,
    int sourcePort,
    const std::string& destinationIp,
    int destinationPort,
    Protocol protocol,
    const std::string& payload
)
    : sourceIp_(sourceIp),
      sourcePort_(sourcePort),
      destinationIp_(destinationIp),
      destinationPort_(destinationPort),
      protocol_(protocol),
      payload_(payload) {
}

const std::string& Packet::getSourceIp() const {
    return sourceIp_;
}

int Packet::getSourcePort() const {
    return sourcePort_;
}

const std::string& Packet::getDestinationIp() const {
    return destinationIp_;
}

int Packet::getDestinationPort() const {
    return destinationPort_;
}

Protocol Packet::getProtocol() const {
    return protocol_;
}

const std::string& Packet::getPayload() const {
    return payload_;
}

void Packet::setSourceIp(const std::string& ip) {
    sourceIp_ = ip;
}

void Packet::setSourcePort(int port) {
    sourcePort_ = port;
}

void Packet::setDestinationIp(const std::string& ip) {
    destinationIp_ = ip;
}

void Packet::setDestinationPort(int port) {
    destinationPort_ = port;
}
