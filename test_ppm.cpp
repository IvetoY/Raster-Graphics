#include "../Image/PPM.h"
#include "../Pixel/Pixel.h"
#include <iostream>
#include <cassert>

void testPPMOperations() {
    try {
        PPM image("test_1.ppm");
        std::cout << "Image loaded successfully. Dimensions: " 
                  << image.getWidth() << "x" << image.getHeight() << std::endl;
        Pixel p = image.getPixel(0, 0);
        std::cout << "Pixel at (0,0): R=" << (int)p.getRed() 
                  << " G=" << (int)p.getGreen() 
                  << " B=" << (int)p.getBlue() << std::endl;

        image.negative();
        image.save("test_negative.ppm");
        std::cout << "Negative saved to test_negative.ppm" << std::endl;

        image.save("test_copy.ppm");
        std::cout << "Copy saved to test_copy.ppm" << std::endl;

        PPM image2("test_1.ppm");
        Image* collage = image.collage(&image2, "collage.ppm", Direction::HORIZONTAL);
        collage->save("test_collage.ppm");
        delete collage;
        std::cout << "Collage saved to test_collage.ppm" << std::endl;

        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }
}

int main() {
    testPPMOperations();
    return 0;
}