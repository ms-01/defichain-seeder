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

## November 14, 2026 - RPC and Shutdown Validation

### STEP 197.1 - Standalone RPC Client

Environment:
- DeFiChain Core 4.2.5
- Local RPC endpoint: 127.0.0.1:8554
- Authentication: RPC cookie
- Implementation: C++20, libcurl, json-c
- Compiler flags: -Wall -Wextra -Werror

| Test | Result |
|---|---|
| RPC connection and authentication | PASS |
| Retrieve blockchain state | PASS |
| Retrieve block hash by height | PASS |
| Calculate checkpoint at depth 100 | PASS |
| Reject negative parameters | PASS |
| Checkpoint consistency retry | PASS |

Observed chain height: 6595123

Checkpoint height: 6595023

Checkpoint hash:
eadbfbc97f7bfe5ed0da7d861f2869315a0b520ec53cca0757e2fd7a245ae7fa

Result: PASS for standalone RPC functionality.

Limitations:
- RPC client not integrated into the Seeder.
- Concurrent checkpoint access not validated.
- RPC failure recovery and reorganizations not validated.

### STEP 198 - Isolated Test Preparation

- No existing Seeder process running.
- Local P2P endpoint listening on port 8555.
- Isolated test directory prepared.
- Production DeFiChain daemon remained operational.

Result: PASS.

### STEP 199 - Controlled Shutdown

Configuration:
- DNS disabled
- Bootstrap peer: 127.0.0.1
- P2P port: 8555
- Crawler threads: 2
- Minimum chain height: 6594000
- Test duration: 60 seconds

| Test | Result |
|---|---|
| Seeder startup | PASS |
| SIGTERM handling | PASS |
| Worker thread shutdown | PASS |
| Final database snapshot | PASS |
| Exit code | 0 |
| Available peers | 0/1 (1 tried) |

Generated files:
- dnsseed.dat: 146 bytes
- dnsseed.dump: 135 bytes

Result: PASS for controlled shutdown and snapshot creation.

The loopback peer was not classified as publicly available.

Database recovery after restart remains unverified.

### STEP 200 - Local Development Commit

Development server:
Masternode (v2202505142473340286)

Commit: ac8c7b6

Files:
- DEVELOPMENT_STATUS_2026-11-14.md
- rpc-client-test.cpp
- rpc_client.cpp
- rpc_client.h

Result: PASS for local Git checkpoint.

The commit has not been pushed to the public repository.

### Outstanding Validation

- [ ] Integrate RPC client into Seeder.
- [ ] Test concurrent checkpoint refresh.
- [ ] Test RPC failures and chain reorganizations.
- [ ] Validate database recovery after restart.
- [ ] Complete sanitizer runtime validation.
- [ ] Investigate outstanding compiler diagnostics.
- [ ] Validate public DNS responses.
- [ ] Complete extended stability and security testing.

### Production Assessment

Standalone RPC tests: PASS.

Controlled shutdown: PASS.

Final snapshot creation: PASS.

Integrated checkpoint management: NOT VERIFIED.

Database recovery: NOT VERIFIED.

Public DNS deployment: NOT APPROVED.

## November 14, 2026 - Additional Runtime Validation

### STEP 209 - Runtime Log Review

Historical test logs on the Masternode were reviewed.

| Test | Observed result |
|---|---|
| Local DNS query test | 2 DNS requests |
| DNS robustness test | 9 DNS requests |
| SIGINT shutdown | Exit status 0 |
| SIGTERM shutdown | Exit status 0 |
| Startup failure handling | Exit status 1 |
| Final database snapshot | Successfully written |

Local DNS request handling was observed.
Correct A/AAAA response contents remain unverified.

### STEP 210-215 - Memory and Sanitizer Investigation

A historical startup-failure test reported a
28-byte memory leak through LeakSanitizer.

The allocation trace references:
CDnsSeedOpts::ParseCommandLine(), main.cpp:264.

The relevant main.cpp files in the sanitized test
directory and current development directory
have identical SHA-256 checksums.

The existing sanitized binary links against:
- libasan.so.8
- libubsan.so.1

The historical leak has not been conclusively
reproduced or resolved for the original failure path.

### STEP 216 - Initial Sanitizer Retest

Exit code: 1.

The process terminated during command-line
validation because the required -m parameter
was missing.

No sanitizer findings were reported.

Result: INCONCLUSIVE.
The intended DNS initialization failure was not reached.

### STEP 217 - Sanitized Runtime Retest

The sanitized Seeder started successfully.

Observed:
- DNS server started.
- 13 DNS requests registered.
- SIGTERM received.
- Worker shutdown completed.
- Final database snapshot written.
- Internal shutdown exit status 0.
- External timeout exit code 124.
- No sanitizer findings reported.

The requested port 0 was not used for binding;
the Seeder started on its default DNS port 53.

Result: PASS for observed controlled shutdown.
Sanitizer findings: NONE REPORTED in this run.

Limitations:
- The original startup-failure path was not reproduced.
- The historical 28-byte leak remains unresolved.
- Correct DNS response contents remain unverified.
- Extended sanitizer runtime testing remains pending.

### Updated Production Assessment

Local DNS runtime: TESTED.
DNS response correctness: NOT VERIFIED.
Controlled shutdown: PASS.
Final database snapshot: PASS.
Sanitized runtime: NO FINDINGS IN OBSERVED RUN.
Historical memory leak: NOT CONCLUSIVELY RESOLVED.
RPC integration: PENDING.
Production deployment: NOT APPROVED.
