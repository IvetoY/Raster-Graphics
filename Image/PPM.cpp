#include "PPM.h"
#include "Image.h"
#include "../Pixel/Pixel.h"
#include "../Utils/PathHelper.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include "../Commands/Load.h"
PPM::~PPM(){pixels.clear();}
PPM::PPM() : Image(), format(Format::P3_ASCII){magicNumber = "P3";}

PPM::PPM(String& fileName){Load(fileName);}

PPM& PPM::operator=(const PPM& other)
{
    if (this != &other){
        pixels.clear();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PPM& PPM::operator=(PPM&& other) noexcept
{
    if (this != &other){
        pixels.clear();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}

PPM::PPM(const PPM& other) : Image(other), format(other.format) {
    pixels = other.pixels;
}
PPM::PPM(PPM&& other) noexcept : Image(std::move(other)){move(std::move(other));}

PPM::PPM(unsigned _width, unsigned _height, uint8_t _maxColour, const String& _magicNum, const String& _fileName, const std::vector<std::vector<Pixel>>& _pixels, Format _format = P3_ASCII): 
    Image(_width, _height, _maxColour, _magicNum, _fileName, _pixels), format(_format) {}
PPM* PPM::clone() const {
    return new PPM(*this);
}

/*void PPM::load(const String& filename){
    std::ifstream file(filename.c_str(), std::ios::binary);
    if(!file){throw std::runtime_error(("Failed to open file: " + filename).c_str());}

    file>>magicNumber;
    if(magicNumber!= "P3" && magicNumber!="P6"){throw std::runtime_error("Invalid PPM format. Only P3 and P6 are supported!");}
    
    if(magicNumber == "P3"){format = P3_ASCII;}
    else {format = P6_BINARY;}
    
    file>>width>>height>>maxColourNumbers;

    //  whitecpace/comments
    file>>std::ws;
    while(file.peek() == '#'){file.ignore(1024,'\n');}
    file >> std::ws;

    pixels.resize(height,std::vector<Pixel>(width));

    
}*/
Image* PPM::collage(const Image* second, const String& newFileName, Direction d)const{
    return second->collageWithPPM(this, newFileName, d);
}

void PPM::save(const String& filename) const{
    std::ios_base::openmode mode = std::ios::out;
    if (format == P6_BINARY) {
        mode |= std::ios::binary;
    }
    
    std::ofstream file(filename.c_str(), mode);
    std::ofstream file(filename.c_str());

    if (!file){throw std::runtime_error(("Failed to create file: " + filename).c_str());}
    file<<magicNumber << std::endl;
    file<<height<<" "<<width <<std::endl;
    file<<(uint8_t)maxColourNumbers<<std::endl;

    for(unsigned y=0;y<height;++y){
        for(unsigned x=0;x<width;++x){
            const Pixel& pixel = pixels[y][x];
            if(format == P3_ASCII){
                file<<static_cast<int>(pixel.getRed()) << " "
                <<static_cast<int>(pixel.getGreen()) << " "
                <<static_cast<int>(pixel.getBlue()) << " ";
            }
            else{//format == P6_BINARY
                file.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
            }
        }
        if(format == P3_ASCII) {file<< std::endl;}
    }
    file.close();
}
Image* PPM::collageWithPBM(const PBM* second, const String& newFileName, Direction d) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPGM(const PGM* second, const String& newFileName, Direction d) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPPM(const PPM* second, const String& newFileName, Direction d) const{
    if(!second){return nullptr;}
    if (strcmp(extractFileExtension(newFileName.c_str()), getFileExtension()) != 0){throw std::runtime_error("Invalid new file name for collage! Must be .ppm!");}
    if (format != second->format){throw std::runtime_error("Cannot collage PPM images with different formats");}

    size_t newWidth = d == Direction::HORIZONTAL ? width + second->width : std::max(width, second->width);
    size_t newHeight = d == Direction::HORIZONTAL ? std::max(height, second->height) : height + second->height;

    std::vector<std::vector<Pixel>> newPixels(newHeight, std::vector<Pixel>(newWidth, Pixel(0,0,0)));

    for (unsigned y = 0; y < height; ++y){
        for (unsigned x = 0; x < width; ++x) {
            newPixels[y][x] = pixels[y][x];
        }
    }
    if(d == Direction::HORIZONTAL){
        for (unsigned y = 0; y < second->getHeight(); ++y){
            for (unsigned x = 0; x < second->getWidth(); ++x){
                newPixels[y][x + width] = second->pixels[y][x];
            }
        }
    }
    else{
        for (unsigned y = 0; y < second->getHeight(); ++y){
            for (unsigned x = 0; x < second->getWidth(); ++x){
                newPixels[y + height][x] = second->pixels[y][x];
            }
        }
    }

    return new PPM(newWidth, newHeight, std::max(maxColourNumbers, second->getMaxColourNumbers()), magicNumber, newFileName, newPixels, format);
}



void PPM::move(PPM&& other) noexcept {
    pixels = std::move(other.pixels);
    other.pixels.clear();
    
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = std::move(other.magicNumber);
    fileName = std::move(other.fileName);
    format = other.format;

    other.width = 0;
    other.height = 0;
    other.maxColourNumbers = 0;
    other.format = P3_ASCII;  
}

void PPM::copy(const PPM& other) {
    width = other.width;
    height = other.height;
    maxColourNumbers = other.maxColourNumbers;
    magicNumber = other.magicNumber;
    fileName = other.fileName;
    format = other.format;
    pixels = other.pixels; 
} 