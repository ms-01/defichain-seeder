# DeFiChain Seeder

Independent development and documentation project for a
DeFiChain-compatible DNS Seeder.

## Objectives

- Restore and maintain independent DeFiChain P2P discovery infrastructure.
- Adapt the Bitcoin Seeder protocol implementation to DeFiChain.
- Validate DeFiChain Proof-of-Stake block headers.
- Verify peer compatibility and checkpoint validation.
- Establish a reproducible deployment and testing process.

## Current Status

| Component | Status |
|---|---|
| Isolated development copy | Completed |
| DeFiChain protocol version 70039 | Implemented |
| Minimum peer protocol 70023 | Implemented |
| DeFiChain header parser | Implemented |
| Header hash verification | Passed |
| Positive P2P checkpoint test | Passed |
| Invalid checkpoint rejection | Passed |
| Full network crawler validation | Pending |
| DNS service validation | Pending |
| Production deployment | Pending |

## Documentation

- [Architecture](docs/ARCHITECTURE.md)
- [Protocol Compatibility](docs/PROTOCOL-COMPATIBILITY.md)
- [Checkpoint Validation](docs/CHECKPOINT-VALIDATION.md)
- [Test Results](docs/TEST-RESULTS.md)
- [Deployment](docs/DEPLOYMENT.md)
- [Implementation Plan](docs/IMPLEMENTATION-PLAN.md)

## Scope

This repository documents the independent DeFiChain Seeder
development project.

The production Masternode and its existing services are kept
separate from experimental development.

## Development Status

Initial documentation: November 2026.

Upstream baseline: 92d2b46
Production reference: DeFiChain 4.2.5
Test endpoint: 127.0.0.1:8555

## Why This Project Is Complex

A DeFiChain DNS Seeder is not simply a DNS server.

It is a network discovery and validation service that must
understand enough of the DeFiChain protocol to distinguish
compatible and reachable blockchain nodes from unsuitable peers.

The implementation combines several engineering disciplines:

- Blockchain protocol compatibility and Proof-of-Stake headers
- P2P networking, handshakes and peer discovery
- Block hash and checkpoint validation
- Concurrent C++ programming and controlled thread shutdown
- Persistent peer databases and reliability classification
- DNS infrastructure, IPv4 and IPv6
- Local blockchain RPC integration and authentication
- Linux service operation, monitoring and security

### Architecture

The intended production architecture consists of:

1. A DeFiChain Core node providing blockchain state.
2. An RPC client retrieving current chain information.
3. A checkpoint manager maintaining validated reference blocks.
4. A P2P crawler discovering and evaluating network peers.
5. A persistent database tracking peer availability.
6. A DNS service publishing eligible peer addresses.
7. Operational monitoring and controlled service recovery.

These components must work together reliably.

### Engineering Challenges

The Seeder must handle network failures, incompatible peers,
changing blockchain heights, chain reorganizations and concurrent
operations without distributing invalid or unreliable peer data.

A successful build or isolated protocol test is therefore not
equivalent to a production-ready network service.

### Development Approach

Development is performed incrementally, with reproducible tests
and documented checkpoints.

Experimental builds remain isolated from production DeFiChain
services. Production deployment requires additional integration,
security, network and stability validation.

### Current Development Milestone

As of November 14, 2026:

- DeFiChain protocol compatibility has been tested.
- External peer discovery has been demonstrated.
- Controlled shutdown and final database snapshots have passed.
- A standalone RPC client has passed initial checkpoint tests.
- Integration of dynamic checkpoints into the Seeder is pending.
- Public DNS operation has not been approved for production.

The objective is a maintainable, independently operated
DeFiChain peer discovery service that can support the network
without depending on a single infrastructure provider.
