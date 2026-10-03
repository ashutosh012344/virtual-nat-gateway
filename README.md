# Virtual NAT Gateway & Port-Forwarding System

## Overview

A Linux-based Network Address Translation (NAT) Gateway implemented in C++.

The system demonstrates:

- NAT address and port translation
- Connection/translation table management
- Port forwarding
- Packet processing
- Linux networking concepts
- User-space and kernel-space interaction
- Network monitoring and statistics

## Architecture

```text
Client
   |
   v
NAT Gateway
   |
   +-- Packet Handler
   +-- NAT Translation Engine
   +-- Connection Table
   +-- Port Forwarder
   |
   v
External Server
