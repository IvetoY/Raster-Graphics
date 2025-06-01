/*#include "gtest/gtest.h"
#include "../System/System.h"
#include "../Image/Image.h"

class SystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        Session::resetSessionCounter();
        // Създаваме тестов PGM файл
        std::ofstream testFile("test.pgm");
        testFile << "P2\n3 3\n255\n1 2 3\n4 5 6\n7 8 9";
        testFile.close();
    }

    void TearDown() override {
        std::remove("test.pgm"); // Изтриваме тестовия файл
    }
};

TEST_F(SystemTest, LoadAndSaveImage) {
    System& system = System::getInstance();
    system.createNewSession();
    
    // Тест за зареждане
    system.loadSession("test.pgm");
    auto images = system.getCurrentSessionImages();
    ASSERT_EQ(images.size(), 1);
    EXPECT_EQ(images[0]->getFileName(), "test.pgm");
    
    // Тест за запазване
    testing::internal::CaptureStdout();
    system.saveSession();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Successfully saved") != std::string::npos);
}*/