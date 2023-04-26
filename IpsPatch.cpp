#include "ROMCheck.h"

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <cstring>

#define IPS_EOF 0x454F46

using namespace std;

bool applyPatch (const std::string &OutFile, const std::string &PatchFile) {
    std::ifstream ReadROM(OutFile, std::ios::binary);
    ReadROM.seekg(0, std::ios::end);
    long ROMFileSize = ReadROM.tellg();
    unsigned char *ROMBuffer = new unsigned char[ROMFileSize];
    ReadROM.seekg(0, std::ios::beg);
    ReadROM.read((char *)ROMBuffer, ROMFileSize);
    ReadROM.close();
    ReadROM.clear();

    std::ifstream ReadPatch(PatchFile, std::ios::binary);
    ReadPatch.seekg(0, std::ios::end);
    long PatchFileSize = ReadPatch.tellg();
    unsigned char *PatchBuffer = new unsigned char[PatchFileSize];
    ReadPatch.seekg(0, std::ios::beg);
    ReadPatch.read((char *)PatchBuffer, PatchFileSize);
    ReadPatch.close();
    ReadPatch.clear();

    int patchPos = 5;    // After the header
    unsigned int offset, size;
    unsigned char b;
    offset = PatchBuffer[patchPos] << 16 | (PatchBuffer[patchPos + 1] << 8 | PatchBuffer[patchPos + 2]);
    patchPos += 3;
    while (offset != IPS_EOF) {
        size = PatchBuffer[patchPos] << 8 | PatchBuffer[patchPos + 1];
        patchPos += 2;
        if (size == 0) {
            // RLE hunk - one byte repeated
            size = PatchBuffer[patchPos] << 8 | PatchBuffer[patchPos + 1];
            patchPos += 2;
            b = PatchBuffer[patchPos++];
            memset(ROMBuffer + offset, b, size);
        } else {
            // Regular hunk - copy slice of patch into ROM
            memcpy(ROMBuffer + offset, PatchBuffer + patchPos, size);
            patchPos += size;
        }
        offset = PatchBuffer[patchPos] << 16 | (PatchBuffer[patchPos + 1] << 8 | PatchBuffer[patchPos + 2]);
        patchPos += 3;
    }

    std::ofstream WriteROM(OutFile, std::ios::binary);
    WriteROM.write((char *)ROMBuffer, ROMFileSize);
    WriteROM.close();
    WriteROM.clear();

    delete[] ROMBuffer;
    delete[] PatchBuffer;
    return true;
}
