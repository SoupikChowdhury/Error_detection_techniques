#ifndef ERRORDETECTOR_LRC_H
#define ERRORDETECTOR_LRC_H

#include <string>
#include <queue>

class LRC {
    int wordSize;
    int dataWordsPerFrame;
    std::queue<std::vector<std::string>> data;
    std::string calculateParityWord(std::vector<std::string> wordsVec);
public:
    LRC(int wordSize, int wordsPerFrame);
    bool init(int wordSize, int wordsPerFrame); // return false if init failed, which happens if inputData is not empty
    bool hasData();
    bool setData(std::string data); // return false if data is not empty
    std::string getFrame();
    bool testFrame(std::string frame);
};


#endif //ERRORDETECTOR_LRC_H
