//
// Created by prasenjit on 1/17/20.
//

#ifndef ERRORDETECTOR_CRC_H
#define ERRORDETECTOR_CRC_H

#include <string>
#include <queue>

const int PolynomialCount = 3;  // Update this value with the number of strings in below Polynomials string

const std::string Polynomials[] = {
        "11",   // x + 1
        "101",  // x2 + 1
        "10011",    // x4 + x + 1
        "11001",    // x4 + x3 + 1
        "110101",   // x5 + x4 + x2 + 1
};

void printPolynomial(unsigned int idx);

class CRC {
    unsigned int poly_idx;
    unsigned int dataBitsPerWord;
    unsigned int padding;
    std::queue<std::string> data;

    std::string division(std::string divisor, std::string dividend);
public:
    CRC(unsigned int dataLen, unsigned int idx = 0);
    bool init(unsigned int dataLen, unsigned int idx = 0);
    bool setData(std::string data);
    bool hasData();
    bool testWord(std::string word);
    std::string getWord();
};


#endif //ERRORDETECTOR_CRC_H
