#include <cassert>
#include <iostream>
#include "nat_gateway.hpp"
#include "nat_engine.hpp"
#include "port_forwarder.hpp"

void testOutgoingNat() {
    NatEngine engine("203.0.113.5", 40001);

    Packet packet(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "Test"
    );

    Packet translated = engine.translateOutgoing(packet);

    assert(translated.getSourceIp() == "203.0.113.5");
    assert(translated.getSourcePort() == 40001);

    std::cout << "[PASS] Outgoing NAT translation\n";
}

void testReverseNat() {
    NatEngine engine("203.0.113.5", 40001);

    Packet outgoing(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "Request"
    );

    Packet translated =
        engine.translateOutgoing(outgoing);

    Packet response(
        "10.0.0.20",
        8080,
        translated.getSourceIp(),
        translated.getSourcePort(),
        Protocol::TCP,
        "Response"
    );

    Packet restored =
        engine.translateIncoming(response);

    assert(restored.getDestinationIp() == "192.168.1.10");
    assert(restored.getDestinationPort() == 5000);

    std::cout << "[PASS] Reverse NAT translation\n";
}

void testPortForwarding() {
    PortForwarder forwarder;

    forwarder.addRule(
        8080,
        "192.168.1.100",
        80
    );

    Packet packet(
        "203.0.113.10",
        55000,
        "203.0.113.5",
        8080,
        Protocol::TCP,
        "Request"
    );

    Packet forwarded =
        forwarder.forwardPacket(packet);

    assert(forwarded.getDestinationIp() ==
           "192.168.1.100");

    assert(forwarded.getDestinationPort() == 80);

    std::cout << "[PASS] Port forwarding\n";
}

void testExistingMappingReuse() {
    NatEngine engine("203.0.113.5", 40001);

    Packet first(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "First"
    );

    Packet second(
        "192.168.1.10",
        5000,
        "10.0.0.30",
        9090,
        Protocol::TCP,
        "Second"
    );

    Packet translatedFirst =
        engine.translateOutgoing(first);

    Packet translatedSecond =
        engine.translateOutgoing(second);

    assert(
        translatedFirst.getSourcePort() ==
        translatedSecond.getSourcePort()
    );

    std::cout << "[PASS] Existing NAT mapping reuse\n";
}

void testUnknownIncomingPacket() {
    NatEngine engine("203.0.113.5", 40001);

    Packet packet(
        "10.0.0.20",
        8080,
        "203.0.113.5",
        45000,
        Protocol::TCP,
        "Unknown"
    );

    Packet result =
        engine.translateIncoming(packet);

    assert(result.getDestinationIp() ==
           "203.0.113.5");

    assert(result.getDestinationPort() == 45000);

    std::cout << "[PASS] Unknown incoming packet handling\n";
}

void testNatGatewayIntegration() {
    NatGateway gateway(
        "203.0.113.5",
        40001
    );

    gateway.addPortForwardRule(
        8080,
        "192.168.1.100",
        80
    );

    Packet outgoing(
        "192.168.1.10",
        5000,
        "10.0.0.20",
        8080,
        Protocol::TCP,
        "Request"
    );

    Packet translated =
        gateway.processOutgoing(outgoing);

    assert(translated.getSourceIp() ==
           "203.0.113.5");

    assert(translated.getSourcePort() ==
           40001);

    Packet response(
        "10.0.0.20",
        8080,
        "203.0.113.5",
        40001,
        Protocol::TCP,
        "Response"
    );

    Packet restored =
        gateway.processIncoming(response);

    assert(restored.getDestinationIp() ==
           "192.168.1.10");

    assert(restored.getDestinationPort() ==
           5000);

    Packet externalRequest(
        "203.0.113.10",
        55000,
        "203.0.113.5",
        8080,
        Protocol::TCP,
        "Forward"
    );

    Packet forwarded =
        gateway.processIncoming(externalRequest);

    assert(forwarded.getDestinationIp() ==
           "192.168.1.100");

    assert(forwarded.getDestinationPort() ==
           80);

    std::cout << "[PASS] NAT gateway integration\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << "       NAT GATEWAY TEST SUITE\n";
    std::cout << "========================================\n";

    testOutgoingNat();
    testReverseNat();
    testPortForwarding();
    testExistingMappingReuse();
    testUnknownIncomingPacket();
    testNatGatewayIntegration();

    std::cout << "\nAll tests passed successfully.\n";

    return 0;
}
