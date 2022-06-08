#include "rhddelta.h"
#include "rhdiff.h"
#include <algorithm>

namespace rhdiff::delta
{
    void Delta::operator()(const rhdiff::signature::SignatureT& signature, const std::vector<uint8_t>& data)
    {
        std::vector<std::pair<uint64_t, rhdiff::data::hashT>> sigChunks;
        if(!signature.chunks(sigChunks))
            return;

        const uint64_t chunkSize = signature.header()->m_chunkSize;
        
        std::vector<rhdiff::Chunk> newChunks = { rhdiff::Chunk{ (uint8_t*)data.data(), chunkSize } };

        newChunks.front().hash();
        for(size_t idx = 0; idx < data.size()-chunkSize; ++idx)
        {
            newChunks.emplace_back( newChunks.back().nextChunk() );
        }

        size_t sigPos = 0;
        size_t newPos = 0;
        size_t delta_pos = 0;
        while(true)
        {
            if(newPos == newChunks.size())
                break;

            if(sigPos < sigChunks.size() && newChunks[newPos].hashValue == sigChunks[sigPos].second)
            {
                // Match
                ++sigPos;
                ++newPos;
                ++delta_pos;
                continue;
            }

            //TODO
        }
    }
}
