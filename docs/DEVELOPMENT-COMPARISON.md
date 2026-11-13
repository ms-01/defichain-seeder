# DeFiChain DNS Seeder – Development Comparison

**Date:** November 13, 2026
**Status:** Development / Crawler Validation
**Base commit:** `92d2b46`
**Upstream project:** `sipa/bitcoin-seeder`

## 1. Overview

Two locally compiled DNS Seeder variants are currently
available on the DeFiChain Masternode.

Both variants share the same upstream Git commit but
contain different DeFiChain-specific modifications.

The objective is to identify the implementation suitable
for reliable DeFiChain peer discovery.

## 2. Build Comparison

| Property | Upstream | Development |
|---|---|---|
| Directory | `/opt/defichain-seeder/upstream` | `/opt/defichain-seeder/development` |
| Binary size | 222 KB | 226 KB |
| Build date | Nov 12, 20:04 | Nov 12, 22:25 |
| Base commit | `92d2b46` | `92d2b46` |
| Modified files | 1 | 2 |
| Added lines | 2 | 39 |
| Removed lines | 2 | 6 |
| Protocol version | 70039 | 70039 |
| Minimum peer protocol | 70023 | 70023 |
| DeFiChain PoS header handling | Not adapted | Adapted |
| Successful crawling | Not verified | Not verified |

## 3. Protocol Modifications

Both variants modify `bitcoin_core/protocol.h`.

Original Bitcoin Seeder values:

- Protocol version: 60000
- Minimum peer protocol: 31800

DeFiChain-specific values:

- Protocol version: 70039
- Minimum peer protocol: 70023

These modifications align the configured protocol
versions with the identified DeFiChain parameters.

Successful P2P compatibility has not yet been verified.

## 4. Development-Specific Changes

The Development variant additionally modifies
`bitcoin.cpp`.

The modification affects known-block verification
and introduces DeFiChain-specific PoS header handling.

Implemented assumptions:

- Fixed header section: 124 bytes
- Signature length: 65 bytes
- Signature length encoded using CompactSize
- Transaction count must equal zero
- No trailing bytes may remain
- Serialized header is hashed for comparison
  with the configured known-block hash

These assumptions still require verification
against the DeFiChain Core 4.2.5 implementation.

## 5. Known-Block Validation Comparison

| Function | Upstream | Development |
|---|---|---|
| Header handling | Bitcoin format | DeFiChain PoS format |
| Fixed header section | Original implementation | 124 bytes |
| Signature handling | No separate PoS signature parsing | 65-byte signature |
| CompactSize handling | Original implementation | Explicit signature length check |
| Transaction count | Read | Must equal zero |
| Remaining payload | No explicit empty check in modified section | Must be empty |
| Hash comparison | Original header | Serialized DeFiChain header |

The Development implementation is the preferred
candidate for further investigation.

However, correctness and compatibility remain unverified.

## 6. Network Connectivity

Initial TCP connectivity tests were successful
for three known DeFiChain peer endpoints.

Tested port:

- TCP 8555

Result:

- 3 of 3 TCP connections successful

This confirms basic TCP reachability only.

It does not establish successful DeFiChain P2P
handshakes or crawler acceptance.

## 7. Current Crawler Status

The previous crawler test reported:

`0/1 available`

The test was terminated by a timeout.

A successful peer handshake and peer discovery
have not yet been demonstrated.

Potential investigation areas:

1. P2P handshake compatibility
2. Network magic handling
3. Protocol version negotiation
4. Minimum block height filtering
5. Known-block verification
6. Peer address discovery and validation

The exact cause remains undetermined.

## 8. Open Compiler Warnings

Two warnings remain under investigation:

| Warning | Source |
|---|---|
| `-Wstringop-overflow` | `bitcoin.cpp` / `DataStream::write` |
| `-Wrestrict` | `bitcoin_core/netbase.cpp` / `CService::ToStringIPPort` |

Both warnings must be evaluated before
production approval.

## 9. Recommended Next Steps

1. Verify the exact test parameters used previously.
2. Compare Upstream and Development crawler behavior.
3. Capture detailed P2P handshake diagnostics.
4. Identify the cause of `0/1 available`.
5. Validate the PoS header assumptions against Core 4.2.5.
6. Confirm successful peer discovery.
7. Perform an extended crawler stability test.
8. Resolve or assess remaining compiler warnings.
9. Enable DNS functionality only after crawler validation.

## 10. Conclusion

The Development variant includes additional
DeFiChain-specific known-block verification logic.

It is the preferred candidate for continued testing,
but it has not yet been demonstrated to be
production-ready.

The immediate priority is reliable P2P communication
and successful discovery of active DeFiChain nodes.

No public DNS Seeder deployment should be considered
complete until these requirements are satisfied.
