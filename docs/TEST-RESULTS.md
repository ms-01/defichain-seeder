# Test Results

## Development Steps 147-172

| Step | Description | Result |
|---|---|---|
| 147 | Inspect compact signature format | Completed |
| 148 | Create isolated development copy | Completed |
| 149 | Preserve existing protocol changes | Verified |
| 150 | Implement DeFiChain header parser | Implemented |
| 152 | Compile development Seeder | Successful |
| 153-164 | Inspect checkpoint and test dependencies | Completed |
| 165-166 | Create and verify standalone P2P test | Completed |
| 167-168 | Compile standalone test and fix output | Successful |
| 169 | Positive checkpoint test | PASS |
| 170-171 | Prepare and compile negative test | Successful |
| 172 | Invalid checkpoint test | Expected rejection |

## Build

Development binary:

`/opt/defichain-seeder/development/dnsseed`

Build command:

`make -B -j2`

Build exit code: 0.

Two compiler warnings were reported in existing serialization
and string-handling code. They require separate review.

## Production Isolation

The production Masternode process was checked repeatedly:

PID: 318400

Process: defid-init

The process remained running throughout the documented tests.

## Outstanding Validation

- Test against multiple external DeFiChain peers.
- Validate peer discovery and address collection.
- Validate database persistence.
- Validate DNS responses.
- Validate restart and recovery behavior.
- Perform security and operational review.


## Test Interpretation

The negative checkpoint test intentionally returns exit code 1.
This is the expected application result because the configured
checkpoint does not match the peer response.

The test is therefore considered successful as a negative test.

## Test Environment

- Upstream source baseline: 92d2b46
- DeFiChain reference node: 4.2.5
- Local P2P endpoint: 127.0.0.1:8555
- Network magic: e2 aa c1 e1
- Protocol version: 70039
- Minimum peer version: 70023

## Validation Limitations

The current results demonstrate checkpoint validation against
one local DeFiChain peer.

They do not establish full compatibility with external peers,
complete network crawling, DNS operation or production readiness.


## Compiler Warnings

The development build completed successfully with exit code 0.

Two compiler warnings were observed in existing serialization
and string-handling code.

These warnings have not yet been independently investigated
or classified as harmless.

---

## November 13, 2026 – External Crawler and Compiler Validation

### External P2P Crawler

A 180-second crawler test was performed using six bootstrap peers
and six crawler threads.

Results:

- 82 known peer addresses
- 15 peer connection attempts
- 8 available peers
- 8 validated peers in the peer dump
- 2 additional peers discovered beyond the bootstrap list
- DeFiChain Core versions 4.2.2, 4.2.4 and 4.2.5 observed

Result: PASS.

The test demonstrated successful external peer discovery
and acceptance of multiple DeFiChain peers.

### Checkpoint Validation

Reference block height: 6,500,000

Checkpoint hash:

`458bcc9a40059bd8ddd17f64090d34c0d389ab1e14400588c263b50f3c3a79b3`

Positive test:

- Correct checkpoint accepted
- One available peer
- Result: PASS

Negative test:

- Deliberately modified checkpoint rejected
- No accepted peers
- Result: EXPECTED REJECTION

Both crawler tests were stopped after their configured
120-second timeout.

### Compiler Optimization

Compiler: GCC 12.2.0

| Configuration | Result | Warnings | Binary size |
|---|---|---|---|
| O2 | Successful | 0 | 204 KB |
| O3 | Successful | 1 | 222 KB |

The remaining O3 warning is:

`-Wstringop-overflow`

Source area:

`DataStream::write` / serialization path in `bitcoin.cpp`.

The previous `-Wrestrict` warning in
`CService::ToStringIPPort` no longer occurs after
the string construction was revised.

Warning-free compilation with O2 does not establish
memory safety.

### Sanitizer Build

Configuration:

- GCC O2
- AddressSanitizer
- UndefinedBehaviorSanitizer
- Debug symbols enabled

Build result: PASS.

Sanitized binary size: approximately 14 MB.

The sanitizer runtime libraries were successfully linked.

### Sanitizer Runtime

Initial execution failed before crawler startup because
`stdbuf` interfered with AddressSanitizer library loading.

Exit code: 1.

This was a test-environment issue, not an observed
application memory violation.

A second runtime test without `stdbuf` was initiated.

Result: PENDING.

### Remaining Validation

- Complete sanitizer runtime analysis
- Validate database persistence and restart behavior
- Test DNS response generation
- Review production service configuration
- Investigate remaining O3 compiler warning
- Perform extended stability testing
