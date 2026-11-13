# Seeder Tests

## Current Tests

### 1. Header Hash Verification

Reference block: 6,500,000

Expected header length: 190 bytes.

Expected signature length: 65 bytes.

Result: PASS.

### 2. Positive P2P Checkpoint Test

Target: 127.0.0.1:8555

Expected checkpoint: 6,500,000.

Result: PASS.

### 3. Negative P2P Checkpoint Test

Expected behavior: Reject an incorrect checkpoint.

Result: PASS (rejection confirmed).

## Future Tests

- External peer connectivity
- Multiple peer crawling
- Address database persistence
- DNS A/AAAA resolution
- Restart and recovery
- Long-running stability

## Source Integrity

The original test sources were transferred from the development
server and verified using SHA256 checksums.

Both files are preserved unchanged.

## Build Requirements

- Linux x86-64
- GCC with C++20 support
- OpenSSL development libraries
- DeFiChain-compatible Seeder development source
- Compiled Seeder object files

## Build Location

The original development environment used:

/opt/defichain-seeder/development

Required object files:

- bitcoin.o
- db.o
- bitcoin_core/netbase.o
- bitcoin_core/protocol.o
- bitcoin_core/util.o

## Build Commands

Positive checkpoint test:

g++ -std=c++20 -O2 -pthread \
  -I/opt/defichain-seeder/development \
  -I/opt/defichain-seeder/development/bitcoin_core \
  /opt/defichain-seeder/test/test-p2p.cpp \
  /opt/defichain-seeder/development/bitcoin.o \
  /opt/defichain-seeder/development/db.o \
  /opt/defichain-seeder/development/bitcoin_core/netbase.o \
  /opt/defichain-seeder/development/bitcoin_core/protocol.o \
  /opt/defichain-seeder/development/bitcoin_core/util.o \
  -lcrypto \
  -o /opt/defichain-seeder/test/test-p2p

Negative checkpoint test:

Use the same command with:

test-p2p-invalid.cpp

as source and:

test-p2p-invalid

as output binary.

## Execution

Positive test:

timeout 75s ./test-p2p

Expected exit code: 0

Negative test:

timeout 75s ./test-p2p-invalid

Expected application exit code: 1,
because the invalid checkpoint must be rejected.

## Important

These tests validate checkpoint handling against a local
DeFiChain P2P node.

They do not prove full network crawler or DNS functionality.
