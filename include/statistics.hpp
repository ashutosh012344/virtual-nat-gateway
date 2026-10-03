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
    
    std::size_t getTotalPackets() const;
    std::size_t getOutgoingPackets() const;
    std::size_t getIncomingPackets() const;
    std::size_t getNatTranslations() const;
    std::size_t getReverseNatTranslations() const;
    std::size_t getPortForwardedPackets() const;
    std::size_t getDroppedPackets() const;

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
