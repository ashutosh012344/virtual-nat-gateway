#include "kernel_monitor.hpp"

#include <fstream>
#include <string>

KernelMonitor::KernelMonitor(const char* procPath)
    : procPath_(procPath) {
}

bool KernelMonitor::updateStatistics(
    std::size_t totalPackets,
    std::size_t outgoingPackets,
    std::size_t incomingPackets,
    std::size_t natTranslations,
    std::size_t reverseNatTranslations,
    std::size_t portForwardedPackets
) const {
    std::ofstream procFile(procPath_);

    if (!procFile.is_open()) {
        return false;
    }

    procFile
        << "total=" << totalPackets
        << " outgoing=" << outgoingPackets
        << " incoming=" << incomingPackets
        << " nat=" << natTranslations
        << " reverse=" << reverseNatTranslations
        << " forward=" << portForwardedPackets;

    return procFile.good();
}
