#include <iostream>
#include <cassert>
#include <fstream>
#include "PBM.h"
#include "../Pixel/Pixel.h"

void testPBM() {
    /*{
        std::ofstream testFile("test.pbm");
        testFile << "P1\n2 2\n1 0\n0 1\n";
        testFile.close();
        
        PBM pbm;
        pbm.load("test.pbm");
        assert(pbm.getWidth() == 2);
        assert(pbm.getHeight() == 2);
        assert(pbm.getMagicNumber() == "P1");
        assert(pbm.getMaxColourNumbers() == 1);
        
        std::cout << "Test 1: Load PBM passed\n";
        std::remove("test.pbm");
    }*/

    {
        PBM pbm1;
        pbm1.load("test.pbm");
        
        PBM pbm2(pbm1);
        assert(pbm2.getWidth() == 2);
        assert(pbm2.getHeight() == 2);
        
        std::cout << "Test 2: Copy constructor passed\n";
    }

    {
        PBM pbm;
        pbm.load("test.pbm");
        pbm.save("output.pbm");
        
        PBM loaded;
        loaded.load("output.pbm");
        assert(loaded.getWidth() == 2);
        assert(loaded.getHeight() == 2);
        
        std::cout << "Test 3: Save and load passed\n";
        std::remove("output.pbm");
    }

    {
        PBM pbm;
        pbm.load("test.pbm");
        
        pbm.negative();
        Pixel p = pbm.getPixel(0, 0);
        assert(p.getRed() == 0 && p.getGreen() == 0 && p.getBlue() == 0);

        pbm.rotateRight();
        assert(pbm.getWidth() == 2 && pbm.getHeight() == 2);
        
        std::cout << "Test 4: Transformations passed\n";
    }

    {
        PBM pbm;
        try {
            pbm.load("nonexistent.pbm");
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Test 5.1: Expected error (nonexistent file): " << e.what() << "\n";
        }
     
        try {
            pbm.load("test.pbm");
            pbm.getPixel(10, 10);
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Test 5.2: Expected error (invalid coordinates): " << e.what() << "\n";
        }
    }
}

int main() {
    std::ofstream testFile("test.pbm");
    testFile << "P1\n2 2\n1 0\n0 1\n";
    testFile.close();
    
    testPBM();
    
    std::remove("test.pbm");
    
    std::cout << "All PBM tests completed!\n";
    return 0;
}