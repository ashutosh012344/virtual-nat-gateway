#include "connection_table.hpp"

#include <iostream>

void ConnectionTable::addMapping(
    const std::string& internalIp,
    int internalPort,
    const std::string& externalIp,
    int externalPort
) {
    mappings_.push_back({
        internalIp,
        internalPort,
        externalIp,
        externalPort
    });
}

const NATMapping* ConnectionTable::findByInternal(
    const std::string& internalIp,
    int internalPort
) const {
    for (const auto& mapping : mappings_) {
        if (mapping.internalIp == internalIp &&
            mapping.internalPort == internalPort) {
            return &mapping;
        }
    }

    return nullptr;
}

const NATMapping* ConnectionTable::findByExternal(
    const std::string& externalIp,
    int externalPort
) const {
    for (const auto& mapping : mappings_) {
        if (mapping.externalIp == externalIp &&
            mapping.externalPort == externalPort) {
            return &mapping;
        }
    }

    return nullptr;
}

void ConnectionTable::display() const {
    std::cout << "\nNAT Translation Table\n";
    std::cout << "----------------------------------------\n";

    if (mappings_.empty()) {
        std::cout << "No active mappings\n";
        return;
    }

    for (const auto& mapping : mappings_) {
        std::cout
            << mapping.internalIp
            << ":"
            << mapping.internalPort
            << "  ->  "
            << mapping.externalIp
            << ":"
            << mapping.externalPort
            << '\n';
    }
}

std::size_t ConnectionTable::size() const {
    return mappings_.size();
}
