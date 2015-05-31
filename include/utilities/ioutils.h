#ifndef IOUTILS_H
#define IOUTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iterator>

namespace IOUtils
{
    bool getFileContents(std::vector<char> &fileBuffer, std::string filePath);
}

#endif
