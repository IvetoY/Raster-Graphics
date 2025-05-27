#include "PBM.h"
#include "Image.h"
#include "../Pixel/Pixel.h"
#include <fstream>
#include "../Transformations/Grayscale.h"
#include <stdexcept>
void PBM::swap(Image& other) {
        PBM* otherPBM = dynamic_cast<PBM*>(&other);
        if (!otherPBM) {
            throw std::runtime_error("Cannot swap PPM with non-PPM image");
        }
        std::swap(width, otherPBM->width);
        std::swap(height, otherPBM->height);
        std::swap(pixels, otherPBM->pixels);
}

PBM::PBM() : Image(), format(P1_ASCII), pixels(nullptr) {}
PBM::PBM(unsigned _width, unsigned _height, uint8_t _maxColorValue,const std::string& _magicNumber, const std::string& _fileName,Pixel**&& pixelsData, Format fmt)
    : Image(_width, _height, _maxColorValue, _magicNumber, _fileName),
      format(fmt),
      pixels(pixelsData)
{
    if (_maxColorValue != 1){throw std::invalid_argument("PBM max color value must be 1");}
}
PBM::PBM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers, const std::string& _magicNumber, const std::string& _fileName,const Pixel* const* _pixels)
    : Image(_width, _height, _maxColourNumbers, _magicNumber, _fileName),
      format(_magicNumber == "P1" ? P1_ASCII : P4_BINARY), pixels(new Pixel*[height])
    {

    for (unsigned y = 0; y < height; ++y){
		this->pixels[y] = new Pixel [width];
		for (unsigned x = 0;  x< width; ++x){
			this->pixels[y][x] = pixels[y][x];
		}
	}
}
PBM::PBM(const std::string& fileName): Image(), format(P1_ASCII), pixels(nullptr) {load(fileName);}

PBM::~PBM(){free();}
PBM::PBM(const PBM& other) : Image(other), format(other.format){copy(other);}
PBM::PBM(PBM&& other) noexcept : Image(std::move(other)), format(other.format){move(std::move(other));}
PBM& PBM::operator=(const PBM& other){
    if(this!=&other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PBM& PBM::operator=(PBM&& other) noexcept{
    if (this != &other){
        free();
        move(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
Image* PBM::collage(const Image* second, const std::string& newFileName, Direction direction) const{
    return second->collageWithPBM(this, newFileName, direction);
}
Image* PBM::collageWithPGM(const PGM* second, const std::string& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PBM::collageWithPPM(const PPM* second, const std::string& newFileName, Direction d) const {throw std::logic_error("Can't collage different types!");}
Image* PBM::collageWithPBM(const PBM* second, const std::string& newFileName, Direction d) const {
    if(!second){throw std::invalid_argument("Null image provided");}
    
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
    for(unsigned y = 0; y < newHeight; ++y) {
        newPixels[y] = new Pixel[newWidth]();
    }
    for(unsigned y = 0; y < height; ++y){
        for(unsigned x = 0; x < width; ++x){
            if(d == Direction::HORIZONTAL){
                newPixels[y][x] = pixels[y][x];
            } 
            else{
                newPixels[y][x] = pixels[y][x];
            }
        }
    }
    for(unsigned y = 0; y < second->height; ++y){
        for(unsigned x = 0; x < second->width; ++x){
            if(d == Direction::HORIZONTAL){
                unsigned ny = y;
                unsigned nx = width + x;
                if(ny < newHeight && nx < newWidth){
                    newPixels[ny][nx] = second->pixels[y][x];
                }
            } 
            else{
                unsigned ny = height + y;
                unsigned nx = x;
                if(ny < newHeight && nx < newWidth){
                    newPixels[ny][nx] = second->pixels[y][x];
                }
            }
        }
    }
    
    return new PBM(newWidth, newHeight, static_cast<uint8_t>(1), magicNumber, newFileName, std::move(newPixels), format);
}


void PBM::grayscale(){
    for(unsigned y = 0; y < height; ++y){
        for(unsigned x = 0; x < width; ++x){
            uint8_t value = (pixels[y][x].getRed() > 0 || pixels[y][x].getGreen() > 0 || pixels[y][x].getBlue() > 0) ? 1 : 0;
            pixels[y][x].setRed(value);
            pixels[y][x].setGreen(value);
            pixels[y][x].setBlue(value);
        }
    }
}

void PBM::monochrome(){grayscale();}

void PBM::negative(){
    for(unsigned y = 0; y < height; ++y){
        for(unsigned x = 0; x < width; ++x){
            uint8_t value = pixels[y][x].getRed() > 0 ? 0 : 255;
            pixels[y][x].setRed(value);
            pixels[y][x].setGreen(value);
            pixels[y][x].setBlue(value);
        }
    }
}

void PBM::rotateLeft(){
    if(width == 0 || height == 0) {return;}
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

void PBM::rotateRight(){
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
PBM* PBM::clone() const{return new PBM(*this);}
void PBM::free(){
    if (pixels != nullptr) {
        for (unsigned y = 0; y < height; ++y) {
            delete[] pixels[y];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}

void PBM::move(PBM&& other){
    if (this == &other) {return;}
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
    other.format = P1_ASCII;
    other.magicNumber = "";
    other.fileName = "";  
}
void PBM::copy(const PBM& other) {
    if (this == &other) {return;}
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    
    if(other.pixels){
        pixels = new Pixel*[height];
        for(unsigned y = 0; y < height; ++y){
            pixels[y] = new Pixel[width];
            std::copy(other.pixels[y], other.pixels[y] + width, pixels[y]);
        }
    }
    else{
        pixels = nullptr;
    }
} 


void PBM::load(const std::string& filePath){
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if(!file.is_open()){throw std::runtime_error(("Failed to open PBM file: " + filePath).c_str());}

    file >> magicNumber;
    if(magicNumber != "P1" && magicNumber != "P4"){throw std::runtime_error("Invalid PBM format. Supported: P1 (ASCII), P4 (binary)");}
    format = (magicNumber == "P1") ? P1_ASCII : P4_BINARY;
    
    file >> width >> height;
    maxColourNumbers = 1; 
    
    file >> std::ws;
    while (file.peek() == '#') {
        file.ignore(1024, '\n');
    }
    file >> std::ws;

    free();
    pixels = new Pixel*[height];
    for(unsigned y = 0; y < height; ++y){
        pixels[y] = new Pixel[width];
    }

    if(format == P1_ASCII){
        for(unsigned y = 0; y < height; ++y){
            for(unsigned x = 0; x < width; ++x){
                int value;
                file >> value;
                if(file.fail()){
                    free();
                    throw std::runtime_error("Error reading PBM data");
                }
                uint8_t pixelValue = (value > 0) ? 255 : 0;
                pixels[y][x] = Pixel{pixelValue, pixelValue, pixelValue};
            }
        }
    } 
    else{ 
        file.ignore(1);
        const size_t bytesPerRow = (width + 7) / 8;
        char* rowBuffer = new char[bytesPerRow];
        
        for(unsigned y = 0; y < height; ++y){
            file.read(rowBuffer, bytesPerRow);
            if(file.gcount() != static_cast<std::streamsize>(bytesPerRow)){
                delete[] rowBuffer;
                free();
                throw std::runtime_error("Unexpected end of PBM file");
            }
            
            for(unsigned x = 0; x < width; ++x){
                const size_t byteIdx = x / 8;
                const size_t bitIdx = 7 - (x % 8);
                bool isWhite = (rowBuffer[byteIdx] & (1 << bitIdx));
                
                uint8_t value = isWhite ? 255 : 0;
                pixels[y][x] = Pixel{value, value, value};
            }
        }
        
        delete[] rowBuffer;
    }

    fileName = filePath;
}

void PBM::save(const std::string& filePath) const {
    std::ofstream file(filePath.c_str(), (format == P4_BINARY) ? std::ios::binary : std::ios::out);
    if(!file.is_open()){throw std::runtime_error(("Failed to create PBM file: " + filePath).c_str());}
    file << (format == P1_ASCII ? "P1\n" : "P4\n")
         << width << " " << height << "\n";

    if(format == P1_ASCII){
        for(unsigned y = 0; y < height; ++y){
            for(unsigned x = 0; x < width; ++x){
                bool isWhite = (pixels[y][x].getRed() > 0 || pixels[y][x].getGreen() > 0 || pixels[y][x].getBlue() > 0);
                file << (isWhite ? "1 " : "0 ");
            }
            file << "\n";
        }
    } 
    else{ 
        const size_t bytesPerRow = (width + 7) / 8;
        char* rowBuffer = new char[bytesPerRow]();
        try {
            for(unsigned y = 0; y < height; ++y){
                std::fill(rowBuffer, rowBuffer + bytesPerRow, 0);
                for(unsigned x = 0; x < width; ++x){
                    bool isWhite = (pixels[y][x].getRed() > 0 || pixels[y][x].getGreen() > 0 || pixels[y][x].getBlue() > 0);
                    if (isWhite){
                        const size_t byteIndex = x / 8;
                        const size_t bitIndex = 7 - (x % 8);
                        rowBuffer[byteIndex] |= (1 << bitIndex);
                    }
                }
                
                file.write(rowBuffer, bytesPerRow);
                if(file.fail()){throw std::runtime_error("Failed to write PBM binary data");}
            }
        } catch (...) {
            delete[] rowBuffer;
            throw;
        }
        
        delete[] rowBuffer;
    }
}

Pixel PBM::getPixel(unsigned x, unsigned y) const {
    if(x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    return pixels[y][x];
}

void PBM::setPixel(unsigned x, unsigned y, const Pixel& pixel){
    if(x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    pixels[y][x] = pixel;
}

