#include "util.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>


std::string stringVectorToString(std::vector<std::string> vec) {
    std::string res;
    for (auto x : vec) {
        res += x;
    }
    return res;
}

std::string flipBits(std::string src, std::vector<unsigned int> pos) {
    for (auto x : pos) {
        if (0 < x && x < src.size()) {
            src[x] = src[x] == '1' ? '0' : '1';
        }
    }
    return src;
}

std::vector<std::string> convert2frames(std::string data, unsigned int wordsize, unsigned int wordsPerFrame) {
    unsigned int dataLen = data.size();
    unsigned int bitsPerFrame = wordsize * wordsPerFrame;
    int frameCount = dataLen / bitsPerFrame;
    std::vector<std::string> frames;
    if (dataLen != frameCount * bitsPerFrame) {
        std::cout << "Frame has wrong number of bits.\n";
        return frames;
    }
    for (int i = 0; i < frameCount; ++i) {
        frames.push_back(data.substr(i*bitsPerFrame, bitsPerFrame));
    }
    return frames;
}

std::vector<std::string> convert2words(std::string data, unsigned int wordsize) {
    unsigned int dataLen = data.size();
    int wordCount = dataLen / wordsize;
    std::vector<std::string> words;
    if (dataLen != wordCount * wordsize) {
        std::cout << "Data has wrong number of bits.\n";
        std::cout << "Datalen: " << dataLen << "\nWordSize: " << wordsize << '\n';
        return words;
    }
    for (int i = 0; i < wordCount; ++i) {
        words.push_back(data.substr(i*wordsize, wordsize));
    }
    return words;
}

std::string XOR(std::string a, std::string b) {
    std::string res;
    unsigned int aLen = a.size();
    unsigned int bLen = b.size();
    if (a != b) {
        int pad = aLen - bLen;
        if (pad > 0) {
            b = std::string(pad, '0') + b;
        } else {
            a = std::string(pad, '0') + a;
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        res += (a[i] == b[i] ? '0' : '1');
    }
    unsigned int pos_1 = res.find('1');
    if (pos_1 < res.size())
        res = res.substr(pos_1);
    return res;
}

std::string divisionUsingXor(std::string divisor, std::string dividend) {   // returns remainder
//    std::cout << "divisor : " << divisor << "\tdividend : " << dividend << '\n';
//    std::string t;
//    std::cin >> t;

    unsigned int pos_1 = 0;
    for (auto x : dividend) {
        if (x == '1')
            break;
        ++pos_1;
    }
    if (pos_1 >= dividend.size())
        return dividend;

    if (divisor.size() > dividend.size() || (divisor.size() == dividend.size() && dividend[0] == '0')) {
        return dividend;
    }
    unsigned int degDivisor = divisor.size() - 1;
    std::string div_1 = dividend.substr(0, divisor.size());
    std::string div_2 = dividend.substr(divisor.size());
    std::string temp;
    if (divisor[0] == dividend[0]) {
        temp = divisor;
    } else {
        temp = std::string(divisor.size(), '0');
    }
    div_2 = XOR(div_1, temp) + div_2;
    int i;
    for (i = 0; i < div_2.size(); ++i) {
        if (div_2[i] == '1')
            break;
    }
    if (i < div_2.size())
        div_2 = div_2.substr(i);
    return divisionUsingXor(divisor, div_2);
}

std::string readDataFromFile(std::string filepath) {
    std::string outData;
    std::ifstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cout << "File (" << filepath << ") does not exists.\n";
        return outData;
    }
    std::string line;
    while (getline(file, line)) {
        for (auto x : line) {
            if (x == '1' || x == '0')
                outData += x;
        }
    }
    file.close();
    return outData;
}

bool writeDataToFile(std::string data, std::string filepath, bool append) {
    std::ofstream file;
    if (append) {
        file.open(filepath, std::ios::out | std::ios::app);
    } else {
        file.open(filepath, std::ios::out);
    }
    if (file.is_open()) {
        file << data;
        file.close();
        return true;
    }
    return false;   // false if for some reason writing to file was unsuccessful
}

std::vector<unsigned int> generateRandomIntegers(unsigned int count, unsigned int start, unsigned int end) {
    std::vector<unsigned int> vec;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end);
    for (unsigned c = 0; c < count; ++c) {
        vec.push_back(dist(rng));
    }
    return vec;
}
