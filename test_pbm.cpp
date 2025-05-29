#include <iostream>
#include <cassert>
#include <fstream>
#include "PBM.h"
#include "../Pixel/Pixel.h"

void testPBM() 
    

    /*{
        PBM pbm1;
        pbm1.loadASCII("test2.pbm");
        
        PBM pbm2(pbm1);
        
        std::cout << "Test 2: Copy constructor passed\n";
    }*/

    {
        PBM pbm;
        pbm.loadASCII("test2.pbm");
        pbm.saveASCII("output.pbm");
        
        /*PBM loaded;
        loaded.loadASCII("output.pbm");
        assert(loaded.getWidth() == 2);
        assert(loaded.getHeight() == 2);
        
        std::cout << "Test 3: Save and load passed\n";
        
    }

    {
        PBM pbm;
        pbm.loadASCII("test2.pbm");
        
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
            pbm.loadASCII("nonexistent.pbm");
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Test 5.1: Expected error (nonexistent file): " << e.what() << "\n";
        }
     
        try {
            pbm.loadASCII("test2.pbm");
            pbm.getPixel(10, 10);
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Test 5.2: Expected error (invalid coordinates): " << e.what() << "\n";
        }
    }*/
}

int main() {
    //std::ofstream testFile("test2.pbm");
    
    testPBM();
    
    
    std::cout << "All PBM tests completed!\n";
    return 0;
}