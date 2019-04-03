#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Graphics::Image::Image()
	: width(0), height(0),
	data(nullptr), nrChannels(0),
	format(0)
{}

Graphics::Image::Image(const char* file_name, bool flip)
	: format(0)
{
	Load(file_name, flip);
}

Graphics::Image::Image(Image& image)
	: width(image.width), height(image.height),
	nrChannels(image.nrChannels), data(image.data),
	format(image.format)
{}

int Graphics::Image::GetWidth()
{
	return width;
}

int Graphics::Image::GetHeight()
{
	return height;
}

int Graphics::Image::GetnrChannels()
{
	return nrChannels;
}

int Graphics::Image::GetFormat()
{
	return format;
}

unsigned char* Graphics::Image::GetData()
{
	return data;
}

void Graphics::Image::Load(const char* file_name, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	data = stbi_load(file_name, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "Cannot load the image!" << std::endl;
		throw new std::exception("Cannot load the image!");
	}

	if (nrChannels == 3)
	{
		format = GL_RGB;
	}
	else if (nrChannels == 4)
	{
		format = GL_RGBA;
	}
}

void Graphics::Image::Dispose()
{
	stbi_image_free(data);
}

Graphics::Image::~Image()
{
	Dispose();
}
