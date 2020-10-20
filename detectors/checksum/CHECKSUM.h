#ifndef ERRORDETECTOR_CHECKSUM_H
#define ERRORDETECTOR_CHECKSUM_H

#include <queue>
#include <vector>
#include <string>
#include <utility>

class CHECKSUM {
    int wordSize;
    int dataWordsPerFrame;
    std::queue<std::vector<std::string>> data;
    std::pair<char, bool> sumBitPosition(std::string a, std::string b, int pos, bool carry);
    std::string addUsing1sComplement(std::string a, std::string b);
    std::string calculateChecksum(std::vector<std::string> data);
    std::string onesComplement(std::string data);
public:
    CHECKSUM(int wordSize, int wordsPerFrame);
    bool init(int wordSize, int wordsPerFrame);
    bool hasData();
    bool setData(std::string data);
    std::string getFrame();
    bool testFrame(std::string);
};


#endif //ERRORDETECTOR_CHECKSUM_H
