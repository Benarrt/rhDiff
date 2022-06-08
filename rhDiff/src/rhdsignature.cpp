#include "rhdsignature.h"

namespace rhdiff::signature
{

    Signature::Signature(uint64_t chunkSize) : m_chunkSize(chunkSize)
    {
        
    }

    SignatureT Signature::operator()(const std::vector<uint8_t>& data)
    {
        SignatureHeaderT sigHeader(1, data.size(), m_chunkSize);
        std::vector<rhdiff::data::Chunk> chunks = { rhdiff::data::Chunk{ (uint8_t*)data.data(), m_chunkSize } };

        chunks.front().hash();
        for(size_t idx = 0; idx+m_chunkSize < data.size()-1; ++idx)
        {
            chunks.emplace_back( chunks.back().nextChunk() );
        }

        return SignatureT(&sigHeader, chunks);
    }


    SignatureT::SignatureT(uint8_t* data) : m_data(data)
    {

    }

    SignatureT::SignatureT(SignatureHeaderT* header, const std::vector<rhdiff::data::Chunk>& chunks)
    {
        header->m_signatureSize = sizeof(SignatureHeaderT) + chunks.size() * sizeof(rhdiff::data::hashT);

        m_data = reinterpret_cast<uint8_t*>(malloc(header->m_signatureSize));
        memcpy(m_data, header, sizeof(SignatureHeaderT));

        auto* chunkHashPtr = reinterpret_cast<rhdiff::data::hashT*>(m_data+sizeof(SignatureHeaderT));
        for(const auto& chunk : chunks)
        {
            *chunkHashPtr + chunk.hashValue();
            ++chunkHashPtr;
        }
    }

    SignatureT::SignatureT(SignatureT&& other) noexcept
    {
        other.m_data = m_data;
        m_data = nullptr;
    }

    SignatureT& SignatureT::operator=(SignatureT&& other) noexcept
    {
        m_data = other.m_data;
        other.m_data = nullptr;
        return *this;
    }

    SignatureT::~SignatureT()
    {
        if(m_data)
            delete m_data;
    }

    SignatureHeaderT* SignatureT::header() const
    {
        return reinterpret_cast<SignatureHeaderT*>(m_data);
    }

    bool SignatureT::chunks(std::vector<std::pair<uint64_t, rhdiff::data::hashT>>& output) const
    {
        if(!m_data)
            return false;

        output.clear();

        rhdiff::data::hashT* chunkHash = reinterpret_cast<rhdiff::data::hashT*>(m_data+sizeof(SignatureHeaderT));
        
        size_t index = 0;
        while(sizeof(SignatureHeaderT) + index * sizeof(rhdiff::data::hashT) < this->header()->m_signatureSize)
        {
            output.push_back({index, chunkHash[index]});
            ++index;
        }

        return true;
    }
}