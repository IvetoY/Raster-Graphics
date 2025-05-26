#include "Image.h"
#include <cstring>
#include <stdexcept>
#include "../Utils/PathHelper.h"
#include "../Pixel/Pixel.h"
#include "../Transformations/Transformations.h"
Image::Image(unsigned width, unsigned height, unsigned maxColourNumbers,const String& magicNumber, const String& fileName)
	:width(width), height(height) , maxColourNumbers(maxColourNumbers), magicNumber(magicNumber),
	fileName(fileName){}

Image::Image() : width(0), height(0), maxColourNumbers(0) {}

Image::Image(const Image& other) 
    : width(other.width),
      height(other.height),
      maxColourNumbers(other.maxColourNumbers),
      magicNumber(other.magicNumber),
      fileName(other.fileName) {
}

Image::Image(Image&& other) noexcept
    : width(std::exchange(other.width, 0)),
      height(std::exchange(other.height, 0)),
      maxColourNumbers(std::exchange(other.maxColourNumbers, 0)),
      magicNumber(std::move(other.magicNumber)),
      fileName(std::move(other.fileName)) {
}

const String& Image::getFileName() const {return fileName;}

void Image::setFileName(const String& newFileName){
	const char* ext = extractFileExtension(newFileName.c_str());

	if (strcmp(ext, getFileExtension()) != 0 || strlen(ext) != 4)
		throw std::runtime_error("Invalid file name!\n");

	fileName = newFileName;
}

void Image::print(std::ostream& os) const{
    os<<fileName<<std::endl;
}



