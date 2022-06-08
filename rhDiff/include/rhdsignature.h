#ifndef RHDSIGNATURE_H
#define RHDSIGNATURE_H

#include "rhddata.h"
#include <cstring>

namespace rhdiff::signature
{
    #pragma pack(push,1)
    struct SignatureHeaderT
    {
        SignatureHeaderT(uint16_t version, uint64_t dataSize, uint64_t chunkSize) : m_version(version), m_dataSize(dataSize), m_chunkSize(chunkSize), m_signatureSize(0)
        {

        }

        uint16_t m_version;
        uint64_t m_dataSize;
        uint64_t m_chunkSize;
        uint64_t m_signatureSize;
    };
    #pragma pack(pop)

    struct SignatureT
    {
        SignatureT(SignatureHeaderT* header, const std::vector<rhdiff::data::Chunk>& chunks);
        SignatureT(uint8_t* data);

        SignatureT(const SignatureT&) = delete;
        SignatureT(SignatureT&& other) noexcept;
        SignatureT& operator=(const SignatureT&) = delete;
        SignatureT& operator=(SignatureT&& other) noexcept;

        ~SignatureT();

        SignatureHeaderT* header() const;
        bool chunks(std::vector<std::pair<uint64_t, rhdiff::data::hashT>>& output) const;

        uint8_t* m_data = nullptr;
    };

    class Signature
    {
        public:
            /*! \brief Create new signature genarting object with specified chunksize.
                \param chunkSize - Size of chunks used for generating signature
            */
            Signature(uint64_t chunkSize);

            /*! \brief Create signature for data.
                \param data - Base data in binary format, we want to calculte signature for. Should be bigger than chunk size.
                \param output - Output container in which we will put our calculated signature binary data.
                \return true calculation succeed
                false calculation failed 
            */
            SignatureT operator()(const std::vector<uint8_t>& data);

            private:
                uint64_t m_chunkSize = 1;
    };
}


#endif // RHDSIGNATURE_H