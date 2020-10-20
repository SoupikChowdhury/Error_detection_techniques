#include "CHECKSUM.h"
#include "../util.h"
#include <iostream>

//#define DEBUG

CHECKSUM::CHECKSUM(int wordSize, int wordsPerFrame) {
    this->wordSize = wordSize;
    this->dataWordsPerFrame = wordsPerFrame - 1;
    std::cout << "CHECKSUM initialized with wordsize = " << wordSize << " and wordsPerFrame = " << wordsPerFrame << " of which last is checksum word.\n";
}

bool CHECKSUM::init(int wordSize, int wordsPerFrame) {
    if (hasData())
        return false;
    this->wordSize = wordSize;
    this->dataWordsPerFrame = wordsPerFrame - 1;
    std::cout << "CHECKSUM initialized with wordsize = " << wordSize << " and wordsPerFrame = " << wordsPerFrame << " of which last is checksum word.\n";
    return true;
}

bool CHECKSUM::hasData() {
    return data.size();
}

std::string CHECKSUM::getFrame() {
    if (hasData()) {
        std::vector<std::string> frame = this->data.front();
        this->data.pop();
        return stringVectorToString(frame);
    }
    std::string temp;
    return temp;
}

bool CHECKSUM::setData(std::string data) {
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
            std::string checksum = calculateChecksum(words);

#ifdef DEBUG
            for (auto x: words) std::cout << "Word = " << x  << '\n';
            std::cout << "Checksum = " << checksum << '\n';
#endif
            words.push_back(checksum);
            this->data.push(words);
            words.clear();
        }
    }
    return true;
}

bool CHECKSUM::testFrame(std::string frame) {
    if (frame.size() != (dataWordsPerFrame + 1) * wordSize) {
        std::cout << "Frame contains " << frame.size() << " bits, whereas it should contain " << (dataWordsPerFrame + 1) * wordSize << " bits.\n";
        return false;
    }
    std::vector<std::string> words;
    for (int i = 0; i <= dataWordsPerFrame; ++i) {
        words.push_back(frame.substr(i * wordSize, wordSize));
    }
    std::string res = words[0];
    for (int i = 1; i < dataWordsPerFrame + 1; ++i) {
        res = addUsing1sComplement(res, words[i]);
    }
    res = onesComplement(res);
    return res == std::string(wordSize, '0');
}

std::pair<char, bool> CHECKSUM::sumBitPosition(std::string a, std::string b, int pos, bool carry) {
    std::pair<char, bool> res;
    int count = 0;
    if (a[pos] == '1')  ++count;
    if (b[pos] == '1')  ++count;
    if (carry)  ++count;
    res.first = (count % 2) ? '1' : '0';
    res.second = (count > 1);
    return res;
}

std::string CHECKSUM::addUsing1sComplement(std::string a, std::string b) {
    std::string sum;
    bool carry = false;
    for (int pos = wordSize - 1; pos > -1; --pos) {
        std::pair<char, bool> temp = sumBitPosition(a, b, pos, carry);
        carry = temp.second;
        sum = temp.first + sum;
    }
#ifdef DEBUG
    std::cout << "  First : " << a << "\n  Second : " << b << "\n  Sum : " << sum << "\n  Sum size : " << sum.size() << '\n';
#endif
    if (carry) {
        std::string temp = std::string(wordSize - 1, '0') + '1';
        sum = addUsing1sComplement(sum, temp);
#ifdef DEBUG
        std::cout << "  Overflow of MSB, new sum : " << sum << "\n  Sum size : " << sum.size() << '\n';
#endif
    }
    return sum;
}

std::string CHECKSUM::onesComplement(std::string data) {
    std::string res;
    for (auto x : data) {
        res += (x == '1' ? "0" : "1");
    }
    return res;
}

std::string CHECKSUM::calculateChecksum(std::vector<std::string> data) {
    std::string res = data[0];
    for (int i = 1; i < dataWordsPerFrame; ++i) {
        res = addUsing1sComplement(res, data[i]);
    }
    res = onesComplement(res);
    return res;
}
