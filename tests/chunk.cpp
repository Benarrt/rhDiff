#include "rhdiff.h"
#include <string>
#include <unordered_map>
#include <iostream>

int main()
{
    std::string s1("Rolling hash works on the priciple that while finding the hash value of the next substring, the window is moved forward only by dropping one character and adding another.In this case character 'a' is removed from substring abc and character 'd' is added next to it to get the substring bcd.");
    std::string s2(s1);

    size_t len = s1.length();
    size_t chunkLen = 3;

    std::vector<rhdiff::Chunk> chunksS1 = { rhdiff::Chunk{ (uint8_t*)s1.data(), chunkLen } };
    std::vector<rhdiff::Chunk> chunksS2 = { rhdiff::Chunk{ (uint8_t*)s2.data(), chunkLen } };

    chunksS1.front().hash();
    chunksS2.front().hash();
    for(size_t idx = 0; idx < len-chunkLen; ++idx)
    {
        chunksS1.emplace_back( chunksS1.back().nextChunk() );
        chunksS2.emplace_back( chunksS2.back().nextChunk() );
    }

    for(size_t idx = 0; idx < chunksS1.size(); idx++)
    {
        if(chunksS1[idx] == chunksS2[idx])
            continue;

        return 1;
    }

    std::unordered_map<uint64_t, std::string> resHashes;
    for(const auto& chunk: chunksS1)
    {
        std::string dataStr;
        dataStr.append((char*)chunk.data(), chunk.dataLen());
        auto res = resHashes.emplace(chunk.hashValue(), dataStr);
        if(!res.second && res.first->second != dataStr)
        {
            std::cerr << "Duplicated hash: " << chunk.hashValue() << "\n" << dataStr << "/" << res.first->second << "\n";
            return 1;
        }
    }

    return 0;
}