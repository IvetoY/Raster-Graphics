#include "PGM.h"
#include "Image.h"
#include <fstream>
#include "../Pixel/Pixel.h"
#include <string>
#include <algorithm>
void PGM::swap(Image& other) {
        PGM* otherPGM = dynamic_cast<PGM*>(&other);
        if (!otherPGM) {
            throw std::runtime_error("Cannot swap PPM with non-PPM image");
        }
        std::swap(fileName, otherPGM->fileName);
        std::swap(width, otherPGM->width);
        std::swap(height, otherPGM->height);
        std::swap(pixels, otherPGM->pixels);
}

PGM::PGM() : Image(), format(P2_ASCII), pixels(nullptr) {}

PGM::PGM(const std::string& filePath)
    : Image(), format(P2_ASCII), pixels(nullptr) {
        fileName = filePath;
    if(format == P2_ASCII) {loadASCII(fileName);}
    else {loadBinary(fileName);}
    
}
PGM::PGM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers,
         const std::string& _magicNumber, const std::string& _fileName,
         Pixel**&& _pixels, Format _format)
    : Image(_width, _height, _maxColourNumbers, _magicNumber, _fileName),
      format(_format),
      pixels(_pixels)
{}
PGM::PGM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers, 
         const std::string& _magicNumber, const std::string& _fileName,
         const Pixel* const* _pixels)
    : Image(_width, _height, _maxColourNumbers, _magicNumber, _fileName),
      format(_magicNumber == "P2" ? P2_ASCII : P5_BINARY)
{
    for(unsigned y = 0; y < height; ++y){
		this->pixels[y] = new Pixel[width];
		for(unsigned x = 0; x < width; ++x){
			this->pixels[y][x] = pixels[y][x];
		}
	}
}

PGM::~PGM(){free();}

PGM::PGM(const PGM& other) : Image(other), format(other.format){copy(other);}
PGM::PGM(PGM&& other) noexcept : Image(std::move(other)), format(other.format){move(std::move(other));}
PGM& PGM::operator=(const PGM& other){
    if(this!=&other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PGM& PGM::operator=(PGM&& other) noexcept{
    if (this != &other){
        free();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
Image* PGM::collage(const Image* second, const std::string& newFileName, Direction direction) const{
    return second->collageWithPGM(this, newFileName, direction);
}
Image* PGM::collageWithPBM(const PBM* second, const std::string& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PGM::collageWithPPM(const PPM* second, const std::string& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PGM::collageWithPGM(const PGM* second, const std::string& newFileName, Direction d) const {
    if (!second) throw std::invalid_argument("Null image provided");
    
    unsigned newWidth = width, newHeight = height;
    if(d == Direction::HORIZONTAL){
        newWidth += second->width;
        newHeight = std::max(height, second->height);
    } 
    else{
        newHeight += second->height;
        newWidth = std::max(width, second->width);
    }
    
    Pixel** newPixels = new Pixel*[newHeight];
    for(unsigned y = 0; y < newHeight; ++y){
        newPixels[y] = new Pixel[newWidth]();  
        if (d == Direction::HORIZONTAL){
            if (y < height){
                for(unsigned x = 0; x < width; ++x){
                    newPixels[y][x] = pixels[y][x];
                }
            }
            if (y < second->height){
                for(unsigned x = 0; x < second->width; ++x){
                    newPixels[y][width + x] = second->pixels[y][x];
                }
            }
        } 
        else {
            if(y < height){
                for(unsigned x = 0; x < width; ++x){
                    newPixels[y][x] = pixels[y][x];
                }
            }
            else if (y - height < second->height){
                for(unsigned x = 0; x < second->width; ++x){
                    newPixels[y][x] = second->pixels[y - height][x];
                }
            }
        }
    }
    
    uint8_t newMaxColor = std::max(maxColourNumbers, second->maxColourNumbers);
    return new PGM(newWidth, newHeight, newMaxColor, magicNumber, newFileName, std::move(newPixels), format);
}

void PGM::grayscale(){}

void PGM::monochrome() {
    uint8_t threshold = maxColourNumbers / 2;
    for(unsigned y = 0; y < height; ++y) {
        for(unsigned x = 0; x < width; ++x) {
            uint8_t value = static_cast<uint8_t>(
                0.299 * pixels[y][x].getRed() + 
                0.587 * pixels[y][x].getGreen() + 
                0.114 * pixels[y][x].getBlue()
            );
            uint8_t monoValue = (value > threshold) ? maxColourNumbers : 0;
            pixels[y][x].setRed(monoValue);
            pixels[y][x].setGreen(monoValue);
            pixels[y][x].setBlue(monoValue);
        }
    }
}

void PGM::negative() {
    for(unsigned y = 0; y < height; ++y){
        for (unsigned x = 0; x < width; ++x){
            unsigned  r = pixels[y][x].getRed();
            unsigned  g = pixels[y][x].getGreen();
            unsigned  b = pixels[y][x].getBlue();
            pixels[y][x].setRed(maxColourNumbers - r);
            pixels[y][x].setGreen(maxColourNumbers - g);
            pixels[y][x].setBlue(maxColourNumbers - b);
        }
    }
}
void PGM::rotateLeft() {
    Pixel** rotated = new Pixel*[width];
    for(unsigned x = 0; x < width; ++x){
        rotated[x] = new Pixel[height];
        for(unsigned y = 0; y < height; ++y){
            rotated[x][y] = pixels[y][width - 1 - x];
        }
    }
    free();
    std::swap(width, height);
    pixels = rotated;
}
void PGM::rotateRight(){
    Pixel** rotated = new Pixel*[width];
    for(unsigned x = 0; x < width; ++x){
        rotated[x] = new Pixel[height];
        for(unsigned y = 0; y < height; ++y){
            rotated[x][y] = pixels[height - 1 - y][x];
        }
    }
    free();
    std::swap(width, height);
    pixels = rotated;
}
PGM* PGM::clone() const{return new PGM(*this);}
void PGM::free(){
    if (pixels != nullptr){
        for(unsigned y = 0; y < height; ++y){
            delete[] pixels[y];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}
void PGM::move(PGM&& other){
    pixels = other.pixels;
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = std::move(other.magicNumber);
    fileName = std::move(other.fileName);
    format = other.format;

    other.pixels = nullptr;
    other.width = 0;
    other.height = 0;
    other.maxColourNumbers = 0;
    other.format = P2_ASCII;
    other.magicNumber = "";
    other.fileName = "";  
}
void PGM::copy(const PGM& other) {
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    pixels = other.pixels; 
} 

void PGM::loadASCII(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open PGM file");
    }
    file >> magicNumber;
    format = P2_ASCII;
    
    while (file.peek() == ' ' || file.peek() == '\t' || file.peek() == '\n' || file.peek() == '#') {
        if (file.peek() == '#') {
            file.ignore(1024, '\n');
        } else {
            file.ignore(1);
        }
    }
    file >> width >> height;
    unsigned maxValue;
    file >> maxValue;
    
    free();
    
    pixels = new Pixel*[height];
    for (unsigned y = 0; y < height; ++y){
        pixels[y] = new Pixel[width];
    }

        for (unsigned y = 0; y < height; ++y){
            for (unsigned x = 0; x < width; ++x){
                int value;
                file >> value;
                uint8_t gray = static_cast<uint8_t>(255 * value / maxValue);
                pixels[y][x] = Pixel(gray, gray, gray);
            }
        }
        maxColourNumbers = static_cast<uint8_t>(maxValue);
        file.close();
}
void PGM::loadBinary(const std::string& filePath){
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open PGM file");
    }
    file >> magicNumber;
    format = (magicNumber == "P2") ? P2_ASCII : P5_BINARY;
    
    while (file.peek() == ' ' || file.peek() == '\t' || file.peek() == '\n' || file.peek() == '#') {
        if (file.peek() == '#') {
            file.ignore(1024, '\n');
        } else {
            file.ignore(1);
        }
    }
    file >> width >> height;
    file >> maxColourNumbers;
    while (file.peek() == ' ' || file.peek() == '\t' || file.peek() == '\n') {
        file.ignore(1);
    }
    free();
    uint8_t* buffer = new uint8_t[width];
        for (unsigned y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(buffer), width);
            for (unsigned x = 0; x < width; ++x) {
                pixels[y][x].setRed(buffer[x]);
                pixels[y][x].setGreen(buffer[x]);
                pixels[y][x].setBlue(buffer[x]);
            }
        }
        this->pixels = pixels;
        delete[] buffer;

        file.close();
}


void PGM::saveASCII(const std::string& filePath) const {
    std::ofstream file(filePath);
    if(!file.is_open()){throw std::runtime_error("Failed to create PGM file");}
    
    file << "P2\n"
         << width << " " << height << "\n"
         << static_cast<int>(maxColourNumbers) << "\n";
    
        const unsigned max_line_length = 70;
        unsigned current_line_length = 0;

        for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            uint8_t gray = pixels[y][x].getRed();
            int value = static_cast<int>(gray);
            std::string valueStr = std::to_string(value);

            if (current_line_length + valueStr.length() + 1 > max_line_length) {
                file << "\n";
                current_line_length = 0;
            } else if (current_line_length > 0) {
                file << " ";
                current_line_length++;
            }
            
            file << valueStr;
            current_line_length += valueStr.length();
        }
        file << "\n";
        current_line_length = 0;
    }
    
        file.close();
    }

void PGM::saveBinary(const std::string& filePath) const{
    std::ofstream file(filePath, std::ios::binary);
    if(!file.is_open()){throw std::runtime_error("Failed to create PGM file");}
    
    file << "P5\n" << width << " " << height << "\n" << maxColourNumbers << "\n";
    uint8_t* buffer = new uint8_t[width];
        for (unsigned y = 0; y < height; ++y){
            for(unsigned x = 0; x < width; ++x){
                buffer[x]= static_cast<uint8_t>(std::min(maxColourNumbers,
    static_cast<uint8_t>(0.299 * pixels[y][x].getRed() + 
                     0.587 * pixels[y][x].getGreen() + 
                     0.114 * pixels[y][x].getBlue())
));;
            }
            file.write(reinterpret_cast<const char*>(buffer), width);
        }
        file.flush();
        file.close();
        delete[] buffer;
        
}
Pixel PGM::getPixel(unsigned x, unsigned y) const {
    if (x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    return pixels[y][x];
}

void PGM::setPixel(unsigned x, unsigned y, const Pixel& pixel) {
    if (x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    pixels[y][x] = pixel;
}