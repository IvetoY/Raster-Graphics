#include <iostream>
#include "Pixel.h"

void testPixelClass() {
    Pixel p1;
    Pixel p2(255, 128, 64);
    Pixel p3(p2);
    std::cout << "Testing get methods:\n";
    std::cout << "p1: " << (int)p1.getRed() << ", " << (int)p1.getGreen() << ", " << (int)p1.getBlue() << "\n";
    std::cout << "p2: " << (int)p2.getRed() << ", " << (int)p2.getGreen() << ", " << (int)p2.getBlue() << "\n";
    std::cout << "p3: " << (int)p3.getRed() << ", " << (int)p3.getGreen() << ", " << (int)p3.getBlue() << "\n";

    p1.setRed(100);
    p1.setGreen(150);
    p1.setBlue(200);
    std::cout << "\nAfter set methods, p1: " << (int)p1.getRed() << ", " << (int)p1.getGreen() << ", " << (int)p1.getBlue() << "\n";

   
    p1.setRGB(10, 20, 30);
    std::cout << "After setRGB, p1: " << (int)p1.getRed() << ", " << (int)p1.getGreen() << ", " << (int)p1.getBlue() << "\n";

    std::cout << "\nTesting comparison operators:\n";
    std::cout << "p2 == p3: " << (p2 == p3) << " (expected: 1)\n";
    std::cout << "p2 != p3: " << (p2 != p3) << " (expected: 0)\n";
    std::cout << "p1 == p2: " << (p1 == p2) << " (expected: 0)\n";
    std::cout << "p1 != p2: " << (p1 != p2) << " (expected: 1)\n";

    Pixel p4;
    p4 = p2;
    std::cout << "\nAfter assignment, p4: " << (int)p4.getRed() << ", " << (int)p4.getGreen() << ", " << (int)p4.getBlue() << "\n";
    std::cout << "p4 == p2: " << (p4 == p2) << " (expected: 1)\n";

    Pixel grayTest(100, 150, 200);
    std::cout << "\nTesting getGray():\n";
    std::cout << "Gray value for (100,150,200): " << grayTest.getGray() << "\n";

}
    

int main() {
    testPixelClass();
    return 0;
}