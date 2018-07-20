// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
//#include "arith_uint256.h"
#include <assert.h>

#include "chainparamsseeds.h"
static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Dec. 31th 2013 Japan, The winning numbers of the 2013 Year-End Jumbo Lottery:23-130916";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams: public CChainParams {
public:
	CMainParams() {

		strNetworkID = "main";
//		uint32_t i=0;
//		bool fNegative;
//		bool fOverflow;
		genesis = CreateGenesisBlock(1532004360,792719, 0x1e0ffff0, 1, 20 * COIN);
//		while (true) {
//			genesis = CreateGenesisBlock(1532004360,++i, 0x1e0ffff0, 1, 20 * COIN);
//		arith_uint256 bnTarget;
//
//		bnTarget.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
//		if (UintToArith256(genesis.GetPoWHash(true)) > bnTarget) {
//		//	std::cout << " nonce not correct  \n";
//			std::cout << i << " ";
//		}
//		else {
//			std::cout << " nonce found  " << i << "\n";
//					break;
//		}
//		}
		consensus.nSubsidyHalvingInterval = 1051200;
		consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
		consensus.BIP34Hash = genesis.GetHash();
		consensus.BIP65Height = -1;
		consensus.BIP66Height = -1;
		consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
		consensus.nPowTargetTimespan = 1.1 * 24 * 60 * 60; // 1.5 days
		consensus.nPowTargetSpacing = 2 * 60; // 1.5 minutes
		consensus.nPowTargetTimespanDigisheld = 1.5 * 60;
		consensus.fPowAllowMinDifficultyBlocks = false;
		consensus.fPowNoRetargeting = false;
		consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
		consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008


		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1531990480972; //19 Jul 2018
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1563490800000;

		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1531990480972;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1563490800000;

		// The best chain should have at least this much work.
		consensus.nMinimumChainWork = uint256S("0x00");

		// By default assume that the signatures in ancestors of this block are valid.
		consensus.defaultAssumeValid = uint256S("0x00");

		// Hardfork params
		nSwitchKGWblock = -1;
		nSwitchDIGIblock = -1;
		nSwitchLyra2REv2_DGW = 0;
		/**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
		pchMessageStart[0] = 0xfa;
		pchMessageStart[1] = 0xbf;
		pchMessageStart[2] = 0xb5;
		pchMessageStart[3] = 0xda;
		nDefaultPort = 8232;
		nPruneAfterHeight = 100000;

		consensus.hashGenesisBlock = genesis.GetHash();
		std::cout  << " genesis " << consensus.hashGenesisBlock.GetHex()  << "\n";
		assert(
				consensus.hashGenesisBlock
						== uint256S(
								"0x23cb2bd72b400520d2cc6abab6a59b57447e33aa349915df8b481ec841754f40"));
		//        assert(genesis.hashMerkleRoot == uint256S("0x97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9"));
		vSeeds.emplace_back("dns.hmncoin.info", false);
		vSeeds.emplace_back("dns.hmncoin.net", false);
		vSeeds.emplace_back("dns.hmncoin.org ", false);

		fDefaultConsistencyChecks = true;
		fRequireStandard = false;
		fMineBlocksOnDemand = true;

		checkpointData =
				(CCheckpointData ) {
								{
										{ 0,
												uint256S(
														"3121f07c5791eea22d053e5a5fcfef0032a2ed38b434a7a53639c63b2ca74718") }, } };

		chainTxData = ChainTxData { 0, 0, 0 };

	vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 117);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
		base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

		base58Prefixes[OLD_SECRET_KEY] = std::vector<unsigned char>(1, 239);
	}
	// Note that of those with the service bits flag, most only support a subset of possible options

};

/**
 * Testnet (v4)
 */
class CTestNetParams: public CChainParams {
public:
	CTestNetParams() {
		strNetworkID = "test";
		consensus.nSubsidyHalvingInterval = 1051200;
		consensus.BIP34Height = 0;
		consensus.BIP34Hash =
				uint256S(
						"a2b106ceba3be0c6d097b2a6a6aacf9d638ba8258ae478158f449c321061e0b2");
		consensus.BIP65Height = -1;
		consensus.BIP66Height = -1;
		consensus.powLimit =
				uint256S(
						"00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
		consensus.nPowTargetTimespan = 1.1 * 24 * 60 * 60; // 1.1 days
		consensus.nPowTargetSpacing = 2 * 60; // 1.5 minutes
		consensus.nPowTargetTimespanDigisheld = 1.5 * 60;
		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.fPowNoRetargeting = false;
		consensus.nRuleChangeActivationThreshold = 75; // 75% for testchains
		consensus.nMinerConfirmationWindow = 100; // nPowTargetTimespan / nPowTargetSpacing
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime =
				1199145601; // January 1, 2008
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout =
				1230767999; // December 31, 2008

		// Deployment of BIP68, BIP112, and BIP113.
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime =
				1488931200; // March 8, 2017
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1520467200; // March 8, 2018

		// Deployment of SegWit (BIP141, BIP143, and BIP147)
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime =
				1488931200; // March 1, 2017
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout =
				1520467200; // March 8, 2018
		// The best chain should have at least this much work.
		consensus.nMinimumChainWork =
				uint256S(
						"0x00000000000000000000000000000000000000000000000000001b57ceb7b646");

		// By default assume that the signatures in ancestors of this block are valid.
		consensus.defaultAssumeValid =
				uint256S(
						"0x9b4de3d23148a6a7d25a991b4353b98ab0585813575ddfcf68354eef7eee1380"); //160675

		pchMessageStart[0] = 0xfd;
		pchMessageStart[1] = 0xd2;
		pchMessageStart[2] = 0xc8;
		pchMessageStart[3] = 0xf1;

		// Hardfork params
		nSwitchKGWblock = 10;
		nSwitchDIGIblock = 20;
		nSwitchLyra2REv2_DGW = 30;

		nDefaultPort = 19403;
		nPruneAfterHeight = 1000;
		vAlertPubKey =
				ParseHex(
						"04887665070e79d20f722857e58ec8f402733f710135521a0b63441419bf5665ba4623bed13fca0cb2338682ab2a54ad13ce07fbc81c3c2f0912a4eb8521dd3cfb");

		genesis = CreateGenesisBlock(1488924140, 2122860, 0x1e0ffff0, 1,
				50 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(
				consensus.hashGenesisBlock
						== uint256S(
								"0x4e30d0d53355be41a8c5633a06c4683ee603a844f411667ab12c94b00389784f"));
		assert(
				genesis.hashMerkleRoot
						== uint256S(
								"0x35e405a8a46f4dbc1941727aaf338939323c3b955232d0317f8731fe07ac4ba6"));

		vFixedSeeds.clear();
		vSeeds.clear();
		// nodes with support for servicebits filtering should be at the top
		vSeeds.emplace_back("testnet-dnsseed.hostmasternode.com", false);

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 117);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
		base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

		base58Prefixes[OLD_SECRET_KEY] = std::vector<unsigned char>(1, 239);

		vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test,
				pnSeed6_test + ARRAYLEN(pnSeed6_test));

		fDefaultConsistencyChecks = false;
		fRequireStandard = false;
		fMineBlocksOnDemand = false;

		checkpointData =
				(CCheckpointData ) {
								{
										{ 0,
												uint256S(
														"0xa2b106ceba3be0c6d097b2a6a6aacf9d638ba8258ae478158f449c321061e0b2") }, } };

		chainTxData = ChainTxData {
		// Data as of block 4bf184706cb65e6571185b2dae8ee95783567ecd18cdc6c1506fc9f281c1bb6a (height 160000)
				1517992899, 161419, 0.010735 };

	}
};

/**
 * Regression test
 */
class CRegTestParams: public CChainParams {
public:
	CRegTestParams() {
		strNetworkID = "regtest";
		consensus.nSubsidyHalvingInterval = 150;
		consensus.BIP34Height = -1; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
		consensus.BIP34Hash = uint256();
		consensus.BIP65Height = -1; // BIP65 activated on regtest (Used in rpc activation tests)
		consensus.BIP66Height = -1; // BIP66 activated on regtest (Used in rpc activation tests)
		consensus.powLimit =
				uint256S(
						"7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
		consensus.nPowTargetTimespan = 1.1 * 24 * 60 * 60; // 1.5 days
		consensus.nPowTargetSpacing = 2 * 60; // 1.5 minutes
		consensus.nPowTargetTimespanDigisheld = 1.5 * 60;
		consensus.fPowAllowMinDifficultyBlocks = true;
		consensus.fPowNoRetargeting = true;
		consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
		consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout =
				999999999999ULL;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout =
				999999999999ULL;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
		consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout =
				999999999999ULL;

		// The best chain should have at least this much work.
		consensus.nMinimumChainWork = uint256S("0x00");

		// By default assume that the signatures in ancestors of this block are valid.
		consensus.defaultAssumeValid = uint256S("0x00");

		// Hardfork params
		nSwitchKGWblock = 20;
		nSwitchDIGIblock = 40;
		nSwitchLyra2REv2_DGW = 60;

		pchMessageStart[0] = 0xfa;
		pchMessageStart[1] = 0xbf;
		pchMessageStart[2] = 0xb5;
		pchMessageStart[3] = 0xda;
		nDefaultPort = 20444;
		nPruneAfterHeight = 1000;

		genesis = CreateGenesisBlock(1296688602, 1, 0x207fffff, 1, 50 * COIN);
		consensus.hashGenesisBlock = genesis.GetHash();
		assert(
				consensus.hashGenesisBlock
						== uint256S(
								"0x7543a69d7c2fcdb29a5ebec2fc064c074a35253b6f3072c8a749473aa590a29c"));
//        assert(genesis.hashMerkleRoot == uint256S("0x97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9"));

		vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
		vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

		fDefaultConsistencyChecks = true;
		fRequireStandard = false;
		fMineBlocksOnDemand = true;

		checkpointData =
				(CCheckpointData ) {
								{
										{ 0,
												uint256S(
														"3121f07c5791eea22d053e5a5fcfef0032a2ed38b434a7a53639c63b2ca74718") }, } };

		chainTxData = ChainTxData { 0, 0, 0 };

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 117);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
		base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

		base58Prefixes[OLD_SECRET_KEY] = std::vector<unsigned char>(1, 239);
	}
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
	assert(globalChainParams);
	return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain) {
	if (chain == CBaseChainParams::MAIN)
		return std::unique_ptr < CChainParams > (new CMainParams());
	else if (chain == CBaseChainParams::TESTNET)
		return std::unique_ptr < CChainParams > (new CTestNetParams());
	else if (chain == CBaseChainParams::REGTEST)
		return std::unique_ptr < CChainParams > (new CRegTestParams());
	throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network) {
	SelectBaseParams(network);
	globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime,
		int64_t nTimeout) {
	globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
