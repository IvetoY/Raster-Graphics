#include "PGM.h"
#include <iostream>
#include <cassert>

/*void testPGMOperations() {
    try {
        PGM image("test_1.pgm");
        std::cout << "PGM image loaded successfully. Dimensions: " 
                  << image.getWidth() << "x" << image.getHeight() 
                  << ", Max color: " << (int)image.getMaxColourNumbers() << std::endl;

        Pixel p = image.getPixel(0, 0);
        std::cout << "Pixel at (0,0): R=" << (int)p.getRed() 
                  << " G=" << (int)p.getGreen() 
                  << " B=" << (int)p.getBlue() << std::endl;

        image.negative();
        image.save("test_negative.pgm");
        std::cout << "Negative saved to test_negative.pgm" << std::endl;

        PGM imageCopy = image;
        imageCopy.monochrome();
        imageCopy.save("test_monochrome.pgm");
        std::cout << "Monochrome saved to test_monochrome.pgm" << std::endl;

        image.save("test_copy.pgm");
        std::cout << "Copy saved to test_copy.pgm" << std::endl;

        
        image.rotateRight();
        image.save("test_rotated.pgm");
        std::cout << "Rotated image saved to test_rotated.pgm" << std::endl;

        PGM image2("test_1.pgm");
        Image* collage = image.collage(&image2, "collage.pgm", Direction::HORIZONTAL);
        collage->save("test_collage.pgm");
        delete collage;
        std::cout << "Collage saved to test_collage.pgm" << std::endl;

        std::cout << "All PGM tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "PGM test failed: " << e.what() << std::endl;
    }
}
*/
void testPGMLoadOnly() {
    try {
        PGM image("test1.pgm");
        std::cout << "Loaded successfully. Size: " 
                 << image.getWidth() << "x" << image.getHeight() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void testPGM(){
    PGM pbm;
    pbm.loadASCII("test1.pgm");
    pbm.saveASCII("pgm.pgm");
}
int main() {
    //testPGMOperations();
    testPGM();
    return 0;
}
