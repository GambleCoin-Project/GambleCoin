// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
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
    (0, uint256("00000ad0f31d7a9e96b81950300618be80c745f099703dfc1f8f7811141384ed"))
    (102, uint256("00000024d01877d42d4090b4645c976f93196cd9f1fd6092f938d3926a9cbe85"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1520117660, // * UNIX timestamp of last checkpoint block
    103,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000913ee74f5160ac5de4ed92e5c8873886fde415978f79e20202fcf2435cc"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1520273549,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

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
        pchMessageStart[0] = 0x90;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xad;
        pchMessageStart[3] = 0x19;
        vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nDefaultPort = 12000;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // GAMBLECOIN starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 5 * 90; // GAMBLECOIN: 7.5 minutes
        nTargetSpacing = 1 * 90;  // GAMBLECOIN: 90 seconds
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 15600000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 0;
        nZerocoinStartHeight = 22;
        nZerocoinStartTime = 1520288156; // Monday, 5 March 2018 22:15:56
        nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 0; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 0; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "28/02/2018 Bill Gates says cryptocurrencies causes deaths";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 30 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1520117660;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 19232;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000083601e509636901be6882bf942c36c3110bb77365acce6cb1bb5af3e266"));
        assert(genesis.hashMerkleRoot == uint256("0x0e8b5b16874da8f82dc7463729f3f63964a5e6f5fea04f0d163e89ae6b9dd1d0"));

        // TODO
        vSeeds.push_back(CDNSSeedData("45.63.9.248", "45.63.9.248"));
        vSeeds.push_back(CDNSSeedData("149.28.58.153", "149.28.58.153"));
        vSeeds.push_back(CDNSSeedData("199.247.20.46", "199.247.20.46"));
        vSeeds.push_back(CDNSSeedData("95.179.155.34", "95.179.155.34"));
        vSeeds.push_back(CDNSSeedData("144.202.24.71", "144.202.24.71"));
        vSeeds.push_back(CDNSSeedData("45.63.64.91", "45.63.64.91"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed1.gamblecoin-info.com", 
                                      "gmcn-dnsseed1.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed2.gamblecoin-info.com", 
                                      "gmcn-dnsseed2.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed3.gamblecoin-info.com", 
                                      "gmcn-dnsseed3.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed4.gamblecoin-info.com", 
                                      "gmcn-dnsseed4.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed5.gamblecoin-info.com", 
                                      "gmcn-dnsseed5.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed6.gamblecoin-info.com", 
                                      "gmcn-dnsseed6.gamblecoin-info.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed1.gamblecoin-casino.com", 
                                      "gmcn-dnsseed1.gamblecoin-casino.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed2.gamblecoin-casino.com", 
                                      "gmcn-dnsseed2.gamblecoin-casino.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed3.gamblecoin-casino.com", 
                                      "gmcn-dnsseed3.gamblecoin-casino.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed4.gamblecoin-casino.com", 
                                      "gmcn-dnsseed4.gamblecoin-casino.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed5.gamblecoin-casino.com", 
                                      "gmcn-dnsseed5.gamblecoin-casino.com"));
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed6.gamblecoin-casino.com", 
                                      "gmcn-dnsseed6.gamblecoin-casino.com"));
        // vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "gamblecoin.seed.fuzzbawls.pw"));     // Primary DNS Seeder from Fuzzbawls
        // vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "gamblecoin.seed2.fuzzbawls.pw"));    // Secondary DNS Seeder from Fuzzbawls
        // vSeeds.push_back(CDNSSeedData("coin-server.com", "coin-server.com"));         // Single node address
        // vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net")); // Single node address
        // vSeeds.push_back(CDNSSeedData("178.254.23.111", "178.254.23.111"));           // Single node address

        // GambleCoin address prefix is 'C'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
        // GambleCoin script address prefix is '8'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);
        // GambleCoin secret key prefix is 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 65);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "043585edf16b2d1680c53b4feee9f8b824f1f8eda11315fd781951b021c8d91385bb645e36c8b5498c3db288c0af6a48ecab44f73bf0ff0b378c631366c00cf6ec";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT

        /** Zerocoin */
        zerocoinModulus = "b04015c56b641b5627228efdd5c1d483e0b804f66fdf1a112c71d664a3348898a782419e8390276b55dc8724568b107b4e"
            "a94afc4d63e2b70ed6b0b598185ba001cc3d7f083a73bdac09960937047324cd6309636b21c39be122dc0ba57a643b4a46a34454453989a2"
            "e1dd25982d72017f3672b5aedb2be9631485ae827eb0e47323c77ce04c105f7c060f5b46e6e76eccf4a4b089b2d5eee11f1bc126f2d446c5"
            "2182c014dd7fc58cd5af7c7f8e796ddc8f5acc5a2df2924af65f2d560fb219ba3c1c09a1536b54d1b79cecb8e4c0917115feba8e90e62b74"
            "bbe023858f43fe6640aed5e53798027122d53b04ced34d9ab4e1697feb887be74ad72ef65d99c1cd8bd18ac67964cfe51dc32c8b99c0da61"
            "51bf0332c5e4a1e9a55a3450beb40ea0cdf5a161a0cd625392933e3455d26e9627760bacef4f1b26732ba28a1ab7ff702206d142263ff9ed"
            "600f20118b65ec8519844f35eaa6e87a6b95a7e923a71621f6e33675d31d787841a4951895e8ce37043ea292325d85b1d1d95bcbd56bc1";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
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
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0xfa;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 13000;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 5 * 90; // GAMBLECOIN: 7.5 minutes
        nTargetSpacing = 1 * 90;  // GAMBLECOIN: 90 seconds
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = 15600000 * COIN;
        nZerocoinStartHeight = 22;
        nZerocoinStartTime = 1520288156; // Monday, 5 March 2018 22:15:56
        nBlockEnforceSerialRange = 0; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 0; //Trigger a recalculation of accumulators GAMBLECOIN: This is not used
        nBlockFirstFraudulent = 0; //First block that bad serials emerged GAMBLECOIN: This is not used
        nBlockLastGoodCheckpoint = 0; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 0; //Start enforcing the invalid UTXO's

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1520273549; // Monday, 5 March 2018 18:12:29
        genesis.nNonce = 4080330;

        hashGenesisBlock = genesis.GetHash();
        // printf("%s\n", hashGenesisBlock.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x00000913ee74f5160ac5de4ed92e5c8873886fde415978f79e20202fcf2435cc"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("gmcn-dnsseed-testnet.wildgarlic.fun", "gmcn-dnsseed-testnet.wildgarlic.fun"));
        // vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "gamblecoin-testnet.seed.fuzzbawls.pw"));
        // vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "gamblecoin-testnet.seed2.fuzzbawls.pw"));
        // vSeeds.push_back(CDNSSeedData("s3v3nh4cks.ddns.net", "s3v3nh4cks.ddns.net"));
        // vSeeds.push_back(CDNSSeedData("88.198.192.110", "88.198.192.110"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet gamblecoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet gamblecoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet gamblecoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet gamblecoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet gamblecoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "045605a12a910328b1c104453c12dfe56cd0a407e17a73e8ab7db7f031ffb3f026186401fcd38c18f1b73c7db939952ce51710c673b97b41f65289bc43eacc2c20";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
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
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x9e;
        pchMessageStart[3] = 0x1c;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // GAMBLECOIN: 1 day
        nTargetSpacing = 1 * 90;        // GAMBLECOIN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        // printf("%s\n", hashGenesisBlock.ToString().c_str());
        assert(hashGenesisBlock == uint256("0x5d19b770edcf3c6efd13e99ba87eaaa9b159ba331c89b7d8bf3468864b97cb83"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

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
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

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
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
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
