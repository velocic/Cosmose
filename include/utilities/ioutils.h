#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iterator>

namespace Utility
{
    namespace IOUtils
    {
        bool getFileContents(std::vector<unsigned char> &fileBuffer, std::string filePath);
    }
}

#endif
