#include "rhdiff.h"
#include <fstream>
#include <iostream>

int main()
{
    std::fstream newFile;
    std::fstream sigFile;
    std::vector<uint8_t> data;

    newFile.open("../../new_file", std::ios::ate | std::ios::in | std::ios::binary);
    data.resize(newFile.tellg());
    newFile.seekg( 0, std::ios_base::beg );
    newFile.read((char*)data.data(), data.size());
    newFile.close();

    sigFile.open("../../signature_file", std::ios::ate | std::ios::in | std::ios::binary);
    size_t dataSize = sigFile.tellg();
    uint8_t* sigData = reinterpret_cast<uint8_t*>(malloc(dataSize));
    sigFile.seekg( 0, std::ios_base::beg );
    sigFile.read((char*)sigData, dataSize);
    sigFile.close();

    rhdiff::signature::SignatureT signature(sigData);
    rhdiff::Delta delta;
    delta(signature, data);

    return 0;
}