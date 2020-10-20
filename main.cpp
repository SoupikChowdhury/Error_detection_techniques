#include <iostream>

#include "detectors/lrc/LRC.h"
#include "detectors/vrc/VRC.h"
#include "detectors/crc/CRC.h"
#include "detectors/checksum/CHECKSUM.h"
#include "detectors/util.h"

void LRC_testing();
void VRC_testing();
void CRC_testing();
void CHECKSUM_testing();
void ChecksumVsCrc();
void VrcVsCrc();
void allDetectErrors();

std::string inputFilepath;
std::string inputData;

void init() {
    inputFilepath = "/home/anwesha/Downloads/Sem 6/Networks/Lab/ASS1/ErrorDetector/input.txt";
    inputData = readDataFromFile(inputFilepath);
}


int main() {
    init();

    LRC_testing();
    std::cout << '\n';
    VRC_testing();
    std::cout << '\n'; 
    CRC_testing();
    std::cout << '\n'; 
    CHECKSUM_testing();
    
    std::cout << '\n';
    ChecksumVsCrc();
    std::cout << '\n';
    VrcVsCrc();
    std::cout << '\n';
    allDetectErrors();
    
    return 0;
}


void LRC_testing() {
    std::cout << "===== LRC Testing =====\n";
    const int wordSize = 8;
    const int wordsPerFrame = 4;
    LRC lrc(wordSize, wordsPerFrame);
    std::cout << "Input Data: " << inputData << "\tof length: " << inputData.size() << '\n';
    lrc.setData(inputData);
    std::string outData;
    unsigned int frameCount = 0;
    while (lrc.hasData()) {
        ++frameCount;
        std::string frame = lrc.getFrame();
        outData += frame;
        std::cout << "Frame " << frameCount <<  ": " << frame << '\n';
        std::cout << "Testing frame: " << (lrc.testFrame(frame) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << "Modifying Data...\n";
    std::vector<unsigned int> pos2flip = generateRandomIntegers(10, 1, outData.size());
    std::string modifiedData = flipBits(outData, pos2flip);
    std::vector<std::string> frames = convert2frames(modifiedData, wordSize, wordsPerFrame);
    for (auto x : frames) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing frame: " << (lrc.testFrame(x) ? "PASS" : "FAIL") << '\n';
    }
}

void VRC_testing() {
    std::cout << "===== VRC Testing =====\n";
    const int wordSize = 32;
    VRC vrc(wordSize);
    std::cout << "Input Data: " << inputData << "\tof length: " << inputData.size() << '\n';
    vrc.setData(inputData);
    unsigned int wordCount = 0;
    std::string outData;
    while (vrc.hasData()) {
        ++wordCount;
        std::string word = vrc.getWord();
        outData += word;
        std::cout << "Word " << wordCount << " : " << word << '\n';
        std::cout << "Testing word: " << ((vrc.testWord(word)) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << "Modifying Data...\n";
    std::vector<unsigned int> pos2flip = generateRandomIntegers(10, 1, outData.size());
    std::string modifiedData = flipBits(outData, pos2flip);
    std::vector<std::string> words = convert2words(modifiedData, wordSize);
    for (auto x : words) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((vrc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }
}

void CRC_testing() {
    std::cout << "===== CRC Testing =====\n";
    const int dataLen = 32;
    const int poly_idx = 4;
    const int poly_len = Polynomials[poly_idx].size();
    const int wordSize = dataLen + poly_len - 1;
    CRC crc(dataLen, poly_idx);
    //std::string data = "10101010101010101010";
    std::string data = inputData;
    std::cout << "Input Data: " << data << "\tof length: " << data.size() << '\n';
    crc.setData(data);
    unsigned int wordCount = 0;
    std::string outData;
    while (crc.hasData()) {
        ++wordCount;
        std::string word = crc.getWord();
        outData += word;
        std::cout << "Word " << wordCount << " : " << word << '\n';
        std::cout << "Testing word: " << ((crc.testWord(word)) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << "Modifying Data...\n";
    std::vector<unsigned int> pos2flip = generateRandomIntegers(10, 1, outData.size());
    std::string modifiedData = flipBits(outData, pos2flip);
    std::vector<std::string> words = convert2words(modifiedData, wordSize);
    for (auto x : words) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((crc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }
}

void CHECKSUM_testing() {
    std::cout << "===== CHECKSUM Testing =====\n";
    const int wordSize = 8;
    const int wordsPerFrame = 4;
    CHECKSUM checksum(wordSize, wordsPerFrame);
    std::cout << "Input Data: " << inputData << "\tof length: " << inputData.size() << '\n';
    checksum.setData(inputData);
    unsigned int frameCount = 0;
    std::string outData;
    while (checksum.hasData()) {
        ++frameCount;
        std::string frame = checksum.getFrame();
        outData += frame;
        std::cout << "Frame " << frameCount <<  ": " << frame << '\n';
        std::cout << "Testing frame: " << (checksum.testFrame(frame) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << "Modifying Data...\n";
    std::vector<unsigned int> pos2flip = generateRandomIntegers(10, 1, outData.size());
    std::string modifiedData = flipBits(outData, pos2flip);
    std::vector<std::string> frames = convert2frames(modifiedData, wordSize, wordsPerFrame);
    for (auto x : frames) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing frame: " << (checksum.testFrame(x) ? "PASS" : "FAIL") << '\n';
    }
}

void ChecksumVsCrc() {
    std::cout << "===== Checksum Vs CRC =====\n";
    std::string data = "1010101010";
    std::vector<unsigned int> pos2flip = { 9, 12, 13 };
    std::cout << "Data: " << data << "\nPositions to flip after processing: ";
    for (auto x : pos2flip) {
        std::cout << x << ", ";
    }
    std::cout << '\n';

    std::cout << "== CHECKSUM: ==\n";
    int wordSize = 8;
    int wordsPerFrame = 3;
    CHECKSUM checksum(wordSize, wordsPerFrame);
    checksum.setData(data);
    std::string checksumOut;
    while (checksum.hasData()) {
        checksumOut += checksum.getFrame();
    }
    std::cout << "Data after CHECKSUM: " << checksumOut << '\n';
    checksumOut = flipBits(checksumOut, pos2flip);
    std::cout << "Modified Data: " << checksumOut << '\n';
    std::vector<std::string> frames = convert2frames(checksumOut, wordSize, wordsPerFrame);
    for (auto x : frames) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing frame: " << (checksum.testFrame(x) ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "\n== CRC: ==\n";
    int dataLen = 10;
    int poly_idx = 2;
    int poly_len = Polynomials[poly_idx].size();
    wordSize = dataLen + poly_len - 1;
    CRC crc(dataLen, poly_idx);
    crc.setData(data);
    std::string crcOut;
    while (crc.hasData()) {
        crcOut += crc.getWord();
    }
    std::cout << "Data after CRC: " << crcOut << '\n';
    crcOut = flipBits(crcOut, pos2flip);
    std::cout << "Modified Data: " << crcOut << '\n';
    std::vector<std::string> words = convert2words(crcOut, wordSize);
    for (auto x : words) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((crc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
}

void VrcVsCrc() {
    std::cout << "===== VRC Vs CRC =====\n";
    std::string data = "1010101010";
    std::vector<unsigned int> pos2flip = { 9, 12, 13 };
    std::cout << "Data: " << data << "\nPositions to flip after processing: ";
    for (auto x : pos2flip) {
        std::cout << x << ", ";
    }
    std::cout << '\n';

    std::cout << "== VRC: ==\n";
    int wordSize = 16;
    VRC vrc(wordSize);
    vrc.setData(data);
    std::string vrcOut;
    while (vrc.hasData()) {
        vrcOut += vrc.getWord();
    }
    std::cout << "Data after VRC: " << vrcOut << '\n';
    vrcOut = flipBits(vrcOut, pos2flip);
    std::cout << "Modified Data: " << vrcOut << '\n';
    std::vector<std::string> words = convert2words(vrcOut, wordSize);
    for (auto x : words) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((vrc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "\n== CRC: ==\n";
    int dataLen = 10;
    int poly_idx = 2;
    int poly_len = Polynomials[poly_idx].size();
    wordSize = dataLen + poly_len - 1;
    CRC crc(dataLen, poly_idx);
    crc.setData(data);
    std::string crcOut;
    while (crc.hasData()) {
        crcOut += crc.getWord();
    }
    std::cout << "Data after CRC: " << crcOut << '\n';
    crcOut = flipBits(crcOut, pos2flip);
    std::cout << "Modified Data: " << crcOut << '\n';
    std::vector<std::string> words2 = convert2words(crcOut, wordSize);
    for (auto x : words2) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((crc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }
    std::cout << '\n';
}

void allDetectErrors() {
    std::cout << "===== All Methods Detecting Errors =====\n";
    std::string data = "1010101010";
    std::vector<unsigned int> pos2flip = { 9, 11, 13 };
    std::cout << "Data: " << data << "\nPositions to flip after processing: ";
    for (auto x : pos2flip) {
        std::cout << x << ", ";
    }
    std::cout << '\n';

    std::cout << "== VRC: ==\n";
    int wordSize = 16;
    VRC vrc(wordSize);
    vrc.setData(data);
    std::string vrcOut;
    while (vrc.hasData()) {
        vrcOut += vrc.getWord();
    }
    std::cout << "Data after VRC: " << vrcOut << '\n';
    vrcOut = flipBits(vrcOut, pos2flip);
    std::cout << "Modified Data: " << vrcOut << '\n';
    std::vector<std::string> words = convert2words(vrcOut, wordSize);
    for (auto x : words) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((vrc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "\n== CRC: ==\n";
    int dataLen = 10;
    int poly_idx = 2;
    int poly_len = Polynomials[poly_idx].size();
    wordSize = dataLen + poly_len - 1;
    CRC crc(dataLen, poly_idx);
    crc.setData(data);
    std::string crcOut;
    while (crc.hasData()) {
        crcOut += crc.getWord();
    }
    std::cout << "Data after CRC: " << crcOut << '\n';
    crcOut = flipBits(crcOut, pos2flip);
    std::cout << "Modified Data: " << crcOut << '\n';
    std::vector<std::string> words2 = convert2words(crcOut, wordSize);
    for (auto x : words2) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing word: " << ((crc.testWord(x)) ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "\n== CHECKSUM: ==\n";
    wordSize = 8;
    int wordsPerFrame = 3;
    CHECKSUM checksum(wordSize, wordsPerFrame);
    checksum.setData(data);
    std::string checksumOut;
    while (checksum.hasData()) {
        checksumOut += checksum.getFrame();
    }
    std::cout << "Data after CHECKSUM: " << checksumOut << '\n';
    checksumOut = flipBits(checksumOut, pos2flip);
    std::cout << "Modified Data: " << checksumOut << '\n';
    std::vector<std::string> frames = convert2frames(checksumOut, wordSize, wordsPerFrame);
    for (auto x : frames) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing frame: " << (checksum.testFrame(x) ? "PASS" : "FAIL") << '\n';
    }
    frames.clear();

    std::cout << "\n== LRC: ==\n";
    wordSize = 8;
    wordsPerFrame = 3;
    LRC lrc(wordSize, wordsPerFrame);
    lrc.setData(data);
    std::string lrcOut;
    unsigned int frameCount = 0;
    while (lrc.hasData()) {
        lrcOut += lrc.getFrame();
    }
    std::cout << "Data after LRC: " << lrcOut << '\n';
    lrcOut = flipBits(lrcOut, pos2flip);
    std::cout << "Modified Data: " << lrcOut << '\n';
    frames = convert2frames(lrcOut, wordSize, wordsPerFrame);
    for (auto x : frames) {
        std::cout << "  Frame: " << x << '\n';
        std::cout << "  Testing frame: " << (lrc.testFrame(x) ? "PASS" : "FAIL") << '\n';
    }
}
