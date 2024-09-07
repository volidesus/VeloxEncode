#include <vector>
#include <array>
#include <stdexcept>

#ifndef QRDECLARATION_HPP
#define QRDECLARATION_HPP

class QRCode {
private:
    std::vector<std::vector<bool>> matrix;
    int size;
    int version;

    const std::array<std::vector<int>, 7> alignmentPatternPositions = {{
        {}, {6, 18}, {6, 22}, {6, 26}, {6, 30}, {6, 34}, {6, 22, 38}
    }};

    void initializeMatrix();
    void setFunctionPatterns();
    void setFinderPattern(int row, int col);
    void setAlignmentPattern(int row, int col);
    void setAlignmentPatterns();
    bool isReservedArea(int row, int col);
    std::string encodeData(const std::string& data);
    void setData(const std::string& data);

public:
    QRCode(const std::string& data, int ver = 1) : version(ver), size(21 + (ver - 1) * 4) {
        if (version < 1 || version > 7) {
            throw std::invalid_argument("Version must be between 1 and 7");
        }
        initializeMatrix();
        setFunctionPatterns();
        setData(data);
    }

    std::vector<std::vector<bool>> getMatrix();
};

#endif