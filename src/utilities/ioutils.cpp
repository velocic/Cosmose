#include <utilities/ioutils.h>

bool IOUtils::getFileContents(std::vector<unsigned char> &fileBuffer, std::string filePath) {
    std::ifstream inFileStream(filePath, std::ios::binary);

    if (!inFileStream) {
        return false;
    }

    inFileStream.seekg(0, std::ios::end);
    std::streampos fileLength = inFileStream.tellg();
    inFileStream.seekg(0, std::ios::beg);

    fileBuffer.resize(fileLength);
    inFileStream.read(&fileBuffer[0], fileLength);

    return true;
}
