#ifndef ERRORDETECTOR_VRC_H
#define ERRORDETECTOR_VRC_H

#include <queue>
#include <string>

class VRC {
    int dataWordSize;
    std::queue<std::string> data;
    std::string calculatePairity(std::string input);
public:
    VRC(int wordSize);
    bool init(int wordSize);
    bool hasData();
    bool setData(std::string data);
    std::string getWord();
    bool testWord(std::string word);
};


#endif //ERRORDETECTOR_VRC_H
