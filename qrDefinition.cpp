#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <bitset>
#include "qrDeclaration.hpp"

void QRCode::initializeMatrix() {
    matrix = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
}

void QRCode::setFunctionPatterns() {
    setFinderPattern(0, 0);
    setFinderPattern(size - 7, 0);
    setFinderPattern(0, size - 7);
        
    if (version >= 2) {
        setAlignmentPatterns();
    }

    for (int i = 8; i < size - 8; ++i) {
        matrix[i][6] = matrix[6][i] = (i % 2 == 0);
    }
}

void QRCode::setFinderPattern(int row, int col) {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if ((i == 0 || i == 6 || j == 0 || j == 6) || (i >= 2 && i <= 4 && j >= 2 && j <= 4)) {
                matrix[row + i][col + j] = true;
            }
        }
    }
}

void QRCode::setAlignmentPattern(int row, int col) {
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            matrix[row + i][col + j] = (i == -2 || i == 2 || j == -2 || j == 2 || (i == 0 && j == 0));
        }
    }
}

void QRCode::setAlignmentPatterns() {
    const std::vector<int>& positions = alignmentPatternPositions[version - 1];
    for (int row : positions) {
        for (int col : positions) {
            if (!((row < 7 && col < 7) || (row < 7 && col > size - 8) || (row > size - 8 && col < 7))) {
                setAlignmentPattern(row, col);
            }
        }
    }
}

bool QRCode::isReservedArea(int row, int col) {
    if (row < 8 && (col < 8 || col >= size - 8)) return true;
    if (row >= size - 8 && col < 8) return true;
    if (row == 6 || col == 6) return true;

    if (version >= 2) {
        const std::vector<int>& positions = alignmentPatternPositions[version - 1];
        for (int r : positions) {
            for (int c : positions) {
                if (std::abs(row - r) <= 2 && std::abs(col - c) <= 2) {
                    return true;
                }
            }
        }
    }

    return false;
}

std::string QRCode::encodeData(const std::string& data) {
    std::string encoded;
    for (char c : data) {
        encoded += std::bitset<8>(c).to_string();
    }
    return encoded;
}

void QRCode::setData(const std::string& data) {
    std::string bitString = encodeData(data);
    int index = 0;
        
    for (int right = size - 1; right >= 0; right -= 2) {
        if (right == 6) right--;
        for (int vert = size - 1; vert >= 0; vert--) {
            for (int left = right; left > right - 2 && left >= 0; left--) {
                if (!isReservedArea(vert, left) && index < bitString.length()) {
                    matrix[vert][left] = (bitString[index++] == '1');
                }
            }
        }
    }
}

std::vector<std::vector<bool>> QRCode::getMatrix() {
    return matrix;
}