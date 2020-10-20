#include "CRC.h"
#include "../util.h"
#include <string>
#include <iostream>
#include <queue>

void printPolynomial(unsigned int idx) {
    if (idx > PolynomialCount)
        return;
    std::cout << "POLYNOMIAL :\t";
    std::string poly = Polynomials[idx];
    unsigned int exp = poly.size() - 1;
    for (auto x : poly) {
        if (x == '1')
            std::cout << " + x^" << exp;
        --exp;
    }
    std::cout << '\n';
}

std::string CRC::division(std::string divisor, std::string dividend) {
    std::string res = divisionUsingXor(divisor, dividend);
//    std::cout << "CRCDiv: " << res << '\n';
//    std::string t;
//    std::cin >> t;
    int pad = divisor.size() - 1 - res.size();
//    std::cout << "pad : " << pad << '\n';
//    std::cin >> t;
    if (pad > 0) {
        res = std::string(pad, '0') + res;
//        std::cout << "CRCdiv after pad " << pad << "  = " << res << '\n';
//        std::cin >> t;
    }
//    std::cout << "CRCDiv: " << res << '\n';
//    std::cin >> t;
    return res;
}

CRC::CRC(unsigned int dataLen, unsigned int idx) {
    dataBitsPerWord = dataLen;
    poly_idx = idx;
    padding = Polynomials[idx].size() - 1;
    std::cout << "CRC initialized with polynomial index : " << idx << '\n';
    printPolynomial(idx);
}

bool CRC::init(unsigned int dataLen, unsigned int idx) {
    if (hasData())
        return false;
    dataBitsPerWord = dataLen;
    poly_idx = idx;
    padding = Polynomials[idx].size() - 1;
    std::cout << "CRC initialized with polynomial index : " << idx << '\n';
    printPolynomial(idx);
    return true;
}

bool CRC::hasData() {
    return data.size();
}

std::string CRC::getWord() {
    std::string res = data.front();
    data.pop();
    return res;
}

bool CRC::setData(std::string data) {
    if (hasData())
        return false;

    unsigned int dataLen = data.size();
    unsigned int wordCount = dataLen / dataBitsPerWord;
    int padLen = (dataLen - (wordCount * dataBitsPerWord)) == 0 ? 0 : (((wordCount + 1) * dataBitsPerWord) - dataLen);
    if (padLen) {
        data = data + std::string(padLen, '0');
        std::cout << "PadLen : " << padLen << "\nPadded Data: " << data << '\n';
        ++wordCount;
    }
    for (int i = 0; i < wordCount; ++i) {
        std::string word = data.substr((i * dataBitsPerWord), dataBitsPerWord);
        std::string dividend = word + std::string(padding, '0');
        std::string divisor = Polynomials[poly_idx];
        std::string remainder = division(divisor, dividend);
        // std::cout << "Word: " << word << "\tDividend: " << dividend << "\tRemainder: " << remainder << '\n';
        word = word + remainder;
        this->data.push(word);
        // std::cout << "CRC: Added data: " << word << '\n';
    }
    return true;
}

bool CRC::testWord(std::string word) {
    std::string divisor = Polynomials[poly_idx];
    if (word.size() < divisor.size())
        return false;

    std::string remainder = division(divisor, word);
//    std::string t;
//    std::cout << "got rem\n";
//    std::cin >> t;
    for (auto x : remainder) {
        if (x == '1')
            return false;
    }
    return true;
}
