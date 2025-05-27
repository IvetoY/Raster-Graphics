#include "Image.h"
#include <cstring>
#include <stdexcept>
#include <fstream>
#include "../Utils/PathHelper.h"
#include "../Pixel/Pixel.h"
#include "../Transformations/Transformations.h"
Image::Image(unsigned width, unsigned height, unsigned maxColourNumbers,const std::string& magicNumber, const std::string& fileName)
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
    : width(std::move(other.width)),
      height(std::move(other.height)),
      maxColourNumbers(std::move(other.maxColourNumbers)),
      magicNumber(std::move(other.magicNumber)),
      fileName(std::move(other.fileName)) {
}
Image::Image(unsigned w, unsigned h) :width(w), height(h) {}
const std::string& Image::getFileName() const {return fileName;}

void Image::setFileName(const std::string& newFileName){
	const char* ext = extractFileExtension(newFileName.c_str());

	if (strcmp(ext, getFileExtension()) != 0 || strlen(ext) != 4)
		throw std::runtime_error("Invalid file name!\n");

	fileName = newFileName;
}

void Image::print(std::ostream& os) const{
    os<<fileName<<'\n';
}



