#ifndef RHDIFF_DATA_H
#define RHDIFF_DATA_H

#include <cstdint>
#include <vector>
#include <queue>
#include <memory>
#include <cmath>

namespace rhdiff
{
    namespace data
    {
        typedef uint64_t hashT;
        typedef uint8_t* dataT;
        typedef uint64_t dataSizeT;

        /*! \brief Self aware class for chunk data. Data of all sequenced chunks must be allocated continuously
            */
        class Chunk
        {
        public:
            static std::vector<hashT> powerVec;

            /*! \brief Create new chunk of data.
                \param data - Base data in binary format.
                \param dataLen - Lenght of data pointed by data param, must be greater than 0.
            */
            Chunk(dataT data, dataSizeT dataLen);

            /*! \brief Calculates hash value for current chunk of data.
            */
            void hash();

            /*! \brief Calculates hash value for current chunk of data, based on hash of previous chunk.
                \param data - Base data in binary format.
                \param n - Do not use, not implemented yet. Step we want to move window for every chunk.
            */
            void hash(hashT prevHash, size_t n=1);

            /*! \brief Returns next chunk of data with calculated hash value.
                \param n - Do not use, not implemented yet. Step we want to move window for every chunk.
            */
            Chunk nextChunk(size_t n=1) const;

            /*! \brief Returns hash value of current chunk.
                \return value of hash calculated for this chunk of data,
                0 indicates eiter hash was not yet caluclated or hash for this chunk is 0 (do not rely on 0 return).
            */
            hashT hashValue() const;

            /*! \brief Returns data of current chunk.
                \return pointer to data this chunk is operating on.
            */
            const dataT data() const;

            /*! \brief Returns lenght of this chunks data
                \return Value od data length.
            */
            dataSizeT dataLen() const;

            bool operator==(const Chunk& other) const;

        private:
            hashT power(dataSizeT index);

            hashT m_hash;
            dataT m_data;
            dataSizeT m_dataLen=0;

            static constexpr uint64_t HASH_BASE_P = 31;
            static constexpr uint64_t HASH_PRIME_M = 1e9 + 9;
        };
    }
    
} // namespace RHDIFF_


#endif // DATA_H