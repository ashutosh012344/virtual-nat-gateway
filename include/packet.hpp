#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>

enum class Protocol {
    TCP,
    UDP
};

class Packet {
public:
    Packet(
        const std::string& sourceIp,
        int sourcePort,
        const std::string& destinationIp,
        int destinationPort,
        Protocol protocol,
        const std::string& payload
    );

    const std::string& getSourceIp() const;
    int getSourcePort() const;

    const std::string& getDestinationIp() const;
    int getDestinationPort() const;

    Protocol getProtocol() const;
    const std::string& getPayload() const;

    void setSourceIp(const std::string& ip);
    void setSourcePort(int port);

    void setDestinationIp(const std::string& ip);
    void setDestinationPort(int port);

private:
    std::string sourceIp_;
    int sourcePort_;

    std::string destinationIp_;
    int destinationPort_;

    Protocol protocol_;
    std::string payload_;
};

#endif
