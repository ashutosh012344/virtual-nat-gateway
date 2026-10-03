#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <cstddef>

class Statistics {
public:
    void recordOutgoingPacket();
    void recordIncomingPacket();
    void recordNatTranslation();
    void recordReverseNatTranslation();
    void recordPortForwarding();
    void recordDroppedPacket();

    void display() const;

private:
    std::size_t totalPackets_ = 0;
    std::size_t outgoingPackets_ = 0;
    std::size_t incomingPackets_ = 0;
    std::size_t natTranslations_ = 0;
    std::size_t reverseNatTranslations_ = 0;
    std::size_t portForwardedPackets_ = 0;
    std::size_t droppedPackets_ = 0;
};

#endif
