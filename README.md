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
