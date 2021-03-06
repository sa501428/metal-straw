/*
  The MIT License (MIT)

  Copyright (c) 2011-2016 Broad Institute, Aiden Lab

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/
#ifndef STRAW_H
#define STRAW_H

#include <fstream>
#include <set>
#include <vector>
#include <map>

// pointer structure for reading blocks or matrices, holds the size and position
struct indexEntry {
    long size;
    long position;
};

// sparse matrixType entry
struct contactRecord {
    int binX;
    int binY;
    float counts;
};

struct footerInfo {
    int resolution;
    bool foundFooter;
    int version;
    int c1;
    int c2;
    int numBins1;
    int numBins2;
    long myFilePos;
    std::string unit;
    std::string norm;
    std::string matrixType;
    std::vector<double> c1Norm;
    std::vector<double> c2Norm;
    std::vector<double> expectedValues;
};

// chromosome
struct chromosome {
    std::string name;
    int index;
    long length;
};


bool readMagicString(std::ifstream &fin);

std::map<std::string, chromosome> readHeader(std::istream &fin, long &masterIndexPosition);

bool readFooter(std::istream &fin, long master, int c1, int c2, std::string matrix, std::string norm, std::string unit,
                int resolution, long &myFilePos, indexEntry &c1NormEntry, indexEntry &c2NormEntry,
                std::vector<double> &expectedValues);

std::map<int, indexEntry>
readMatrixZoomData(std::istream &fin, const std::string &myunit, int mybinsize, float &mySumCounts,
                   int &myBlockBinCount,
                   int &myBlockColumnCount, bool &found);

std::map<int, indexEntry>
readMatrix(std::istream &fin, int myFilePosition, std::string unit, int resolution, float &mySumCounts,
           int &myBlockBinCount, int &myBlockColumnCount);

std::set<int>
getBlockNumbersForRegionFromBinPosition(int *regionIndices, int blockBinCount, int blockColumnCount, bool intra);

std::vector<contactRecord> readBlock(std::istream &fin, int blockNumber);

std::vector<double> readNormalizationVector(std::istream &fin, indexEntry entry);

std::vector<contactRecord>
straw(std::string matrixType, std::string norm, std::string fname, std::string chr1loc, std::string chr2loc,
      const std::string &unit, int binsize);

#endif
