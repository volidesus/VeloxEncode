#include <iostream>
#include "qrDeclaration.hpp"
#include "jpegWriteDeclaration.hpp"

int main() {
    std::string data = "Hello, World! This is a longer message for a larger QR code.";
    QRCode qr(data, 7);
    writeJPEG(qr.getMatrix(), "qrcode.jpg", 7);
    return 0;
}
