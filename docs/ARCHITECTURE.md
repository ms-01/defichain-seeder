# Seeder Architecture

## Objective

Provide independent peer discovery infrastructure for DeFiChain.

## Technical Components

1. P2P network connectivity
2. Version handshake
3. Peer protocol compatibility
4. Known-block checkpoint validation
5. Peer crawling and reliability assessment
6. Address database
7. DNS response service
8. Operational monitoring

## Development Separation

The development environment was created as an isolated copy
of the existing Seeder source.

Development path on the server:

`/opt/defichain-seeder/development`

Original source:

`/opt/defichain-seeder/upstream`

The production Masternode remained running during the documented
development and testing steps.

## Important Distinction

Successful P2P checkpoint validation does not automatically
prove that the complete crawler, address database and DNS service
are production-ready.
