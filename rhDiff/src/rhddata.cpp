#include "rhddata.h"
#include <cassert>
 
namespace rhdiff::data
{
    std::vector<hashT> Chunk::powerVec={1};
   
    Chunk::Chunk(dataT data, dataSizeT dataLen) : m_data(data), m_dataLen(dataLen), m_hash(0)
    {
        assert(dataLen>0);
        power(dataLen-1);
    }

    bool Chunk::operator==(const Chunk& other) const
    {
        return this->m_hash == other.hashValue();
    }

    hashT Chunk::hashValue() const
    {
        return m_hash;
    }

    const dataT Chunk::data() const
    {
        return m_data;
    }

    dataSizeT Chunk::dataLen() const
    {
        return m_dataLen;
    }

    void Chunk::hash()
    {
        m_hash = 0;
        for(size_t idx = 0; idx < m_dataLen; idx++)
        {
            m_hash += (m_data[idx]) * powerVec[idx];
            m_hash %= HASH_PRIME_M;
        }
    }

    void Chunk::hash(hashT prevHash, size_t n)
    {
        m_hash = 0;
        
        hashT prev_pow = pow(*(m_data-n), m_dataLen-1);
        m_hash = (prevHash - prev_pow) * HASH_BASE_P + m_data[m_dataLen-1];
        m_hash %= HASH_PRIME_M;
    }

    Chunk Chunk::nextChunk(size_t n) const
    {
        Chunk next(m_data+1, m_dataLen);
        next.hash(m_hash, n);
        return next;
    }

    hashT Chunk::power(dataSizeT index)
    {
        if(powerVec.size() > index)
        {
            return powerVec[index];
        }

        while(index > powerVec.size())
        {
            power(powerVec.size());
        }

        return powerVec.emplace_back( (powerVec[index-1] * HASH_BASE_P) % HASH_PRIME_M );
    }
}