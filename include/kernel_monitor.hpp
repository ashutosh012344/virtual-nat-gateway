#ifndef KERNEL_MONITOR_HPP
#define KERNEL_MONITOR_HPP

#include <cstddef>

class KernelMonitor {
public:
    explicit KernelMonitor(
        const char* procPath = "/proc/virtual_nat"
    );

    bool updateStatistics(
        std::size_t totalPackets,
        std::size_t outgoingPackets,
        std::size_t incomingPackets,
        std::size_t natTranslations,
        std::size_t reverseNatTranslations,
        std::size_t portForwardedPackets
    ) const;

private:
    const char* procPath_;
};

#endif
