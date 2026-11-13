# Checkpoint and Header Validation

## Reference Checkpoint

Block height: 6,500,000

Block hash:

`458bcc9a40059bd8ddd17f64090d34c0d389ab1e14400588c263b50f3c3a79b3`

## Raw Block Verification

The raw block was retrieved through the DeFiChain RPC interface.

Observed values:

| Parameter | Result |
|---|---:|
| Raw block size | 998 bytes |
| Signature length | 65 bytes |
| Serialized header length | 190 bytes |
| Calculated header hash | Matches checkpoint |

Result: SUCCESS.

## Positive P2P Test

Target: 127.0.0.1:8555

Observed peer:

- Protocol: 70039
- Client: DeFiChain 4.2.5
- Reported height: 6,592,080
- Services: 1033
- Ban time: 0

Result: PASS.

## Negative P2P Test

The checkpoint was modified by changing its final hexadecimal
character from `3` to `4`.

Observed result:

- Connection established.
- Peer version received.
- Invalid checkpoint rejected.
- Test returned exit code 1.

Result: EXPECTED REJECTION.

## Conclusion

The tests demonstrate that the adapted Seeder can successfully
validate the configured DeFiChain checkpoint against the local
P2P node and reject an incorrect checkpoint.

They do not yet establish compatibility with the entire
production peer network.
