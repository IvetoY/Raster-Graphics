#include "PPM.h"
#include "Image.h"
#include <fstream>
#include "../Pixel/Pixel.h"
#include <cstring>
#include "../Utils/PathHelper.h" 
void PPM::swap(Image& other) {
        PPM* otherPPM = dynamic_cast<PPM*>(&other);
        if (!otherPPM) {
            throw std::runtime_error("Cannot swap PPM with non-PPM image");
        }
        std::swap(width, otherPPM->width);
        std::swap(height, otherPPM->height);
        std::swap(pixels, otherPPM->pixels);
}
PPM::PPM() : Image(), format(Format::P3_ASCII), pixels(nullptr){}
PPM::PPM(unsigned _width, unsigned _height, uint8_t _maxColour,
         const std::string& _magicNumber, const std::string& _fileName,
         Pixel**&& pixels, Format _format)
    : Image(_width, _height, _maxColour, _magicNumber, _fileName),
      format(_format),
      pixels(pixels)
{}
PPM::PPM(unsigned _width, unsigned _height, uint8_t _maxColourNumbers, 
         const std::string& _magicNumber, const std::string& _fileName,
         const Pixel* const* _pixels)
    : Image(_width, _height, _maxColourNumbers, _magicNumber, _fileName),
      format(_magicNumber == "P3" ? P3_ASCII : P6_BINARY)
{
    for(unsigned i = 0; i < height; ++i){
		this->pixels[i] = new Pixel[width];
		for (unsigned j = 0; j < width; ++j){
			this->pixels[i][j] = pixels[i][j];
		}
	}
}
PPM::PPM(const std::string& fileName):Image(), format(P3_ASCII), pixels(nullptr){load(fileName);}

PPM& PPM::operator=(const PPM& other){
    if(this!=&other){
        free();
        copy(other);
        Image::operator=(other);
    }
    return *this;
}
PPM& PPM::operator=(PPM&& other) noexcept{
    if (this != &other){
        free();
        copy(std::move(other));
        Image::operator=(std::move(other));
    }
    return *this;
}
PPM::~PPM(){free();}
PPM::PPM(const PPM& other) : Image(other), format(other.format) {copy(other);}
PPM::PPM(PPM&& other) noexcept : Image(std::move(other)){move(std::move(other));}

PPM* PPM::clone() const {return new PPM(*this);}

void PPM::grayscale() {
    for (unsigned y = 0; y < height; ++y){
        for(unsigned x = 0; x < width; ++x) {
            Pixel& p = pixels[y][x];
            uint8_t gray = static_cast<uint8_t>(
                0.299 * p.getRed() + 
                0.587 * p.getGreen() + 
                0.114 * p.getBlue()
            );
            p.setRed(gray);
            p.setGreen(gray);
            p.setBlue(gray);
        }
    }
}
void PPM::monochrome() {
    for (unsigned y = 0; y < height; ++y) {
        for(unsigned x = 0; x < width; ++x){
            Pixel& p = pixels[y][x];
            uint8_t avg = static_cast<uint8_t>(
                (p.getRed() + p.getGreen() + p.getBlue()) / 3
            );
            uint8_t bw = (avg > maxColourNumbers / 2) ? maxColourNumbers : 0;
            p.setRed(bw);
            p.setGreen(bw);
            p.setBlue(bw);
        }
    }
}
void PPM::rotateLeft(){
    Pixel** rotated = new Pixel*[width];
    for(unsigned x = 0; x < width; ++x){
        rotated[x] = new Pixel[height];
        for (unsigned y = 0; y < height; ++y){
            rotated[x][y] = pixels[y][width - 1 - x];
        }
    }
    free();
    pixels = rotated;
    std::swap(width, height);
}
void PPM::rotateRight(){
    Pixel** rotated = new Pixel*[width];
    for(unsigned x = 0; x < width; ++x){
        rotated[x] = new Pixel[height];
        for(unsigned y = 0; y < height; ++y){
            rotated[x][y] = pixels[height - 1 - y][x];
        }
    }
    free();
    pixels = rotated;
    std::swap(width, height);
}
void PPM::negative(){
    for (unsigned y = 0; y < height; ++y){
        for (unsigned x = 0; x < width; ++x) {
            Pixel& p = pixels[y][x];
            p.setRed(maxColourNumbers - p.getRed());
            p.setGreen(maxColourNumbers - p.getGreen());
            p.setBlue(maxColourNumbers - p.getBlue());
        }
    }
}

Image* PPM::collage(const Image* second, const std::string& newFileName, Direction d)const{
    return second->collageWithPPM(this, newFileName, d);
}

void PPM::save(const std::string& filename) const{
    std::ios_base::openmode mode = std::ios::out;
    if (format == P6_BINARY) {
        mode |= std::ios::binary;
    }
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
            else{//P6_BINARY
                file.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
            }
        }
        if(format == P3_ASCII) {file<< std::endl;}
    }
    file.close();
}
Image* PPM::collageWithPBM(const PBM* second, const std::string& newFileName, Direction d) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPGM(const PGM* second, const std::string& newFileName, Direction d) const{throw std::logic_error("Can't collage different types!");}

Image* PPM::collageWithPPM(const PPM* second, const std::string& newFileName, Direction d) const{
    if(!second){return nullptr;}
    if (strcmp(extractFileExtension(newFileName.c_str()), getFileExtension()) != 0){throw std::runtime_error("Invalid new file name for collage! Must be .ppm!");}
    if (format != second->format){throw std::runtime_error("Cannot collage PPM images with different formats");}

    size_t newWidth = d == Direction::HORIZONTAL ? width + second->width : std::max(width, second->width);
    size_t newHeight = d == Direction::HORIZONTAL ? std::max(height, second->height) : height + second->height;

    Pixel** newPixels = new Pixel*[newHeight];

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
        for(unsigned y = 0; y < second->getHeight(); ++y){
            for(unsigned x = 0; x < second->getWidth(); ++x){
                newPixels[y + height][x] = second->pixels[y][x];
            }
        }
    }
    uint8_t newMaxColour=std::max(maxColourNumbers, second->getMaxColourNumbers());
    return new PPM(newWidth, newHeight, newMaxColour, magicNumber, newFileName, std::move(newPixels), format);
}


void PPM::free(){
    if(pixels){
        for(unsigned y = 0; y < height; ++y){
            delete[] pixels[y];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}
void PPM::move(PPM&& other) noexcept {
    pixels = other.pixels;
    format = other.format;
    other.pixels = nullptr;
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

void PPM::load(const std::string& filePath) {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if(!file.is_open()){throw std::runtime_error("Failed to open PPM file");}
    file >> magicNumber;
    if(magicNumber != "P3" && magicNumber != "P6"){throw std::runtime_error("Invalid PPM format. Only P3 and P6 are supported!");}

    format = (magicNumber == "P3") ? P3_ASCII : P6_BINARY;
    file >> width >> height >> maxColourNumbers;

    file >> std::ws;
    while (file.peek() == '#') {
        file.ignore(1024, '\n');
    }
    file >> std::ws;
    free();
    pixels = new Pixel*[height];
    for (unsigned y = 0; y < height; ++y){
        pixels[y] = new Pixel[width];
    }

    if (format == P3_ASCII){
        for (unsigned y = 0; y < height; ++y){
            for (unsigned x = 0; x < width; ++x) {
                int r, g, b;
                file >> r >> g >> b;
                if (file.fail()){
                free();
                throw std::runtime_error("Error reading color values from PPM file");
                }
                
                if (r < 0 || r > maxColourNumbers || 
                    g < 0 || g > maxColourNumbers || 
                    b < 0 || b > maxColourNumbers) {
                    free();
                    throw std::runtime_error("Invalid color value in PPM file");
                }
                
                pixels[y][x] = Pixel(static_cast<uint8_t>(r),static_cast<uint8_t>(g),static_cast<uint8_t>(b));
            }
        }
    } else {
        file.ignore(1);
        
        const size_t rowSize = width * 3;
        char* rowBuffer = new char[rowSize];
        
        for (unsigned y = 0; y < height; ++y){
            file.read(rowBuffer, rowSize);
            if (file.gcount() != static_cast<std::streamsize>(rowSize)) {
                delete[] rowBuffer;
                free();
                throw std::runtime_error("Unexpected end of file in PPM binary data");
            }
            
            for (unsigned x = 0; x < width; ++x) {
                pixels[y][x] = Pixel(static_cast<uint8_t>(rowBuffer[x*3]),static_cast<uint8_t>(rowBuffer[x*3+1]),static_cast<uint8_t>(rowBuffer[x*3+2]));
            }
        }
        delete[] rowBuffer;
    }
    fileName = filePath;
}

Pixel PPM::getPixel(unsigned x, unsigned y) const {
    if(x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    return pixels[y][x];
}

void PPM::setPixel(unsigned x, unsigned y, const Pixel& pixel) {
    if(x >= width || y >= height){throw std::out_of_range("Invalid pixel coordinates!");}
    pixels[y][x] = pixel;
}