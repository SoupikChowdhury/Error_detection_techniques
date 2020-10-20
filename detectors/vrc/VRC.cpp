#include "VRC.h"
#include <string>
#include <cassert>
#include <iostream>

std::string VRC::calculatePairity(std::string input) {
    assert(input.size() == dataWordSize);
    int count = 0;
    for (auto x : input) {
        if (x == '1')
            ++count;
    }
    return (count % 2) ? "1" : "0" ;
}

VRC::VRC(int wordSize) {
    this->dataWordSize = wordSize - 1;
    std::cout << "VRC initialized with wordSize = " << wordSize << " of which last bit is pairity bit.\n";
}

bool VRC::init(int wordSize) {
    if (hasData())
        return false;
    this->dataWordSize = wordSize - 1;
    std::cout << "VRC initialized with wordSize = " << wordSize << " of which last bit is pairity bit.\n";
    return true;
}

bool VRC::hasData() {
    return (this->data.size() > 0);
}

bool VRC::setData(std::string data) {
    if (hasData())
        return false;

    unsigned int dataLen = data.size();
    unsigned int wordcount = dataLen / dataWordSize;
    wordcount = ((wordcount * dataWordSize) == dataLen) ? wordcount : wordcount + 1;
    unsigned int paddLen = (wordcount * dataWordSize) - dataLen;
    if (paddLen) {
        data += std::string(paddLen, '0');
        std::cout << "Padded Data: " << data << " with padding length: " << paddLen << '\n';
    }
    for (unsigned int i = 0; i < wordcount; ++i) {
        std::string substr =data.substr(i * dataWordSize, dataWordSize);
        substr += calculatePairity(substr);
        this->data.push(substr);
    }
    return true;
}

std::string VRC::getWord() {
    std::string str;
    if (hasData()) {
        str = this->data.front();
        this->data.pop();
    }
    return str;
}

bool VRC::testWord(std::string word) {
    std::string substr = word.substr(0, dataWordSize);
    substr += calculatePairity(substr);
    return substr == word;
}
