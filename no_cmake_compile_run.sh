mkdir build
g++ -c ./detectors/util.cpp
g++ -c ./detectors/checksum/CHECKSUM.cpp
g++ -c ./detectors/lrc/LRC.cpp
g++ -c ./detectors/vrc/VRC.cpp
g++ -c ./detectors/crc/CRC.cpp
g++ main.cpp util.o CHECKSUM.o LRC.o VRC.o CRC.o -o build/main
./build/main