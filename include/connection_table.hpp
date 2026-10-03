#ifndef CONNECTION_TABLE_HPP
#define CONNECTION_TABLE_HPP

#include <string>
#include <vector>

struct NATMapping {
    std::string internalIp;
    int internalPort;

    std::string externalIp;
    int externalPort;
};

class ConnectionTable {
public:
    void addMapping(
        const std::string& internalIp,
        int internalPort,
        const std::string& externalIp,
        int externalPort
    );

    const NATMapping* findByInternal(
        const std::string& internalIp,
        int internalPort
    ) const;

    const NATMapping* findByExternal(
        const std::string& externalIp,
        int externalPort
    ) const;

    void display() const;

    std::size_t size() const;

private:
    std::vector<NATMapping> mappings_;
};

#endif
