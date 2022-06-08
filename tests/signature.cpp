#include "rhdiff.h"
#include <fstream>
#include <iostream>

int main()
{
    std::fstream baseFile;
    std::fstream sigFile;
    std::vector<uint8_t> data, output;
    baseFile.open("../../base_file", std::ios::ate | std::ios::in | std::ios::binary);

    data.resize(baseFile.tellg());
    baseFile.seekg( 0, std::ios_base::beg );
    baseFile.read((char*)data.data(), data.size());
    baseFile.close();

    rhdiff::Signature sig(128);
    auto signature = sig(data);
  
    if(signature.header()->m_version != 1)
        return 1;

    if(signature.header()->m_dataSize != 290)
        return 1;

    if(signature.header()->m_chunkSize != 128)
        return 1;

    if(signature.header()->m_signatureSize != 1322)
        return 1;

    if(reinterpret_cast<uint64_t*>(signature.m_data)[9] != 376154362)
        return 1;

    sigFile.open("../../signature_file", std::ios::trunc | std::ios::out | std::ios::binary);
    sigFile.write((char*)signature.m_data, signature.header()->m_signatureSize);
    sigFile.close();
    return 0;
}