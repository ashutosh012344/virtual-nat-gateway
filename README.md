# Virtual NAT Gateway & Port-Forwarding System

## 1. Overview

Virtual NAT Gateway & Port-Forwarding System is a Linux-based networking project implemented primarily in C++.

The project demonstrates the core concepts of a Network Address Translation (NAT) gateway, port forwarding, connection tracking, Linux network namespaces, Linux NAT/MASQUERADE, and user-space to kernel-space interaction.

A custom Linux kernel module is also implemented to monitor NAT gateway statistics through the `/proc/virtual_nat` interface.

---

## 2. Objectives

The main objectives of this project are:

- Implement basic NAT address and port translation.
- Maintain a NAT connection/translation table.
- Implement reverse NAT translation.
- Implement port forwarding.
- Maintain NAT gateway statistics.
- Demonstrate Linux network namespaces and virtual Ethernet interfaces.
- Demonstrate Linux IP forwarding and MASQUERADE.
- Implement a Linux kernel monitoring module.
- Synchronize C++ application statistics with the kernel module.
- Provide automated tests for the NAT gateway functionality.

---

## 3. System Architecture

### 3.1 Software Architecture

```text
                    Virtual NAT Gateway
                           |
        +------------------+------------------+
        |                  |                  |
        v                  v                  v
 Packet Handler       NAT Engine        Port Forwarder
                           |
                           v
                  Connection Table
                           |
                           v
                    Statistics Module
                           |
                           v
                 Kernel Monitor Interface
                           |
                           v
                   /proc/virtual_nat
                           |
                           v
                  Linux Kernel Module

###3.2 Linux Network Architecture

                    Linux Host
                Virtual NAT Gateway
                       |
          +------------+------------+
          |                         |
          |                         |
     veth-client               veth-server
      10.0.1.1                  10.0.2.1
          |                         |
          |                         |
   Client Namespace          Server Namespace
      10.0.1.2                  10.0.2.2

The Linux host acts as the gateway between the client and server namespaces.

## 4. Main Features
### NAT Translation

The NAT engine translates an internal source IP and port into an external IP and allocated port.

Example:

Internal:
192.168.1.10:5000

        ↓ NAT

External:
203.0.113.5:40001

## Reverse NAT
### Incoming responses are mapped back to the original internal client.

External:
203.0.113.5:40001

        |
        | Reverse NAT
        v

Internal:
192.168.1.10:5000

## Port Forwarding
## External requests received on a configured port are forwarded to an internal server.

203.0.113.5:8080
        |
        v
192.168.1.100:80

## Connection Table
## The connection table stores NAT mappings between internal and external addresses and ports.

Statistics
The gateway maintains statistics for:
- Total packets
- Outgoing packets
- Incoming packets
- NAT translations
- Reverse NAT translations
- Port-forwarded packets
- Dropped packets

## Linux Kernel Monitoring
## A custom Linux kernel module creates:
/proc/virtual_nat

Example output:

Virtual NAT Gateway Kernel Monitor
--------------------------------
Status: Kernel module loaded
Total packets          : 3
Outgoing packets       : 1
Incoming packets       : 2
NAT translations       : 1
Reverse translations   : 1
Port-forwarded packets : 1

## 5. Linux Networking Demonstration
## The project uses Linux network namespaces to simulate separate client and server environments.

Client
Namespace: client
IP: 10.0.1.2/24
Gateway: 10.0.1.1

Server
Namespace: server
IP: 10.0.2.2/24
Gateway: 10.0.2.1

IPv4 forwarding is enabled on the Linux host:
net.ipv4.ip_forward = 1

Linux MASQUERADE is used for source NAT:
10.0.1.0/24
      |
      | MASQUERADE
      v
veth-server

## 6. Linux Kernel Module
The project includes:
kernel/virtual_nat_monitor.c

The module demonstrates Linux kernel module concepts including:
- Module initialization
- Module cleanup
- Kernel logging
- /proc interface
- User-space/kernel-space interaction
- Runtime statistics monitoring

The module creates:
/proc/virtual_nat

Example output:
Virtual NAT Gateway Kernel Monitor
--------------------------------
Status: Kernel module loaded
Total packets          : 3
Outgoing packets       : 1
Incoming packets       : 2
NAT translations       : 1
Reverse translations   : 1
Port-forwarded packets : 1

## 7. Project Structure

virtual-nat-gateway/
│
├── CMakeLists.txt
├── Makefile
├── README.md
├── .gitignore
│
├── include/
│   ├── connection_table.hpp
│   ├── kernel_monitor.hpp
│   ├── nat_engine.hpp
│   ├── nat_gateway.hpp
│   ├── packet.hpp
│   ├── port_forwarder.hpp
│   └── statistics.hpp
│
├── src/
│   ├── connection_table.cpp
│   ├── kernel_monitor.cpp
│   ├── main.cpp
│   ├── nat_engine.cpp
│   ├── nat_gateway.cpp
│   ├── packet.cpp
│   ├── port_forwarder.cpp
│   └── statistics.cpp
│
├── tests/
│   └── test_nat_gateway.cpp
│
└── kernel/
    ├── Makefile
    └── virtual_nat_monitor.c

## 8. Technologies Used

- C++
- C
- Linux
- Linux Kernel Modules
- Linux Network Namespaces
- Virtual Ethernet (veth)
- IP Forwarding
- iptables
- MASQUERADE
- tcpdump
- CMake
- Make
- Git
- GitHub

## 9. Build the C++ Project
From the project directory:
cmake -S . -B build
cmake --build build

The following executables are generated:
build/vnat-gateway
build/nat-tests

## 10. Run the NAT Gateway
./build/vnat-gateway

The application demonstrates:
1. Outgoing NAT translation.
2. Reverse NAT translation.
3. Port forwarding.
4. NAT statistics.
5. Kernel statistics synchronization.

Output:

========================================
       VIRTUAL NAT GATEWAY
========================================

NAT Gateway Status
----------------------------------------

Port Forwarding Rules
----------------------------------------
External Port 8080  ->  192.168.1.100:80

Original Outgoing Packet
----------------------------------------
Source      : 192.168.1.10:5000
Destination : 10.0.0.20:8080
Payload     : Hello Server

After Outgoing NAT
----------------------------------------
Source      : 203.0.113.5:40001
Destination : 10.0.0.20:8080
Payload     : Hello Server

Incoming Server Response
----------------------------------------
Source      : 10.0.0.20:8080
Destination : 203.0.113.5:40001
Payload     : Hello Client

After Reverse NAT
----------------------------------------
Source      : 10.0.0.20:8080
Destination : 192.168.1.10:5000
Payload     : Hello Client

External Request
----------------------------------------
Source      : 203.0.113.10:55000
Destination : 203.0.113.5:8080
Payload     : Hello Internal Server

After Port Forwarding
----------------------------------------
Source      : 203.0.113.10:55000
Destination : 192.168.1.100:80
Payload     : Hello Internal Server

NAT Gateway Statistics
----------------------------------------
Total packets          : 3
Outgoing packets       : 1
Incoming packets       : 2
NAT translations       : 1
Reverse translations   : 1
Port-forwarded packets : 1
Dropped packets        : 0

## 11. Run the Test Suite
./build/nat-tests

Expected result:
========================================
       NAT GATEWAY TEST SUITE
========================================
[PASS] Outgoing NAT translation
[PASS] Reverse NAT translation
[PASS] Port forwarding
[PASS] Existing NAT mapping reuse
[PASS] Unknown incoming packet handling
[PASS] NAT gateway integration

All tests passed successfully.

The project currently contains six automated tests, and all six tests pass successfully.

## 12. Build the Linux Kernel Module
Enter the kernel directory:
cd kernel

Build the module:
make

Return to the project directory:
cd ..

The compiled kernel module is:
kernel/virtual_nat_monitor.ko

## 13.  Load the Kernel Module

Load the module:
sudo insmod kernel/virtual_nat_monitor.ko

Verify that it is loaded:
lsmod | grep virtual_nat_monitor

Example:
virtual_nat_monitor    16384  0

Check the kernel interface:
cat /proc/virtual_nat

Example:
Virtual NAT Gateway Kernel Monitor
--------------------------------
Status: Kernel module loaded
Total packets          : 3
Outgoing packets       : 1
Incoming packets       : 2
NAT translations       : 1
Reverse translations   : 1
Port-forwarded packets : 1

## 14. Linux Network Demonstration
The Linux networking demonstration uses two network namespaces:
client
server

Check the namespaces:
sudo ip netns list

Example:
server (id: 1)
client (id: 0)

Check the Client
sudo ip netns exec client ip addr

The client uses:
10.0.1.2/24

Check the Server
sudo ip netns exec server ip addr

The server uses:
10.0.2.2/24

## 15. Linux IP Forwarding
Check IPv4 forwarding:
sysctl net.ipv4.ip_forward

Expected result:
net.ipv4.ip_forward = 1

This allows the Linux host to forward packets between the client and server networks.

## 16. Test Client-to-Server Connectivity
Run:
sudo ip netns exec client ping -c 3 10.0.2.2

Expected result:
3 packets transmitted, 3 received, 0% packet loss

Example:
64 bytes from 10.0.2.2: icmp_seq=1 ttl=63
64 bytes from 10.0.2.2: icmp_seq=2 ttl=63
64 bytes from 10.0.2.2: icmp_seq=3 ttl=63

3 packets transmitted, 3 received, 0% packet loss

## 17. Linux Network Interfaces
The Linux host uses two virtual Ethernet interfaces:
veth-client
    10.0.1.1/24

veth-server
    10.0.2.1/24

The complete network topology is:
Client Namespace
10.0.1.2
     |
     |
veth-client-ns
     |
     |
veth-client
10.0.1.1
     |
     |
Linux Host / NAT Gateway
     |
     |
veth-server
10.0.2.1
     |
     |
veth-server-ns
     |
     |
Server Namespace
10.0.2.2

## 18. Client Routing
Check the client routing table:
sudo ip netns exec client ip route

Example:
10.0.1.0/24 dev veth-client-ns proto kernel scope link src 10.0.1.2
10.0.2.0/24 via 10.0.1.1 dev veth-client-ns

The client sends traffic destined for the server network through the Linux gateway:
10.0.1.1

## 19. Server Routing
Check the server routing table:
sudo ip netns exec server ip route

Example:
10.0.1.0/24 via 10.0.2.1 dev veth-server-ns
10.0.2.0/24 dev veth-server-ns proto kernel scope link src 10.0.2.2

The server uses:
10.0.2.1

as the gateway to reach the client network.

## 20. Linux NAT Configuration
Display the NAT configuration:
sudo iptables -t nat -L -n -v

The project uses a MASQUERADE rule for traffic originating from:
10.0.1.0/24

and leaving through:
veth-server

Example:
Chain POSTROUTING (policy ACCEPT)
 pkts bytes target      prot opt in out         source
    6   504 MASQUERADE  all  --  *  veth-server 10.0.1.0/24

The packet and byte counters demonstrate that traffic has passed through the NAT rule.

## 21. Verify NAT with tcpdump
Start packet capture inside the server namespace:
sudo ip netns exec server tcpdump -n -i veth-server-ns icmp

In another terminal, generate traffic from the client:
sudo ip netns exec client ping -c 3 10.0.2.2

Example captured traffic:
10.0.2.1 > 10.0.2.2: ICMP echo request
10.0.2.2 > 10.0.2.1: ICMP echo reply

10.0.2.1 > 10.0.2.2: ICMP echo request
10.0.2.2 > 10.0.2.1: ICMP echo reply

10.0.2.1 > 10.0.2.2: ICMP echo request
10.0.2.2 > 10.0.2.1: ICMP echo reply

This demonstrates that the original client traffic is translated before reaching the server.
The client source address is:
10.0.1.2

The server observes the NAT-translated source address:
10.0.2.1

## 22. Kernel Statistics Integration
After running the C++ NAT Gateway, check:
cat /proc/virtual_nat

Example:
Virtual NAT Gateway Kernel Monitor
--------------------------------
Status: Kernel module loaded
Total packets          : 3
Outgoing packets       : 1
Incoming packets       : 2
NAT translations       : 1
Reverse translations   : 1
Port-forwarded packets : 1

The data flow is:
C++ NAT Gateway
       |
       v
Kernel Monitor
       |
       v
/proc/virtual_nat
       |
       v
Linux Kernel Module

This demonstrates user-space and kernel-space interaction.

## 23. Kernel Module Logs
Kernel module activity can be checked using:
sudo dmesg | grep virtual_nat_monitor | tail -10

Example:
virtual_nat_monitor: module loaded
virtual_nat_monitor: /proc/virtual_nat created

These messages confirm that the custom kernel module was successfully loaded and that the /proc/virtual_nat interface was created.

## 24. Testing Summary
The automated test suite verifies:
Test	Result
Outgoing NAT translation	PASS
Reverse NAT translation	PASS
Port forwarding	PASS
Existing NAT mapping reuse	PASS
Unknown incoming packet handling	PASS
NAT gateway integration	PASS


Total: 6/6 tests passed

## 25. Project Demonstration Flow
1. Load and verify the Linux kernel module
             |
             v
2. Show /proc/virtual_nat
             |
             v
3. Run the C++ NAT Gateway
             |
             v
4. Run the automated test suite
             |
             v
5. Show Linux network namespaces
             |
             v
6. Show client and server IP addresses
             |
             v
7. Demonstrate client-server connectivity
             |
             v
8. Show Linux NAT/MASQUERADE rule
             |
             v
9. Capture translated traffic using tcpdump

## 26. Cleanup
After completing the Linux networking demonstration, the temporary network namespaces and interfaces can be removed.
Delete the namespaces:
sudo ip netns del client
sudo ip netns del server

Remove the host-side virtual Ethernet interfaces if they still exist:
sudo ip link del veth-client 2>/dev/null || true
sudo ip link del veth-server 2>/dev/null || true

Restore IPv4 forwarding if required:
sudo sysctl -w net.ipv4.ip_forward=0

Unload the kernel module when it is no longer needed:
sudo rmmod virtual_nat_monitor

Verify:
lsmod | grep virtual_nat_monitor

## 27. Conclusion
The Virtual NAT Gateway & Port-Forwarding System demonstrates core Network Address Translation and Linux networking concepts using C++ and Linux.
The project combines:
- C++ NAT logic
- NAT address and port translation
- Reverse NAT
- Port forwarding
- Connection/translation table
- NAT statistics
- Linux network namespaces
- Virtual Ethernet interfaces
- Linux routing
- IPv4 forwarding
- Linux MASQUERADE
- tcpdump packet monitoring
- Linux kernel module development
- /proc kernel interface
- User-space and kernel-space interaction
- Automated testing
The project provides a practical demonstration of software architecture, Linux system programming, networking concepts, and relevant Linux kernel module concepts.


