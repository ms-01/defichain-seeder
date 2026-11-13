# DeFiChain P2P Protocol Compatibility

## Protocol Settings

| Parameter | Value |
|---|---:|
| Protocol version | 70039 |
| Minimum peer version | 70023 |
| Mainnet P2P port | 8555 |
| Network magic | e2 aa c1 e1 |
| Checkpoint test height | 6,500,000 |

## Source Changes

File: `bitcoin_core/protocol.h`

The original Bitcoin Seeder protocol settings were changed:

- PROTOCOL_VERSION: 60000 -> 70039
- MIN_PEER_PROTO_VERSION: 31800 -> 70023

The original protocol changes were preserved in the development copy.

## DeFiChain Block Header

The DeFiChain block header contains:

- 124 bytes of fixed header fields
- CompactSize signature length
- 65-byte compact signature

Total serialized header length: 190 bytes.

The signature is part of the serialized block header and therefore
part of the block hash calculation.

## Compatibility Implementation

File: `bitcoin.cpp`

The header parser was adapted to:

1. Read the 124-byte fixed header.
2. Read and validate the signature length.
3. Read the 65-byte signature.
4. Reconstruct the serialized header.
5. Read the transaction count.
6. Verify the reconstructed header hash against the checkpoint.

The checkpoint response is accepted only if the transaction count
is zero, no unexpected payload remains and the calculated hash
matches the configured checkpoint.
