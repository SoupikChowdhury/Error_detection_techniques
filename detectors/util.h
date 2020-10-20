//
// Created by prasenjit on 1/24/20.
//

#ifndef ERRORDETECTOR_UTIL_H
#define ERRORDETECTOR_UTIL_H

#include <string>
#include <vector>

std::string stringVectorToString(std::vector<std::string> vec);
std::string flipBits(std::string src, std::vector<unsigned int> pos);
std::vector<std::string> convert2frames(std::string data, unsigned int wordsize, unsigned int wordsPerFrame);
std::vector<std::string> convert2words(std::string data, unsigned int wordsize);
std::string XOR(std::string a, std::string b);
std::string divisionUsingXor(std::string divisor, std::string dividend);
std::string readDataFromFile(std::string filePath);
bool writeDataToFile(std::string data, std::string filepath, bool append=false);
std::vector<unsigned int> generateRandomIntegers(unsigned int count, unsigned int start, unsigned int end);

#endif //ERRORDETECTOR_UTIL_H
