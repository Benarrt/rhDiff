#ifndef RHDDELTA_H
#define RHDDELTA_H

#include "rhdsignature.h"

namespace rhdiff::delta
{
    class Delta
    {
        public:
            /*! \brief Create delta for signature data nad new file data.
                \param signature - Signature generate for base file.
                \param data - Binary data of new file.
            */
            void operator()(const rhdiff::signature::SignatureT& signature, const std::vector<uint8_t>& data);
    };
}


#endif // RHDDELTA_H