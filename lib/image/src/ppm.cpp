#include "ppm.h"
#include <fstream>
#include <iostream>

namespace luled::image
{

Image readPpm(const std::filesystem::path &p)
{
    if(!std::filesystem::exists(p)) 
	{
        throw std::runtime_error("file " + p.string() + " not found");
    }

    if(p.extension().compare(".ppm") != 0) 
	{
        throw std::runtime_error("Only .ppm files with P6 header supported");
    }

    std::ifstream imageFile(p);
    std::string buf;

    // header check
    std::getline(imageFile, buf);
    if (buf.compare("P6") != 0) 
	{
        throw std::runtime_error("Only .ppm files with P6 header supported");
    }

    Image image;

    int maxColorValue;
    imageFile >> image.width;
    imageFile >> image.height;
    imageFile >> maxColorValue; // assume 255;
	if(maxColorValue != 255){
		std::cerr << "Error in max color value" << std::endl;
	}
    image.channels = 3;

	size_t nBytes = image.width * image.height * image.channels;
    image.data = std::make_unique<uint8_t[]>(nBytes);

	size_t gPrev = imageFile.tellg();
	imageFile.seekg(-nBytes, std::ios::end); //start of image data

	if(imageFile.tellg() < gPrev)
	{
		throw std::runtime_error("Error in image pixel count");
	}

    imageFile.read(reinterpret_cast<char *>(image.data.get()), nBytes);

	if(imageFile.fail() || imageFile.eof())
	{
		throw std::runtime_error("Error reading image " + p.string() +  " data");
	}
    imageFile.close();
    return image;
}


}