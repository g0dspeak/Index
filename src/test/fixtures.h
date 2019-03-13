#include "primitives/transaction.h"
#include "test/test_bitcoin.h"
#include "zerocoin.h"
#include "test/testutil.h"

#include <boost/test/unit_test.hpp>

static bool no_check( std::runtime_error const& ex ) { return true; }

struct ZerocoinTestingSetupBase : public TestingSetup {
    ZerocoinTestingSetupBase();
    
    CScript scriptPubKey;
    
    CBlock CreateBlock(const std::vector<CMutableTransaction>&,
                       const CScript&);

    bool ProcessBlock(CBlock&);

    // Create a new block with just given transactions, coinbase paying to
    // scriptPubKey, and try to add it to the current chain.
    CBlock CreateAndProcessBlock(const std::vector<CMutableTransaction>&,
                                 const CScript&);

    std::vector<CTransaction> coinbaseTxns; // For convenience, coinbase transactionsl
    CKey coinbaseKey; // private/public key needed to spend coinbase transactions
};

struct ZerocoinTestingSetup200 : public ZerocoinTestingSetupBase {
        ZerocoinTestingSetup200();
};

struct ZerocoinTestingSetup109 : public ZerocoinTestingSetupBase {
        ZerocoinTestingSetup109();
};

struct MtpMalformedTestingSetup : public ZerocoinTestingSetupBase {
        MtpMalformedTestingSetup();

    CBlock CreateBlock(const std::vector<CMutableTransaction>&,
                       const CScript&, bool);

    CBlock CreateAndProcessBlock(const std::vector<CMutableTransaction>&,
                                 const CScript&, bool);
};