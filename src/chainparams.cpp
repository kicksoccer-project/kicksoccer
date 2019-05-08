// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The Kicksoccer developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("00000c42789aa13befe57776f7ed976779858369e180cd0cf982f37a3767fe6f"))
    (50, uint256("00000f1b0c7b5e0acca78a5fdae623ac69313bc445f832ebad221bb35010ce55"))
    (150, uint256("0000034e77e71d7fe68d34a27996fae8b6b070d615bbe303d0e908e6119497c9"))
    (200, uint256("00000e348f133435e5d4a90aca60d0d03fdfe735099913dc31b85a744d9ca14f"))
    (250, uint256("68f6fd4ac0dab389e35d28eb504fe5b0ebfd2e38a8303fe89f4b53b43a4244a3"))
    (300, uint256("996caec96f44421aa76ef0e824d4522fa1c6768385a1ac9a531cfec3c14c611f"))
    (2116, uint256("5da3b214c14cbc3b8347b3e369a7125192330d68b40f8e167115833b570810da"))
    (2636, uint256("4b71c161f0a6a05d7850234e0fbfca4718d17c4f818125dc9eaa48ffe1af8650"))
    (10000, uint256("dfcc0977b332433c8c5b383d2562640a2fb38275104231a0e0bf9c747d283563"))
    (20000, uint256("d3d39e4ec818285f9e08201ddbecb472b24070a2737cb63b0591fe07da5bf154"))
    (30000, uint256("c36924a7fb1afc66980385805efd2c804ffd866bb5a3c402e3e25d2898364d09"))
    (40000, uint256("6bc969b81cadaa9f58c823708fb341b1cba92726f4054cf822b79d2f1632c58a"))
    (50000, uint256("f475f1d2c0bec2eebef0028b7a0cdcdc8d43d173b7c4651e176cea5b329e2437"))
    (60000, uint256("d8968ba07c853b3aff30613158c5798ff42503389478708117ff5c48db062774"))
    (61808, uint256("e737f1fe02e653fdcd1c055b41da6e7a701554e38a6fd01d2d0433a3be7df6b1"))
    (70000, uint256("6426b7297b99ac995e161317d9c9cd73e3bb29775c355c485a699c875e82e363"))
    (80000, uint256("f58bcef91ec110f96ce6f58486165bf6c795f0dd8d56763225fcc8d28ed58785"))
    (90000, uint256("c8f6dff95953bf54bedc17145f16ada4cb16f51d734c35b53792a7f4a4f3056d"))
    (100000, uint256("c53bd3ce1d7c07fd48ac05f67e1ae6363533e0455c791f1df734e9081fd44062"))
    (110000, uint256("aeeb97fe7b4374cf838d696b7f9b82bed0b6815677421a12f22cf51bceb53f54"))
    (120000, uint256("71f5b88c4b85649faf22c20f24e9a0e7f7d1420e800bea4cd7f46d415be619c3"))
    (124600, uint256("f20dd87ad0bfbc35288c3135bac5f49ac70b235279a5e2116be7cc4ea7758793"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1557234737, // * UNIX timestamp of last checkpoint block
    251781,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    100        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538651638,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1538651638,
    0,
100};


class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xd8;
        vAlertPubKey = ParseHex("04402a5f3465fd930b48f68034e4ed717d47fd801570eb24c1b4ff271bfe016f016265ab58b73de89bae37b7a8498f1c3a6ee590c1b1b4dad8a057254b79f7e7cd");
        nDefaultPort = 10555;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // KSOC starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nLastPOWBlock = 200;
        nTargetTimespan = 2 * 60;
        nTargetSpacing = 2 * 60;
        nMaturity = 100;
        nMaxMoneyOut = 1000000000 * COIN;
        nMasternodeCountDrift = 20;
        nMinerThreads = 0;
        nModifierUpdateBlock = 0;

        nEnforceBlockUpgradeMajority = 201;
        nRejectBlockOutdatedMajority = 202;
        nToCheckBlockUpgradeMajority = 203;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "NY Times 10/Oct/2018 Hurricane Michael Live Updates: Storm Upgraded to Category 3";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04ab8dbce32c7daa6ff8a7d43794de3402a4e4f8909140d9d687624db0899ccc532c86b2310a9c10ac35fc3c7fdd5e7d5997928c7dfdebc568039790f6c141c0e8") << OP_CHECKSIG;

        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1539704377;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 57612;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000c42789aa13befe57776f7ed976779858369e180cd0cf982f37a3767fe6f"));
        assert(genesis.hashMerkleRoot == uint256("0xdc4ccfefda206a88916d71e36f9dec148c9b22171f28d8de9c6ec6287b715918"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 107);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("ksoc-network.com", "seeds.ksoc-network.com"));
        vSeeds.push_back(CDNSSeedData("kicksoccercoin.com", "seeds.ksoc.kicksoccercoin.com"));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nStartMasternodePayments = 1; // from start

        nPoolMaxTransactions = 3;
        strSporkKey = "043e75dc3d44e52f40d4b4823807bfeedd5a8d07140d43a7278bef1b432a3f1b25eff51244106f010cf36671226ec124b9467cae8c38b624b11e11f477c11f4526";
        strObfuscationPoolDummyAddress = "KLPBfsxXEyNJWTbnpC8Fm9sxbceLDBCvnE";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x10;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x06;
        vAlertPubKey = ParseHex("04821ff72e55171b6e209661e557d0356be1d401e7e04d928dfa9406a711c759c4818584caa8cf4ba392688c108ce8b2e2e643bcab07d9cd279f28ec9f4a10d6cb");
        nDefaultPort = 11555;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // KSOC: 2 minute
        nTargetSpacing = 2 * 60;  // KSOC: 2 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1539704377;
        genesis.nNonce = 175582;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009589c38406c12f38ae758264a3374941d1daaf4996bbd523a30e4ea00d3"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ksoc addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ksoc script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet ksoc BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet ksoc BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        vFixedSeeds.clear();
        vSeeds.clear();

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0427a26d2003ef77437c6287041e81812687077dbbb4a2243229756b926ae49fb1c858f7a671d081f51755cd6d53ed8540b90a25984165d939d701666ecd95995b";
        strObfuscationPoolDummyAddress = "xzctEamdG1LveaMEsoV4WWFjSHeg7g3nBE";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        nDefaultPort = 11557;
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xd9;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 2 * 60; // ksoc: 2 minutes
        nTargetSpacing = 2 * 60;  // ksoc: 2 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1539704377;
//        genesis.nBits = 0x207fffff;
        genesis.nNonce = 418712;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001540d2f01047b7e38d2f8b670669a0d46987828d44eacc0672ab84f6b01"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 11559;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
