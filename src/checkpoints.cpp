// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of // Yo dawg, this is the secret. Checkpoint 0 hash == Genesis block hash.
        (         0, uint256("0xd592e6110f92acc63899d45070221eaa5d75ec23950387d3d7595f6a61d178b2"))
        (        50, uint256("0x53f893c43e4a94d3350ed03cf30da535e8e14109db262ea31dd79d6f5f5cd022"))
        (       100, uint256("0x33b4eeb1abd2fe62d0c400c17fd3fc0adc89e8803c8a74cdc1efc5f9299c393b"))
		(      4000, uint256("0x3dd24e2bc22c030ceb0b4f85d6ca0b6d028ba80e25ac64da7b17f3db41917912"))
		(      4500, uint256("0x31aa7baf89ac8aae7ec7cd46a85602f3c3c9f77260f77e133ddd37db83a0200b"))
		(      5000, uint256("0x4b26ad750625d438e9455d909a91b6481924ea7d49ccc2a0626cbf1697256e0d"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
