#include "statistics.hpp"

#include <iostream>

void Statistics::recordOutgoingPacket() {
    ++totalPackets_;
    ++outgoingPackets_;
}

void Statistics::recordIncomingPacket() {
    ++totalPackets_;
    ++incomingPackets_;
}

void Statistics::recordNatTranslation() {
    ++natTranslations_;
}

void Statistics::recordReverseNatTranslation() {
    ++reverseNatTranslations_;
}

void Statistics::recordPortForwarding() {
    ++portForwardedPackets_;
}

void Statistics::recordDroppedPacket() {
    ++droppedPackets_;
}

void Statistics::display() const {
    std::cout << "\nNAT Gateway Statistics\n";
    std::cout << "----------------------------------------\n";

    std::cout << "Total packets          : "
              << totalPackets_ << '\n';

    std::cout << "Outgoing packets       : "
              << outgoingPackets_ << '\n';

    std::cout << "Incoming packets       : "
              << incomingPackets_ << '\n';

    std::cout << "NAT translations       : "
              << natTranslations_ << '\n';

    std::cout << "Reverse translations   : "
              << reverseNatTranslations_ << '\n';

    std::cout << "Port-forwarded packets : "
              << portForwardedPackets_ << '\n';

    std::cout << "Dropped packets        : "
              << droppedPackets_ << '\n';
}
