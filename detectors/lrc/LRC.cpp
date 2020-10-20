#include "LRC.h"
#include "../util.h"
#include <vector>
#include <string>
#include <iostream>
#include <cassert>

LRC::LRC(int wordSize, int wordsPerFrame) {
    this->wordSize = wordSize;
    this->dataWordsPerFrame = wordsPerFrame - 1;
    std::cout << "LRC initialized with dataWordSize = " << wordSize << " and " << wordsPerFrame - 1 << " dataWords and 1 pairity word per frame.\n";
}

bool LRC::init(int wordSize, int wordsPerFrame) {
    if (hasData())
        return false;
    this->wordSize = wordSize;
    this->dataWordsPerFrame = wordsPerFrame - 1;
    std::cout << "LRC initialized with dataWordSize = " << wordSize << " and " << wordsPerFrame - 1 << " dataWords and 1 pairity word per frame.\n";
    return true;
}

bool LRC::hasData() {
    return data.size();
}

std::string LRC::calculateParityWord(std::vector<std::string> wordsVec) {
    assert(wordsVec.size() == dataWordsPerFrame);
    std::string pairityWord;
    for (int i = 0; i < wordSize; ++i) {
        unsigned int count = 0;
        for (int j = 0; j < dataWordsPerFrame; ++j) {
            if (wordsVec[j][i] == '1') {
                ++count;
            }
        }
        pairityWord += count % 2 ? "1" : "0";
    }
    return pairityWord;
}

bool LRC::setData(std::string data) {
    if (hasData())
        return false;

    unsigned int dataLen = data.size();
    unsigned int wordCount = dataLen / wordSize;
    unsigned int frameCount = wordCount / dataWordsPerFrame;
    unsigned int dataBitsPerFrame = dataWordsPerFrame * wordSize;
    unsigned int paddLen = ((dataBitsPerFrame * frameCount) != dataLen) ? ((frameCount + 1) * dataBitsPerFrame - dataLen) : 0;
    if (paddLen) {
        std::cout << "Required padding length = " << paddLen << '\n';
        data += std::string(paddLen, '0');
        std::cout << "Data after padding: " << data << '\n';
        dataLen = data.size();
        wordCount = dataLen / wordSize;
        frameCount = wordCount / dataWordsPerFrame;
    }
    std::vector <std::string> words;
    for(int i = 0; i < wordCount; ++i) {
        words.push_back(data.substr(i * wordSize, wordSize));
        if ((i + 1) % dataWordsPerFrame == 0) {
            std::string pairityWord = calculateParityWord(words);
            words.push_back(pairityWord);
            this->data.push(words);
            words.clear();
        }
    }
    return true;
}

std::string LRC::getFrame() {
    if (hasData()) {
        std::vector<std::string> frame = this->data.front();
        this->data.pop();
        return stringVectorToString(frame);
    }
    std::string temp;
    return temp;
}

bool LRC::testFrame(std::string frame) {
    std::vector<std::string> words;
    for (int i = 0; i < dataWordsPerFrame; ++i) {
        words.push_back(frame.substr(i * wordSize, wordSize));
    }
    std::string pairityWord = calculateParityWord(words);
    return pairityWord == frame.substr(dataWordsPerFrame * wordSize, wordSize);
}
