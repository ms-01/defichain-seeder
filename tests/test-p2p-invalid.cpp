#include <cstdio>
#include <csignal>
#include <string>

#include "bitcoin.h"
#include "db.h"
#include "netbase.h"
#include "protocol.h"
#include "uint256.h"

bool fTestNet = false;

int main() {
    signal(SIGPIPE, SIG_IGN);

    nDefaultP2Port = 8555;
    nMinimumHeight = 6500000;
    nConnectTimeout = 5000;

    pchMessageStart[0] = 0xe2;
    pchMessageStart[1] = 0xaa;
    pchMessageStart[2] = 0xc1;
    pchMessageStart[3] = 0xe1;

    auto checkpoint = uint256::FromHex(
        "458bcc9a40059bd8ddd17f64090d34c0d389ab1e14400588c263b50f3c3a79b4"
    );

    if (!checkpoint) {
        std::fprintf(stderr, "Invalid checkpoint hash\n");
        return 2;
    }

    hashKnownBlock = *checkpoint;

    CService peer("127.0.0.1", 8555);

    int ban = 0;
    int version = 0;
    int height = 0;
    uint64_t services = 0;
    std::string subversion;

    std::printf("=== DeFiChain Local P2P Test ===\n");
    std::printf("Target: 127.0.0.1:8555\n");
    std::printf("Minimum height: 6500000\n");
    std::printf("Checkpoint: %s\n",
                "458bcc9a40059bd8ddd17f64090d34c0d389ab1e14400588c263b50f3c3a79b4");
    std::fflush(stdout);

    bool success = TestNode(
        peer, ban, version, subversion,
        height, nullptr, services
    );

    std::printf("\n=== Results ===\n");
    std::printf("Connection and checkpoint result: %s\n",
                success ? "PASS" : "FAIL");
    std::printf("Protocol version: %d\n", version);
    std::printf("Client: %s\n", subversion.c_str());
    std::printf("Reported height: %d\n", height);
    std::printf("Services: %llu\n",
                static_cast<unsigned long long>(services));
    std::printf("Ban time: %d\n", ban);

    return success ? 0 : 1;
}
