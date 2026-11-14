# Implementation Plan

## Phase 1 - Protocol Compatibility
Status: Implemented and validated for the tested checkpoint.

- [x] Update protocol version.
- [x] Update minimum peer version.
- [x] Implement DeFiChain header parsing.
- [x] Verify header hash.
- [x] Positive checkpoint test.
- [x] Negative checkpoint test.

## Phase 2 - Peer Discovery
Status: Pending.

- [ ] Verify external peer connections.
- [ ] Test peer version handling.
- [ ] Test multiple peer connections.
- [ ] Validate address collection.
- [ ] Verify peer filtering.

## Phase 3 - Seeder Database
Status: Pending.

- [ ] Validate address database persistence.
- [ ] Test restart and recovery.
- [ ] Validate good/bad peer classification.
- [ ] Review minimum chain height logic.

## Phase 4 - DNS Service
Status: Pending.

- [ ] Configure DNS hostname.
- [ ] Configure authoritative nameserver.
- [ ] Test A and AAAA responses.
- [ ] Validate returned peer addresses.
- [ ] Test DNS availability and response times.

## Phase 5 - Operational Deployment
Status: Pending.

- [ ] Prepare isolated service deployment.
- [ ] Configure systemd.
- [ ] Configure firewall.
- [ ] Configure monitoring and logging.
- [ ] Test restart and failure recovery.

## Phase 6 - Production Readiness
Status: Pending.

- [ ] Complete external network testing.
- [ ] Complete security review.
- [ ] Verify operational stability.
- [ ] Publish seed endpoint.
- [ ] Document maintenance procedures.

## Phase 7 - Dynamic Checkpoint Integration

Status: In development.

The standalone RPC client has been implemented and tested
against a local DeFiChain Core 4.2.5 node.

- [x] Implement local RPC client.
- [x] Implement cookie-based authentication.
- [x] Retrieve blockchain height and best block hash.
- [x] Calculate checkpoints using confirmation depth.
- [x] Reject negative checkpoint parameters.
- [x] Verify checkpoint consistency against chain changes.
- [ ] Integrate RPC client into the Seeder.
- [ ] Implement thread-safe checkpoint snapshots.
- [ ] Handle RPC connection failures and timeouts.
- [ ] Test chain reorganizations.
- [ ] Validate checkpoint refresh during crawler operation.

## Phase 8 - Shutdown and Persistence

Status: Partially validated.

The isolated 60-second test on November 14, 2026
completed with exit code 0.

- [x] Start two crawler threads.
- [x] Handle SIGTERM.
- [x] Join worker threads during shutdown.
- [x] Write final database snapshot.
- [x] Verify production node remains operational.
- [ ] Validate database recovery after restart.
- [ ] Complete extended runtime stability tests.

## Phase 9 - Final Engineering Review

Status: Pending.

- [ ] Review remaining GCC stringop-overflow warning.
- [ ] Confirm resolution of previous GCC restrict warning.
- [ ] Validate concurrent RPC and crawler operations.
- [ ] Review authentication and credential handling.
- [ ] Complete sanitizer runtime validation.
- [ ] Perform extended external peer testing.
- [ ] Verify production DNS behavior.
- [ ] Complete production security review.

## Development Checkpoint - November 14, 2026

Development server:
Masternode (v2202505142473340286)

Local development commit:
ac8c7b6

The RPC client and its tests are committed locally
on the development server.

The implementation has not yet been integrated into
the public Seeder repository.

No production deployment has been performed.
